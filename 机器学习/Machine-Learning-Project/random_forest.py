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
from sklearn.model_selection import learning_curve

from sklearn import naive_bayes
from sklearn.neighbors import KNeighborsClassifier
from sklearn import ensemble
from sklearn import svm 

import xgboost

def plot_learning_curve(estimator,title, X, y, ax, ylim=None, cv=3, n_jobs=None):
    array=np.linspace(0.01,1.0,10)
    train_sizes, train_scores, test_scores = learning_curve(estimator, X, y,cv=cv,n_jobs=n_jobs,train_sizes=array)
    ax.set_title(title)
    if ylim is not None:
        ax.set_ylim(*ylim)
    ax.set_xlabel("Training examples")
    ax.set_ylabel("Score")
    ax.grid() 
    ax.plot(train_sizes, np.mean(train_scores, axis=1), 'o-' , color="r",label="Training score")
    ax.plot(train_sizes, np.mean(test_scores, axis=1), 'o-' , color="g",label="Test score")
    ax.legend(loc="best")
    return ax

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
x_train1 = train[["meanfun","IQR","Q25","sd","sp.ent"]]
y_train1 = train["label"]
x_test1 = test[["meanfun","IQR","Q25","sd","sp.ent"]]
y_test1 = test["label"]

model=ensemble.RandomForestClassifier(n_estimators = 20)
plot_learning_curve(model, "Random Forest", x_train1 , y_train1 , ax=plt.gca(), ylim = [0.1, 1.05],n_jobs=20, cv=3)
plt.show()
classify(model,x_train1,y_train1,x_test1,y_test1)

model=naive_bayes.GaussianNB()
classify(model,x_train1,y_train1,x_test1,y_test1)

