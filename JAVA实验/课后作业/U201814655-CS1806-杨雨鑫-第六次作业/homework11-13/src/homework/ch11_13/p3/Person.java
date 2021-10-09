package homework.ch11_13.p3;

import java.util.Objects;

public class Person implements Cloneable{
    private String name;    //姓名
    private int age;        //年龄

    public Person(){        //缺省构造函数

    }
    public Person(String name,int age){  //构造函数
        this.name=name;
        this.age=age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
    @Override
    public String toString(){   //覆盖
        return "name: "+name+"age: "+age;
    }
    @Override
    public boolean equals(Object o){    //比较两个person对象是否相等
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        if(name == null){
            if(person.name==null)
                return age == person.age;
            return false;
        }
        return age == person.age && name.equals(person.name);
    }
    @Override
    public Object clone() throws CloneNotSupportedException{      //深拷贝克隆
        Person new_person=(Person)super.clone();
        new_person.age=this.age;
        new_person.name=new String(this.name);
        return new_person;
    }
    public static void main(String [] args){
        int age=20;
        String name="aaa";
        Person p1=new Person(name,age);
        Person p2=new Person(name,age);



        System.out.println(p1.equals(p2));

    }
}
