package homework.ch11_13.p4;

import java.util.ArrayList;

public class ComponentList extends ArrayList<Component> implements Iterator{
    private int position=0;

    public ComponentList(){

    }

    public boolean hasNext(){
        if(position>=this.size())
            return false;
        else
            return true;
    }

    public Component next(){
        if(hasNext()){
            Component c=this.get(position);
            position++;
            return c;
        }
        else
            return null;
    }

}
