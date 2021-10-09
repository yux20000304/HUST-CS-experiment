package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.StopWords;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * AbstractTermTupleFilter的具体实现类,功能为停用词过滤器
 */
public class StopWordTermTupleFilter extends AbstractTermTupleFilter {

    public List<String> StopWord=new ArrayList<>();
    /**
     * 构造函数
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     */
    public StopWordTermTupleFilter(AbstractTermTupleStream input){
        super(input);
        this.StopWord.addAll(Arrays.asList(StopWords.STOP_WORDS));
    }

    /**
     * 构造函数
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     * @param StopWords：Filter的输入，类型为String[],停用词集合
     */
    public StopWordTermTupleFilter(AbstractTermTupleStream input,String[] StopWords){
        super(input);
        StopWord.addAll(Arrays.asList(StopWords));
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
        }while(StopWord.contains(tempTermTuple.term.getContent()));
        return tempTermTuple;
    }

}

