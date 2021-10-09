import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class test {

    public static void main(String [] args) throws InterruptedException {
        Lock lock=new ReentrantLock();
        Condition full= lock.newCondition();
        Runnable task1 = new Runnable() {
            @Override
            public void run() {
                lock.lock();
                System.out.println("Thread " + Thread.currentThread().getId() +
                        ": is running " + toString());
                try { Thread.sleep(200); }
                catch (InterruptedException e) { e.printStackTrace(); }
                finally {
                    lock.unlock();
                }
            }
            @Override
            public String toString() {
                return "task1";
            }
        };

        Runnable task2 = new Runnable() {
            @Override
            public void run() {
                lock.lock();
                System.out.println("Thread " + Thread.currentThread().getId() +
                        " is running " + toString());
                try { Thread.sleep(100); }
                catch (InterruptedException e) { e.printStackTrace(); }
                finally {
                    lock.unlock();
                }
            }
            @Override
            public String toString() {
                return "task2";
            }
        };

        ReusableThread t =new ReusableThread();
        t.start();  //主线程启动子线程
        for(int i = 0; i < 5; i++){
            t.submit(task1);
            t.submit(task2);
        }
    }

}
