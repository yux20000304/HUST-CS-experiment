#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar  8 16:02:34 2020

@author: yushan
"""

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun 8th March 2020

@author: yyx
"""

import numpy as np
import pandas as pd
import sklearn.linear_model
import sklearn.tree
import sklearn.metrics
from matplotlib import pyplot as plt
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfVectorizer
import string
from nltk.corpus import wordnet
import string
from nltk import pos_tag
from nltk.corpus import stopwords
from nltk.tokenize import WhitespaceTokenizer
from nltk.stem import WordNetLemmatizer
import enchant
import re
from sklearn.linear_model import LogisticRegressionCV
from autocorrect import spell
from keras import Sequential
from keras.layers import Dense
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.model_selection import cross_val_score
from keras.utils import to_categorical


# Clean Data
def get_wordnet_pos(pos_tag):
    if pos_tag.startswith('J'):
        return wordnet.ADJ
    elif pos_tag.startswith('V'):
        return wordnet.VERB
    elif pos_tag.startswith('N'):
        return wordnet.NOUN
    elif pos_tag.startswith('R'):
        return wordnet.ADV
    else:
        return wordnet.NOUN

def check_english(text):
    d = enchant.Dict("en_US")
    english_words = []
    for word in text:
        if d.check(word):
            english_words.append(word)
    return english_words

def reduce_lengthening(text):
    pattern = re.compile(r"(.)\1{2,}")
    return pattern.sub(r"\1\1", text)


def clean_text(text):
    # lower text
    text = text.lower()
    # tokenize text and remove puncutation
    text = [word.strip(string.punctuation) for word in text.split(" ")]
    # remove words that contain numbers
    text = [word for word in text if not any(c.isdigit() for c in word)]
    # remove stop words
    stop = stopwords.words('english')
    text = [x for x in text if x not in stop]
    # remove empty tokens
    text = [t for t in text if len(t) > 0]
    # pos tag text
    pos_tags = pos_tag(text)
    # lemmatize text
    text = [WordNetLemmatizer().lemmatize(t[0], get_wordnet_pos(t[1])) for t in pos_tags]
    # remove words with only one letter
    text = [t for t in text if len(t) > 1]
    # modify mis-spelled
    text = [spell(reduce_lengthening(t)) for t in text]
    # remove non english and mis-spelled
    text = check_english(text)
    # join all
    text = " ".join(text)
    return(text)
    
#Part II
#2.1 


import sklearn.neighbors
from collections import OrderedDict

word_embeddings = pd.read_csv('glove.6B.50d.txt.zip',
                               header=None, sep=' ', index_col=0,
                               nrows=100000, compression='zip', encoding='utf-8', quoting=3)
# Build a dict that will map from string word to 50-dim vector
word_list = word_embeddings.index.values.tolist()
word2vec = OrderedDict(zip(word_list, word_embeddings.values))

x_train_df = pd.read_csv('hair_dryer_review.csv')
y_tr = pd.read_csv('hair_dryer_label.csv')


x_train_df["text"] = x_train_df["text"].apply(lambda x: clean_text(x))


def create_feature(x_train_df):
    words_vector = []
    for text in x_train_df['text']:
        vector = np.zeros(50)
        for word in text.split( ):
            try:
#                v = word2vec[word]/np.argmax(word2vec[word])
                v = word2vec[word]
                vector += v
            except:
                pass
        words_vector.append(list(vector))
    return(words_vector)
        
x_train = create_feature(x_train_df)


def check_length_train(x_train,y_tr):
    index = 0
    for i in x_train:
        if len(i) != 50:
            x_train.pop(index)
            
            y_tr.pop(index)
        index+=1
    return x_train,y_tr

def check_length_test(x_test):
    index = 0
    for i in x_test:
        if len(i) != 50:
            x_test.pop(index)
            
        index+=1
    return x_test


#logistic 
    
C_grid = np.logspace(-9, 6, 31)
logistic_train_error = []
logistic_test_error = []
x_train, y_tr = check_length_train(x_train,y_tr)
x_t, x_v, y_t, y_v = sklearn.model_selection.train_test_split(x_train, y_tr, test_size=0.2, random_state=1)

for c in C_grid:
    clf_logistic = sklearn.linear_model.LogisticRegression(random_state=0, solver='liblinear', C =c )
    clf1 = sklearn.model_selection.cross_validate(clf_logistic, x_train, y_tr, cv=3,return_train_score=True)
    logistic_train_error.append(np.average(clf1['train_score']))
    logistic_test_error.append(np.average(clf1['test_score']))
print(logistic_train_error,logistic_test_error) 
best_C = C_grid[np.argmax(np.array(logistic_test_error))] 

clf_logistic = sklearn.linear_model.LogisticRegression(random_state=0, solver='liblinear', C =best_C ).fit(x_train, y_tr)


# LOGISTIC PLOT 
plt.plot(C_grid,logistic_train_error,label='train')
plt.plot(C_grid,logistic_test_error,label='test')
#plt.ylim([0.75, 0.80])
plt.xlim([0, 0.02])
plt.xlabel("C_grid")
plt.ylabel("Average Score")
plt.legend()
plt.show()

