using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace EtelFutarok
{
    class Util
    {
        public static Random rnd = new Random();
    }
    class Program
    {
        static void Main(string[] args)
        {
            //PÉLDÁNYOSÍTÁS (1db étterem , 4-4db Futár (Fürgefutár ,TurboTeknos)
            Etterem etterem = new Etterem();
            List<Futar> F_futarok = Enumerable.Range(1, 4).Select(x => new Futar(Futar.FutarTipus.FurgeFutar)).ToList();
            List<Futar> T_futarok = Enumerable.Range(1, 4).Select(x => new Futar(Futar.FutarTipus.TurboTeknos)).ToList();

            //FUTAROK 1db LISTÁBA
            List<Futar> futarok = new List<Futar>();
            futarok.AddRange(F_futarok);
            futarok.AddRange(T_futarok);

            //TASKOK LÉTREHOZÁSA
            Task Rendelestkeszit = new Task(() =>
            {
                etterem.RendelesKeszit();
            }, TaskCreationOptions.LongRunning);

            List<Task> RendelesekDoWork = Etterem.osszesRendeles.Select(x => new Task(() =>
            {
                x.DoWork();
            }, TaskCreationOptions.LongRunning)).ToList();

            List<Task> futarok_tasks = futarok.Select(x => new Task(() =>
            {
                x.DoWork();
            }, TaskCreationOptions.LongRunning)).ToList();

            //NAPLÓZÓ SZÁL
            Console.CursorVisible = false;
            Task naplozo = new Task(() =>
            {
                int Time = 0;
                int refreshRate = 60;
                while (futarok_tasks.All(x => !x.IsCompleted))
                {
                    Console.Clear();

                     //AKTUALIS ELKESZÜLT RENDELÉSEK MENTÉSE             
                    List<Rendeles> saved = new List<Rendeles>();
                    saved.AddRange(Etterem.osszesRendeles);

                    //BEJÖVŐ RENDELÉSEK  
                    Console.WriteLine(" :: BEJOVO RENDELESEK ::");
                    saved.ForEach(x => Console.WriteLine(x.ToString()));
                    Console.WriteLine();

                    //IDŐ
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($" {Time/1000} . perc ");  

                    //STATISZTIKÁK
                    Console.ForegroundColor = ConsoleColor.DarkCyan;        
                    Console.WriteLine($"Elkeszult rendelesek szama: {saved.Count()}");
                    Console.WriteLine($"Kiszallitas alatt levo rendelesek: {saved.Where(x => x.Status == Rendeles.RendelesStatus.KiszallitasAlatt).Count()}");
                    Console.WriteLine($"Futarra varakozó rendelesek: {saved.Where(x => x.Status == Rendeles.RendelesStatus.FutarrVar).Count()}");
                    Console.WriteLine($"Kiszallitott rendelesek: {saved.Where(x => x.Status == Rendeles.RendelesStatus.Kiszallitva).Count()}");
                    Console.ForegroundColor = ConsoleColor.White;

                    //FUTAROK
                    Console.WriteLine();
                    Console.WriteLine(" :: FUTAROK ALLAPOTAI ::");
                    Console.ForegroundColor = ConsoleColor.Red;
                    //futarok.ForEach(x => Console.WriteLine($"FutarID: #{x.Id} [{x.Tipus}]  Kiszallitott: {x.KiszallitottRendelesek} ( {x.Status} ) Rendeles: #{(x.aktualisRendeles == null ? "nincs" : x.aktualisRendeles.Id.ToString())}"));
                    foreach (var x in futarok)
                    {
                        Console.WriteLine(x.ToString());
                        Console.WriteLine($"Kiszallitott  [ {x.KiszallitottDB} ] : { x.KiszallitottRendelesek}   || Összes penz: {x.OsszesPenz}Ft"  );
                        Console.WriteLine("--------------------------------------");
                    }
                    Console.ForegroundColor = ConsoleColor.White;

                    Thread.Sleep(refreshRate);
                    Time += refreshRate;
                }
                Console.WriteLine();

                //FUTÁRTIPUSOK GYŰJTÖTT PÉNZ ALAPÚ ÖSSZEHASONLÍTÁSA
                Console.WriteLine($"ÖSSZES RENDELES KISZALLITVA: {Etterem.osszesRendeles.Where(x => x.Status == Rendeles.RendelesStatus.Kiszallitva).Count()} ");

                double TurboTeknos = futarok.Where(x => x.Tipus == Futar.FutarTipus.TurboTeknos).Sum(x => x.OsszesPenz);
                double FurgeFutar = futarok.Where(x => x.Tipus == Futar.FutarTipus.FurgeFutar).Sum(x => x.OsszesPenz);

                double max = Math.Max(TurboTeknos, FurgeFutar);
                Console.WriteLine();
                Console.ForegroundColor = ConsoleColor.Green;

                Console.WriteLine($" #TEAM Turboteknos összes bevétel: {TurboTeknos}Ft {(max.Equals(TurboTeknos) ? "NYERTES" : "")}");
                Console.WriteLine($" #TEAM  FurgeFutar összes bevétel: {FurgeFutar}Ft {(max.Equals(FurgeFutar) ? "NYERTES" : "")}");

                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine();
                Console.WriteLine(" [:: SZIMULACIO VEGE ::] ");

            }, TaskCreationOptions.LongRunning);

            //TASKOK INDÍTÁSA
            naplozo.Start();
            Rendelestkeszit.Start();
            RendelesekDoWork.ForEach(x => x.Start());
            futarok_tasks.ForEach(x => x.Start());

            Console.ReadLine();
        }
    }
    class Etterem
    {
        public static List<Rendeles> osszesRendeles = new List<Rendeles>();
        static int nextId = 1;
        public static bool osszesRendelesElkeszult { get; private set; }
        public void RendelesKeszit()
        {
            while (osszesRendeles.Count() < 30)
            {
                Thread.Sleep(Util.rnd.Next(500, 600));

                int aktualis_Id = nextId++;
                int aktualis_Ertek = Util.rnd.Next(2000, 10000);
                int aktualis_Tavolsag = Util.rnd.Next(500, 10000);
                Rendeles.RendelesStatus aktualisStatus = Rendeles.RendelesStatus.FutarrVar;
                Rendeles aktualisRendeles = new Rendeles(aktualis_Id, aktualis_Ertek, aktualis_Tavolsag, aktualisStatus);
                aktualisRendeles.SzallitasiIdoKalk();
                osszesRendeles.Add(aktualisRendeles);

                lock (Futar.ValasztasLock)
                {
                    Monitor.Pulse(Futar.ValasztasLock); // Ha elkészült egy rendeles értesítünk egy futart hogy választhat
                }
            }
            osszesRendelesElkeszult = true;
        }
    }
    class Rendeles
    {
        public enum RendelesStatus
        {
            FutarrVar,
            KiszallitasAlatt,
            Kiszallitva,
        }
        public int Id { get; private set; }
        public int Ertek { get; private set; }
        public int Tavolsag { get; private set; }
        public RendelesStatus Status { get; set; }
        public int SzallitasiIdo { get; private set; }
        public Futar KiszallitoFutar { get; set; }

        public object RendelesLock = new object();

        public Rendeles(int id, int ertek, int tavolsag, RendelesStatus status)
        {
            Id = id;
            Ertek = ertek;
            Tavolsag = tavolsag;
            Status = status;

        }
        public void SzallitasiIdoKalk()
        {
            int km = Tavolsag / 1000;
            for (int i = 1; i < km + 1; i++)
            {
                int random = Util.rnd.Next(2, 4); // ! 2 éa 3.9 között kell  a feladatban
                SzallitasiIdo += random;
            }

            int atadasIdo = Util.rnd.Next(2000, 5000);
            SzallitasiIdo += atadasIdo;
        }
        public void DoWork()
        {
            while (Etterem.osszesRendeles.Any(x => x.Status != RendelesStatus.Kiszallitva))
            {
                lock (RendelesLock)
                    Monitor.Wait(RendelesLock);

                Status = RendelesStatus.KiszallitasAlatt;
                Thread.Sleep(SzallitasiIdo);
                Status = RendelesStatus.Kiszallitva;

                Thread.Sleep(SzallitasiIdo);
            }
        }
        public override string ToString()
        {
            return $"RendelesID: #{Id} ( {Status} )  { (Status == RendelesStatus.FutarrVar ? "" : $"(FutarID: #{KiszallitoFutar.Id.ToString()})")}";
        }
    }
    class Futar
    {
        public enum FutarTipus
        {
            FurgeFutar,
            TurboTeknos
        }
        public enum FutarStatus
        {
            RendelesreVar,
            Kiszallit,
            RendelesKiszallitva,
            VisszaUton
        }
        static int nextId = 1;
        public int Id { get; private set; }
        public FutarTipus Tipus { get; private set; }
        public FutarStatus Status { get; set; }

        public Rendeles aktualisRendeles { get; set; }

        public int SzallitasiIdo { get; private set; }
        public double SzallitasiDij { get; private set; }

        public string KiszallitottRendelesek { get; private set; } //****
        public int KiszallitottDB { get; private set; }
        public double OsszesPenz { get; private set; }

        public static object ValasztasLock = new object();

        public Futar(FutarTipus tipus)
        {
            Id = nextId++;
            Tipus = tipus;
            Status = FutarStatus.RendelesreVar;
            aktualisRendeles = null;
            OsszesPenz = 0;
            KiszallitottDB = 0;
        }
        public void DoWork()
        {
            while (Etterem.osszesRendelesElkeszult != true || Etterem.osszesRendeles.Any(x => x.Status != Rendeles.RendelesStatus.Kiszallitva))
            {
                if (Status == FutarStatus.RendelesreVar)
                {
                    if (Etterem.osszesRendeles.Where(x=>x.KiszallitoFutar==null).Count() == 0 ) //Ha nincs olyan rendelés
                    {
                        lock (ValasztasLock)
                        {
                            Monitor.Wait(ValasztasLock); //Várakozunk arra hogy rendelest választhassunk,legyen elérhető rendelés
                        }
                    }
                    lock (ValasztasLock) //Egyszerre csak egy futár választhat
                    {
                        if (Etterem.osszesRendeles.Any(x =>x.KiszallitoFutar==null )) //amik még nem voltak kiválasztva(futárnál)
                        {
                            List<Rendeles> ElerhetoRendelesek = Etterem.osszesRendeles.Where(x => x.KiszallitoFutar==null).ToList();
                            if (Tipus == FutarTipus.FurgeFutar)
                            {
                                aktualisRendeles = ElerhetoRendelesek.OrderBy(x => x.Tavolsag).First();
                                aktualisRendeles.Status = Rendeles.RendelesStatus.KiszallitasAlatt;
                                aktualisRendeles.KiszallitoFutar = this;
                                Status = FutarStatus.Kiszallit;

                                lock (aktualisRendeles.RendelesLock) {
                                    Monitor.Pulse(aktualisRendeles.RendelesLock); // Jelzünk a kivalasztott rendeles saját lockjának hogy kiválasztásra került
                                }

                            }
                            else
                            {
                                aktualisRendeles = ElerhetoRendelesek.OrderBy(x => x.Tavolsag).Last();
                                aktualisRendeles.Status = Rendeles.RendelesStatus.KiszallitasAlatt;
                                aktualisRendeles.KiszallitoFutar = this;
                                Status = FutarStatus.Kiszallit;

                                lock (aktualisRendeles.RendelesLock) {
                                    Monitor.Pulse(aktualisRendeles.RendelesLock);  // Jelzünk a kivalasztott rendeles saját lockjának hogy kiválasztásra került
                                }
                            }
                        }
                    }
                }
                if (Status == FutarStatus.Kiszallit)
                {
                    SzallitasiIdo = aktualisRendeles.SzallitasiIdo;
                    Thread.Sleep(SzallitasiIdo); // ODAÚT IDŐ

                    aktualisRendeles.Status = Rendeles.RendelesStatus.Kiszallitva;
                    KiszallitottDB++;
                    KiszallitottRendelesek += $" #{aktualisRendeles.Id} ,";
                    Status = FutarStatus.RendelesKiszallitva;
                    SzallitasiDijKalk();
                    aktualisRendeles = null; // RENDELES KISZALLITVA

                    Status = FutarStatus.VisszaUton;
                    Thread.Sleep(SzallitasiIdo); // VISSZAÚT IDŐ

                    OsszesPenz += SzallitasiDij; //PENZ 
                    Status = FutarStatus.RendelesreVar; //ÚJRA VÁRAKOZUNK
                }
            }
        }
        void SzallitasiDijKalk()
        {
            if (Tipus.Equals(FutarTipus.FurgeFutar))
            {
                SzallitasiDij = 600;
            }
            else
            {
                if (aktualisRendeles != null)
                {
                    SzallitasiDij = aktualisRendeles.Ertek * 0.05;
                    if (aktualisRendeles.Tavolsag / 1000 > 3)
                    {
                        SzallitasiDij += ((aktualisRendeles.Tavolsag - 3000) / 1000) * 200;
                    }
                }
            }
        }
        public override string ToString()
        {
            return $"FutarID: #{Id} [{Tipus}] ( {Status} ) Rendeles: #{(aktualisRendeles == null ? "nincs" : aktualisRendeles.Id.ToString())}";
        }
    }
}
