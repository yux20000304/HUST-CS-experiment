# -*- coding: UTF-8 -*-

import pandas as pd
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE
from sklearn.preprocessing import StandardScaler
import numpy as np

array1=[89,96,98,97.6,98.6]
array2=["Naive Bayes","Naive Bayes Pro","KNN","Logistic Regression","Random Forest"]

plt.bar(range(len(array2)), array1,tick_label=array2,color='skyblue',label='Accuary')
plt.ylabel('Accuarcy')
plt.xlabel('Methods')
plt.title('Comparation between each algorithm')
plt.ylim(85,100)
plt.show()
