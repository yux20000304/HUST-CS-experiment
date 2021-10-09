package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

/**
 * AbstractTermTupleScanner的具体实现类
 */
public class TermTupleScanner extends AbstractTermTupleScanner {

    /**
     * regex为切割字符串的正则表达式
     */
    public String regex;

    /**
     * nowStringList为BufferReader.readLine()所得到的List中当前未被读取的部分
     */
    public List<String> nowStringList = new ArrayList<>();;

    /**
     * position为当前三元组的位置
     */
    public int position = 0;

    /**
     * stringSplitter为分词工具
     */
    public StringSplitter stringSplitter = new StringSplitter();
    /**
     * 缺省构造函数
     */
    public  TermTupleScanner(){
    }

    /**
     * 构造函数
     * @param input：指定输入流对象，应该关联到一个文本文件
     */
    public  TermTupleScanner(BufferedReader input){
        super(input);
        this.regex= Config.STRING_SPLITTER_REGEX; //正则表达式定义好在config中
        this.stringSplitter.setSplitRegex(this.regex);
    }

    /**
     * 构造函数
     * @param input：指定输入流对象，应该关联到一个文本文件
     * @param regex：指定输入流对象，英文分词正则表达式
     */
    public  TermTupleScanner(BufferedReader input,String regex){
        super(input);
        this.regex= regex;
        this.stringSplitter.setSplitRegex(this.regex);
    }

    /**
     * 获得下一个三元组
     * @return 下一个三元组；如果到了流的末尾，返回null
     */
    public AbstractTermTuple next(){
        try {
            //没有了就再readLine一次
            if(nowStringList.isEmpty()){
                String tempString;
                if((tempString=input.readLine())==null)
                    return null;
                while(tempString.trim().length()==0){
                    tempString = input.readLine();
                    if (tempString == null)
                        return null;
                }
                List<String> temp = stringSplitter.splitByRegex(tempString);
                for (String i : temp)
                    nowStringList.add(i.toLowerCase(Locale.ROOT));
            }
            Term term = new Term(nowStringList.get(0));
            TermTuple termTuple =new TermTuple(term,position);
            position++;
            nowStringList.remove(0);
            return termTuple;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    /**
     * 关闭流
     */
    @Override
    public void close() {
        super.close();
    }
}
