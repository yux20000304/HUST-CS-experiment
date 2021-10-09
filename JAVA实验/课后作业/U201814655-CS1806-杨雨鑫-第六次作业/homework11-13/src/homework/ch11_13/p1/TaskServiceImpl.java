package homework.ch11_13.p1;

import java.util.ArrayList;

public class TaskServiceImpl implements TaskService{
    ArrayList<Task> tasks=new ArrayList<>();

    public TaskServiceImpl(){
    }

    @Override
    public void exeuteTasks() {
        for(int i=0;i<tasks.size();i++){
            tasks.get(i).execute();
        }
    }

    @Override
    public void addTask(Task t) {
        tasks.add(t);
    }
}
