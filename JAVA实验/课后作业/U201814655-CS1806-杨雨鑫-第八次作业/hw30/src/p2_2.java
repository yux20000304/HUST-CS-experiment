import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;



public class p2_2 {
    private static int flag=0;
    public static void main(String[] args){
        SyncQueue<Integer> syncQueue = new SyncQueue<>();
        Lock lock=new ReentrantLock();
        Condition full= lock.newCondition();
        Condition empty= lock.newCondition();
        Runnable produceTask = ()->{
            while(true){
                lock.lock();
                try {
                    List<Integer> list = new ArrayList<>();
                    System.out.print("produce:");
                    int elementsCount = (int)(Math.random() * 10) + 1;
                    for(int i = 0; i < elementsCount; i++){
                        int r = (int)(Math.random() * 10) + 1;
                        list.add(r);
                        System.out.print(r);
                    }
                    syncQueue.produce(list);
                    System.out.print("\n");
                    flag=1;
                    empty.signal();
                    Thread.sleep((int)(Math.random() * 5) + 1);
                }
                catch (InterruptedException e) { e.printStackTrace(); }
                finally {
                    lock.unlock();
                }
            }
        };

        Runnable consumeTask = ()->{
            while (true){
                lock.lock();
                try{
                    while(flag == 0){
                        empty.await();
                    }
                    System.out.print("consume:");
                    List<Integer> list = syncQueue.consume();
                    for(Integer ele:list){
                        System.out.print(ele);
                    }
                    System.out.print("\n");
                    flag=0;
                    full.signal();
                    Thread.sleep((int)(Math.random()*5) + 1);
                }
                catch (InterruptedException e) { e.printStackTrace(); }
                finally {
                    lock.unlock();
                }
            }
        };

        ExecutorService es = Executors.newFixedThreadPool(2);
        es.execute(produceTask);
        es.execute(consumeTask);
        es.shutdown();
        while (!es.isTerminated()){}
    }
}