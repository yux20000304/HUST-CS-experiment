package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;

import java.util.Objects;

/**
 * TermTuple是AbstractTermTuple父类的子类实现
 */
public class TermTuple extends AbstractTermTuple {
    /**
     * 缺省构造
     */
    public TermTuple(){
    }
    /**
     * 构造函数
     * @param term ：单词
     * @param curPos  ：单词在文档里出现的位置
     */
    public TermTuple(AbstractTerm term,int curPos){
        this.term=term;
        this.curPos=curPos;
    }
    /**
     * 判断二个三元组内容是否相同
     * @param obj ：要比较的另外一个三元组
     * @return 如果内容相等（三个属性内容都相等）返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj){
        if(obj instanceof TermTuple) {
            TermTuple temp=(TermTuple) obj;
            return Objects.equals(this.term,temp.term) && this.curPos==temp.curPos;
        }
        return false;
    }

    /**
     * 获得三元组的字符串表示
     * @return ： 三元组的字符串表示
     */
    @Override
    public String toString(){
        return "word: "+this.term.toString()+" feq: "+this.freq+" curPos: "+this.curPos;
    }
}

