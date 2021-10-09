package homework.ch11_13.p4;

import homework.ch11_13.p3.Person;

abstract public class Component extends Object{
    protected int id;
    protected String name;
    protected double price;

    public Component(){

    }

    public Component(int id,String name,double price){
        this.id=id;
        this.price=price;
        this.name=name;
    }

    public int getId(){
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return calcPrice();
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public abstract void add(Component component) throws UnsupportedOperationException;
    public abstract void remove(Component component) throws UnsupportedOperationException;
    public abstract double calcPrice();
    public abstract Iterator iterator();

    @Override
    public boolean equals(Object obj){
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Component component = (Component) obj;
        if(name == null){
            if(component.name==null)
                return id == component.id && price==component.price;
            return false;
        }
        return id==component.id && price==component.price;
    }

    @Override
    public String toString(){
        return "id: "+id+"name: "+name+" price: "+price;
    }
}
