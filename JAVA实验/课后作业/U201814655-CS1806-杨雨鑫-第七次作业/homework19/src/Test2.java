import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Test2 {
    public static class TwoTuple<T1 extends Comparable<T1>, T2 extends Comparable<T2>> implements Comparable<TwoTuple<T1, T2>> {
        T1 first;
        T2 second;

        public TwoTuple() {

        }

        public TwoTuple(T1 first, T2 second) {
            this.first = first;
            this.second = second;
        }

        public T1 getFirst() {
            return first;
        }

        public void setFirst(T1 first) {
            this.first = first;
        }

        public T2 getSecond() {
            return second;
        }

        public void setSecond(T2 second) {
            this.second = second;
        }


        @Override
        public boolean equals(Object obj) {
            if (obj instanceof TwoTuple) {
                TwoTuple<T1, T2> twoTuple = (TwoTuple<T1, T2>) obj;
                return this.first.equals(twoTuple.first) && (this.second.equals(twoTuple.second));
            } else return false;
        }

        @Override
        public String toString() {
            return "("+first.toString()+","+second.toString()+")";
        }

        @Override
        public int compareTo(TwoTuple o) {
            if (o.first.equals(first))
                return second.compareTo(((TwoTuple<T1, T2>) o).second);
            else return first.compareTo(((TwoTuple<T1, T2>) o).first);
        }

        public static void main(String[] argv) {

            TwoTuple<Integer, String> twoTuple1 = new TwoTuple<>(1, "ccc");
            TwoTuple<Integer, String> twoTuple2 = new TwoTuple<>(1, "bbb");
            TwoTuple<Integer, String> twoTuple3 = new TwoTuple<>(1, "aaa");
            TwoTuple<Integer, String> twoTuple4 = new TwoTuple<>(2, "ccc");
            TwoTuple<Integer, String> twoTuple5 = new TwoTuple<>(2, "bbb");
            TwoTuple<Integer, String> twoTuple6 = new TwoTuple<>(2, "aaa");
            List<TwoTuple<Integer, String>> list = new ArrayList<>();
            list.add(twoTuple1);
            list.add(twoTuple2);
            list.add(twoTuple3);
            list.add(twoTuple4);
            list.add(twoTuple5);
            list.add(twoTuple6);

            //测试equals，contains方法是基于equals方法结果来判断
            TwoTuple<Integer, String> twoTuple10 = new TwoTuple<>(1, "ccc"); //内容=twoTuple1
            System.out.println(twoTuple1.equals(twoTuple10)); //应该为true
            if (!list.contains(twoTuple10)) {
                list.add(twoTuple10);  //这时不应该重复加入
            }

            //sort方法是根据元素的compareTo方法结果进行排序，课测试compareTo方法是否实现正确
            Collections.sort(list);


            for (TwoTuple<Integer, String> t : list) {
                System.out.println(t);
            }

            TwoTuple<TwoTuple<Integer, String>, TwoTuple<Integer, String>> tt1 =
                    new TwoTuple<>(new TwoTuple<>(1, "aaa"), new TwoTuple<>(1, "bbb"));
            TwoTuple<TwoTuple<Integer, String>, TwoTuple<Integer, String>> tt2 =
                    new TwoTuple<>(new TwoTuple<>(1, "aaa"), new TwoTuple<>(2, "bbb"));
            System.out.println(tt1.compareTo(tt2)); //输出-1
            System.out.println(tt1);
        }
    }

    public static void main(String[] args){
        TwoTuple<Integer,String> twoTuple1 =new TwoTuple<>(1, "ccc");
        TwoTuple<Integer,String> twoTuple2 =new TwoTuple<>(1, "bbb");
        TwoTuple<Integer,String> twoTuple3 =new TwoTuple<>(1, "aaa");
        TwoTuple<Integer,String> twoTuple4 =new TwoTuple<>(2, "ccc");
        TwoTuple<Integer,String> twoTuple5 =new TwoTuple<>(2, "bbb");
        TwoTuple<Integer,String> twoTuple6 =new TwoTuple<>(2, "aaa");
        List<TwoTuple<Integer,String>> list = new ArrayList<>();
        list.add(twoTuple1);
        list.add(twoTuple2);
        list.add(twoTuple3);
        list.add(twoTuple4);
        list.add(twoTuple5);
        list.add(twoTuple6);

        //测试equals，contains方法是基于equals方法结果来判断
        TwoTuple<Integer,String> twoTuple10 =new TwoTuple<>(1, "ccc"); //内容=twoTuple1
        System.out.println(twoTuple1.equals(twoTuple10)); //应该为true
        if(!list.contains(twoTuple10)){
            list.add(twoTuple10);  //这时不应该重复加入
        }

        //sort方法是根据元素的compareTo方法结果进行排序，课测试compareTo方法是否实现正确
        Collections.sort(list);


        for (TwoTuple<Integer, String> t: list) {
            System.out.println(t);
        }

        TwoTuple<TwoTuple<Integer,String >,TwoTuple<Integer,String >> tt1 =
                new TwoTuple<>(new TwoTuple<>(1,"aaa"),new TwoTuple<>(1,"bbb"));
        TwoTuple<TwoTuple<Integer,String >,TwoTuple<Integer,String >> tt2 =
                new TwoTuple<>(new TwoTuple<>(1,"aaa"),new TwoTuple<>(2,"bbb"));
        System.out.println(tt1.compareTo(tt2)); //输出-1
        System.out.println(tt1);

    }
}
