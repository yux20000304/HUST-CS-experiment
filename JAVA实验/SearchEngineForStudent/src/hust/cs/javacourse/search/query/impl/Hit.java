package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.util.FileUtil;

import java.util.Map;
import java.util.TreeMap;

/**
 * AbstractHit的具体实现类
 */
public class Hit extends AbstractHit {

    /**
     * 默认构造函数
     */
    public Hit(){

    }

    /**
     * 构造函数
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     */
    public Hit(int docId, String docPath){
        super(docId,docPath);
    }

    /**
     * 构造函数
     * @param docId              ：文档id
     * @param docPath            ：文档绝对路径
     * @param termPostingMapping ：命中的三元组列表
     */
    public Hit(int docId, String docPath, Map<AbstractTerm, AbstractPosting> termPostingMapping){
        super(docId,docPath,termPostingMapping);
    }

    /**
     * 获得文档id
     * @return ： 文档id
     */
    public int getDocId(){
        return this.docId;
    }

    /**
     * 获得文档绝对路径
     * @return ：文档绝对路径
     */
    public String getDocPath(){
        return this.docPath;
    }

    /**
     * 获得文档内容
     * @return ： 文档内容
     */
    public String getContent(){
        return this.content;
    }

    /**
     * 设置文档内容
     * @param content ：文档内容
     */
    public void setContent(String content){
        this.content=content;
    }

    /**
     * 获得文档得分
     * @return ： 文档得分
     */
    public double getScore(){
        return this.score;
    }

    /**
     * 设置文档得分
     * @param score ：文档得分
     */
    public void setScore(double score){
        this.score=score;
    }

    /**
     * 获得命中的单词和对应的Posting键值对
     * @return ：命中的单词和对应的Posting键值对
     */
    public Map<AbstractTerm, AbstractPosting> getTermPostingMapping(){
        return this.termPostingMapping;
    }

    /**
     * 获得命中结果的字符串表示, 用于显示搜索结果.
     * @return : 命中结果的字符串表示
     */
    @Override
    public String toString(){
        return "docId: " + this.docId + " docPath: " + this.docPath + " content: " +
                this.content +  " score: " + this.score + " termPostingMapping: " + this.termPostingMapping;
    }

    /**
     * 比较二个命中结果的大小，根据score比较
     * @param o     ：要比较的名字结果
     * @return      ：二个命中结果得分的差值
     */
    @Override
    public int compareTo(AbstractHit o){
        return (int)(this.score-o.getScore());
    }


}
