# -*- coding: UTF-8 -*-

####################################################
#       gender recognition by naive bayes          #
#       resource from Kaggle                       #
#                                                  #
#       author:yyx_inevitable                      #
#       by 2020.6.4  22:01                         #
####################################################

import numpy as np                  
import  pandas as pd

from sklearn import preprocessing
import seaborn as sns
import matplotlib.pyplot as plt
import warnings

from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

from sklearn import naive_bayes
from sklearn.neighbors import KNeighborsClassifier
from sklearn import svm 

from sklearn.model_selection import cross_val_score

import xgboost


def classify(model,x_train,y_train,x_test,y_test):
    from sklearn.metrics import classification_report
    target_names = ['female', 'male']
    model.fit(x_train,y_train)              #训练数据
    y_pred=model.predict(x_test)
    print(classification_report(y_test, y_pred, target_names=target_names, digits=6))


#防止报错
warnings.filterwarnings('ignore')

#读取数据
voice = pd.read_csv('./input/voice.csv')
#文本替换成数字
le = preprocessing.LabelEncoder()               
voice["label"] = le.fit_transform(voice["label"])

voice[:]=preprocessing.MinMaxScaler().fit_transform(voice)


train, test = train_test_split(voice, test_size=0.3)        #随机划分训练集和数据集，这里使用7：3划分

#使用所有的变量来训练
x_train = train.iloc[:,:-1]
y_train = train["label"]
x_test = test.iloc[:,:-1]
y_test = test["label"]

#只使用三个变量来训练
x_train1 = train[["meanfun","IQR","Q25","sd"]]
y_train1 = train["label"]
x_test1 = test[["meanfun","IQR","Q25","sd"]]
y_test1 = test["label"]

model=KNeighborsClassifier(n_neighbors=1)
score_list=[]
for each in range(1,20):
    knn2 = KNeighborsClassifier(n_neighbors=each)
    knn2.fit(x_train,y_train)
    score_list.append(knn2.score(x_test,y_test))

plt.figure(figsize=(20,8) , dpi=80)
plt.grid(alpha=0.4,linestyle='-.')
plt.xlabel('Number of Neighbors K')
plt.ylabel('Score')
plt.xticks(np.arange(0,20,1))
plt.plot(range(1,20),score_list)
plt.show()                      
classify(model,x_train,y_train,x_test,y_test)



