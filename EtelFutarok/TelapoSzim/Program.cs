using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TelapoSzim
{
    public enum TelapoStatus
    {
        Diskural,
        Szabad
    }
    public enum AjandekStatus
    {
        ManoraVarakozik,
        SzallitasAlatt,
        FaAlatt
    }
    public enum ManoStatus
    {
        TelaporaVarakozik,
        TelapovalDiskural,
        AjandekotSzallit,
        BajbaKerult,
        Visszauton
    }
    class Program
    {
        static void Main(string[] args)
        {
        }
    }
    class Telapo
    {
        static public  object listaLock = new object();
        static public List<Ajandek> OsszesAjandek = new List<Ajandek>();
        static public TelapoStatus Status = TelapoStatus.Szabad;
    }
    class Ajandek
    {
        static public int _nextID = 1;
        public int ID { get; private set; }

        public AjandekStatus Status { get; set; }
        public Mano Kiszallito { get; private set; }

        public Ajandek()
        {
            ID = _nextID++;
            Status = AjandekStatus.ManoraVarakozik;
            Kiszallito = null;                                 
            Telapo.OsszesAjandek.Add(this);
        }

        public override string ToString()
        {
            return $" AjandekID: #{ID} ( {Status} )  {(Kiszallito == null ? "#nincs" : Kiszallito.ID.ToString())} ";
        }
    }
    class Mano
    {
        static public int _nextID = 1;
        public int ID { get; private set; }

        public ManoStatus Status { get; private set; }
    }
}
