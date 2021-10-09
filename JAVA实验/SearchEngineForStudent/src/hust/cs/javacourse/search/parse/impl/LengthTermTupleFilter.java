package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StopWords;

/**
 * AbstractTermTupleFilter的具体实现类,功能为长度过滤器
 */
public class LengthTermTupleFilter extends AbstractTermTupleFilter {
    public int minLength;
    public int maxLength;

    /**
     * 构造函数
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     */
    public LengthTermTupleFilter(AbstractTermTupleStream input){
        super(input);
        minLength = Config.TERM_FILTER_MINLENGTH;
        maxLength = Config.TERM_FILTER_MAXLENGTH;
    }

    /**
     * 构造函数
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     * @param minLength：Filter的输入，类型为int,单词最小长度
     * @param maxLength：Filter的输入，类型为int,单词最大长度
     */
    public LengthTermTupleFilter(AbstractTermTupleStream input,int minLength,int maxLength){
        super(input);
        this.minLength=minLength;
        this.maxLength=maxLength;
    }


    /**
     * 获得下一个三元组
     * @return 下一个三元组；如果到了流的末尾，返回null(该三元组已进行长度过滤）
     */
    public AbstractTermTuple next(){
        AbstractTermTuple tempTermTuple;
        do{
            tempTermTuple =input.next();
            if(tempTermTuple==null)
                return null;
        }while(tempTermTuple.term.getContent().length()<minLength||tempTermTuple.term.getContent().length()>maxLength);
        return tempTermTuple;
    }
}
