using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CsirkeFutar
{
    class Program
    {
        static void Main(string[] args)
        {

        }
        public enum ConsumerStatus
        {
            Not_hungry,
            Hungry,
            Ordering,
            WaitingForFood,
            FoodDelivered
        }
        public enum OrderStatus
        {
            KitchenFIFO,
            Cooking,
            CookingDone,
            WaitingForRunner,
            UnderDelivery,
            Delivered
        }
        public enum RunnerStatus
        {
            Waiting,
            Deliver,
            OnTheWayBack
        }

        class Order
        {
            static int NextId = 1;
            public int ID { get; private set; }
            public OrderStatus Status { get; set; }
            public Runner Runner { get; set; }
            public int MakingTime { get; private set; }
            public Order()
            {
                ID = NextId++;
                Status = OrderStatus.KitchenFIFO;
                Runner = null;
                MakingTime = Util.rnd.Next(3*Util.PERC, 10*Util.PERC+1);
            }
        }
        class Consumer
        {
            static int NextID = 1;
            public int ID { get; private set; }
            public ConsumerStatus Status { get; set; }
            public Order Order { get; private set; }
            public Consumer()
            {
                ID = NextID++;
                Status = ConsumerStatus.Not_hungry;
                Order = null;

            }

            public void DoWork()
            {
                Thread.Sleep(Util.rnd.Next(1 * Util.PERC, 2* Util.PERC + 1));
                Status=ConsumerStatus.Hungry;
                Thread.Sleep(Util.rnd.Next(2 * Util.PERC, 5 * Util.PERC + 1));
                Status = ConsumerStatus.Ordering;

                Order = new Order();
                Kitchen.AllOrders.Enqueue(Order);
            }
        }
        class Kitchen
        {
            public static ConcurrentQueue<Order> AllOrders = new ConcurrentQueue<Order>();
            public string KitchenStatus { get; private set; }
            public Order selected;

            public void MakingOrder()
            {
                while(true)
                {
                    AllOrders.TryDequeue(out selected);
                    if (selected != null)
                    {

                    }
                    else
                    {

                    }
                }
               
            }
        }
        class Runner
        {

        }
        static class Util
        {
            public static Random rnd = new Random();
            public static int PERC=1000;
        }
    }
}
