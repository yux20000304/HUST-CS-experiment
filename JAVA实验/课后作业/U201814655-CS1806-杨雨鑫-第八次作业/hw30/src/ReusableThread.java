import javax.swing.*;
import java.util.*;
import java.util.concurrent.locks.Condition;

public class ReusableThread extends Thread{
    private Runnable runTask = null;  //保存接受的线程任务
    //TODO 加入需要的数据成员
    private final Queue<Runnable> threadList= new LinkedList<Runnable>();

    //只定义不带参数的构造函数
    public ReusableThread(){
        super();
    }

    /**
     * 覆盖Thread类的run方法
     */
    @Override
    public void run() {
        //这里必须是永远不结束的循环
        while(true){
            if(!threadList.isEmpty()) {
                Runnable task = null;
                task = threadList.poll();
                task.run();
            }
        }
    }

    /**
     * 提交新的任务
     * @param task 要提交的任务
     */
    public void submit(Runnable task){
        threadList.add(task);
    }
}

