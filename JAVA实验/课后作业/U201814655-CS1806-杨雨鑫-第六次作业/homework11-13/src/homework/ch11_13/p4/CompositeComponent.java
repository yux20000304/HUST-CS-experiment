package homework.ch11_13.p4;

public class CompositeComponent extends Component{
    protected ComponentList childs=new ComponentList();

    public CompositeComponent(){

    }

    public CompositeComponent(int id,String name,double price){
        super(id, name, price);
    }

    public void add(Component component) throws UnsupportedOperationException{
        childs.add(component);
    }

    public void remove(Component component) throws UnsupportedOperationException{
        childs.remove(component);
    }

    public double calcPrice(){
        double price=0.0;
        while(childs.hasNext()){
            Component s=childs.next();
            price+=s.calcPrice();
        }
        return price;
    }

    public Iterator iterator(){
        CompositeIterator a=new CompositeIterator(childs);
        return a;
    }

    @Override
    public String toString(){
        String s=new String();
        for(int i=0;i<childs.size();i++){
            s+=childs.get(i).toString();
        }
        return super.toString()+s;
    }

    public static void main(String [] args){
        Object[][] objects = null;
        int id = 0;
        String aName1 = "aaa1";
        String aName2 = "aaa2";
        String aName3 = "aaa3";
        String aName4 = "aaa4";
        double aPrice1 = 5.0D;
        double aPrice2 = 10.0D;
        double aPrice3 = 15.0D;
        double aPrice4 = 25.0D;
        int var26 = id + 1;
        Component a1 = new AtomicComponent(id, aName1, aPrice1);
        Component a2 = new AtomicComponent(var26++, aName2, aPrice2);
        Component a3 = new AtomicComponent(var26++, aName3, aPrice3);
        Component a4 = new AtomicComponent(var26++, aName4, aPrice4);
        String cName1 = "ccc1";
        String cName2 = "ccc2";
        String cName3 = "ccc3";
        Component c1 = new CompositeComponent(var26++, cName1, 10.0D);
        Component c2 = new CompositeComponent(var26++, cName2, 10.0D);
        String tName = "root";
        Component root = new CompositeComponent(var26++, tName, 100.0D);
        c1.add(a1);
        c1.add(a2);
        c1.add(c2);
        c2.add(a3);
        c2.add(a4);
        objects = new Object[][]{{a1, aPrice1}, {root, 0.0D}, {c1, aPrice1 + aPrice2 + aPrice3 + aPrice4}};
        System.out.println(objects);
        String[] m={root.toString(),c1.toString(),c2.toString()};
        boolean a=testTestToString(root,m);
        System.out.println(a);
    }

    public static boolean testTestToString(Component c, String[] values) {
        String toString = c.toString();
        String[] var4 = values;
        int var5 = values.length;

        for(int var6 = 0; var6 < var5; ++var6) {
            String value = var4[var6];
            int index = toString.indexOf(value);
            System.out.println((index != -1));
        }
        return true;
    }
}
