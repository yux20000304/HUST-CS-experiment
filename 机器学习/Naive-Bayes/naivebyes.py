#!usr/bin/python
# -*- coding: utf-8 -*-


import numpy as np
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import MultinomialNB



def textParse(bigString):
    #将单词以空格划分
    listOfTokens = bigString.split()
    #去除单词长度小于2的无用单词
    return [tok.lower() for tok in listOfTokens if len(tok)>2]

#去列表中重复元素，并以列表形式返回
def createVocaList(dataSet):
    vocabSet = set({})
    #去重复元素，取并集
    for document in dataSet:
        vocabSet = vocabSet | set(document)
    return list(vocabSet)

#统计每一文档（或邮件）在单词表中出现的次数，并以列表形式返回
def setOfWordsToVec(vocabList,inputSet):
    #创建0向量，其长度为单词量的总数
    returnVec = [0]*len(vocabList)
    #统计相应的词汇出现的数量
    for word in inputSet:
        if word in vocabList:
            returnVec[vocabList.index(word)] += 1
    return returnVec

#处理数据
def data_deal(x,y):
    x_train,x_test,y_train,y_test=train_test_split(x, y, test_size=0.25)
    x_train,x_test,y_train,y_test=np.array(x_train),np.array(x_test),np.array(y_train),np.array(y_test)
    return x_train,x_test,y_train,y_test

def main():
    docList,classList,x = [],[],[]
    for i in range(1, 26):
        # 读取第i篇垃圾文件，并以列表形式返回
        wordList = textParse(open('email/spam/{0}.txt'.format(i)).read())
        docList.append(wordList)
        classList.append(1)        # 标记文档为垃圾文档
        # 读取第i篇非垃圾文件，并以列表形式返回
        wordList = textParse(open('email/ham/{0}.txt'.format(i)).read())
        docList.append(wordList)
        classList.append(0)        # 标记文档为非垃圾文档
    vocabList = createVocaList(docList)  # 创建词汇表，不重复
    # 将数据向量化
    for wordList in docList:
        x.append(setOfWordsToVec(vocabList, wordList))
    #处理数据
    x_train,x_test,y_train,y_test=data_deal(x,classList)
    #训练数据
    pSpam=MultinomialNB()
    pSpam.fit(x_train,y_train)
    #测试数据
    y_pred=pSpam.predict(x_test)

    #输出
    print("正确值：{0}".format(y_test))
    print("预测值：{0}".format(y_pred))
    print("准确率：%f%%"%(accuracy_score(y_test, y_pred)*100))

if __name__ == '__main__':
    main()