package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StopWords;

/**
 * AbstractTermTupleFilter的具体实现类,功能为单词过滤器
 */
public class PatternTermTupleFilter extends AbstractTermTupleFilter {

    public String regex ;

    /**
     * 构造函数
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     */
    public PatternTermTupleFilter(AbstractTermTupleStream input){
        super(input);
        regex= Config.TERM_FILTER_PATTERN;
    }

    /**
     * 构造函数
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     * @param regex：Filter的输入，类型为String,过滤单词的正则表达式
     */
    public PatternTermTupleFilter(AbstractTermTupleStream input,String regex){
        super(input);
        this.regex=regex;
    }


    /**
     * 获得下一个三元组
     * @return 下一个三元组；如果到了流的末尾，返回null(该三元组已进行停用词过滤）
     */
    public AbstractTermTuple next(){
        AbstractTermTuple tempTermTuple;
        do{
            tempTermTuple =input.next();
            if(tempTermTuple==null)
                return null;
        }while(!(tempTermTuple.term.getContent().matches(regex)));
        return tempTermTuple;
    }

}