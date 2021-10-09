# -*- coding: UTF-8 -*-

####################################################
#       gender recognition by naive bayes          #
#       resource from Kaggle                       #
#                                                  #
#       author:yyx_inevitable                      #
#       by 2020.6.4  18:01                         #
####################################################

import numpy as np                  
import  pandas as pd

from sklearn import preprocessing
import seaborn as sns
import matplotlib.pyplot as plt
import warnings


warnings.filterwarnings('ignore')
#读取数据
voice = pd.read_csv('./input/voice.csv')
le = preprocessing.LabelEncoder()
voice["label"] = le.fit_transform(voice["label"])
voice[:]=preprocessing.MinMaxScaler().fit_transform(voice)
data_male=pd.read_csv('./output/male.csv')
data_female=pd.read_csv('./output/female.csv')



sns.set()
'''sns.FacetGrid(voice, hue="label", size=10).map(plt.scatter, "meanfun", "meanfreq").add_legend()
plt.show()
'''

#sns.despine(left=True)
'''
for i in range(0,21):
    sns.violinplot(x='label' ,y=voice.columns[i], data=voice)
    plt.show()
'''
'''
plt.title(voice.columns[0]+' data')
sns.distplot(voice.loc[voice['label'] == 0, voice.columns[0]], color= 'red', label='FEMALE',bins=200,axlabel=voice.columns[0])
sns.distplot(voice.loc[voice['label'] == 1, voice.columns[0]], color= 'blue', label='MALE',bins=200)
plt.show()
'''

sns.jointplot(x=data_male.columns[1] ,y=data_male.columns[2], data=data_male,kind="scatter",s=2,color='red')
sns.jointplot(x=data_female.columns[1] ,y=data_female.columns[2], data=data_female,kind="scatter",s=2)
plt.show()

'''
sns.heatmap(voice)
plt.show()
'''
    

