package homework.ch11_13.p1;

public class test {
    public static void main(String [] args){
        TaskService test=new TaskServiceImpl();
        Task t1=new Task1();
        Task t2=new Task2();
        Task t3=new Task3();
        test.addTask(t1);
        test.addTask(t2);
        test.addTask(t3);
        test.exeuteTasks();

    }
}
