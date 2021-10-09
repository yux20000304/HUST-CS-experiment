package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Objects;

/**
 * Term是AbstractTerm父类的子类实现
 */
public class Term extends AbstractTerm {

    /**
     * 缺省构造
     */
    public Term(){
    }

    /**
     * 构造函数
     */
    public Term(String content){
        super(content);//调用父类构造函数
    }


    /**
     * 判断二个Term内容是否相同
     * @param obj ：要比较的另外一个Term
     * @return 如果内容相等返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj){
        if(obj instanceof Term) {
            Term temp = (Term) obj;
            return Objects.equals(this.content,temp.content);
        }
        return false;
    }

    /**
     * 返回Term的字符串表示
     * @return 字符串
     */
    @Override
    public String toString(){
        return this.content;
    }

    /**
     * 返回Term内容
     * @return Term内容
     */
    public String getContent(){
        return this.content;
    }

    /**
     * 设置Term内容
     * @param content：Term的内容
     */
    public void setContent(String content){
        this.content=content;
    }

    /**
     * 比较二个Term大小（按字典序）
     * @param o： 要比较的Term对象
     * @return ： 返回二个Term对象的字典序差值
     */
    @Override
    public int compareTo(AbstractTerm o){
        return content.compareTo(o.getContent());
    }

    /**
     * 写到二进制文件
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            //将 this 对象的成员序列化
            out.writeObject(this.content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 从二进制文件读
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        //将 this 对象的成员反序列化
        try {
            this.content = (String)(in.readObject());
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
