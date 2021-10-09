#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar  8 13:09:45 2020

@author: yushan
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

import seaborn as sns
from sklearn.model_selection import cross_validate

#sns.countplot(x='is_positive_sentiment', data=y_train_df)


#x_train_df['Word Count'] = [len(Text.split()) for Text in x_train_df['text']]
#x_train_df['Uppercase Char Count'] = [sum(char.isupper() for char in Text)  for Text in x_train_df['text']]                           
#x_train_df['Special Char Count'] = [sum(char in string.punctuation for char in Text) for Text in x_train_df['text']]   
#   
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

def bag_of_words(x_train_df):
    vectorizer = TfidfVectorizer()
    corpus = x_train_df['text']
    X = vectorizer.fit_transform(corpus)
    vectorizer.get_feature_names()
    feature_train  = X.toarray()
    
    
    return feature_train


def bag_of_words_large(x_train_df):
    bigram_vectorizer = TfidfVectorizer(ngram_range=(1, 2),token_pattern=r'\b\w+\b', min_df=1)
#    analyze = bigram_vectorizer.build_analyzer()
    corpus = x_train_df['text']
    feature_train = bigram_vectorizer.fit_transform(corpus).toarray()
    
    return feature_train


def generate_train_and_test_data(x_train_df,large):

    x_train_df["text"] = x_train_df["text"].apply(lambda x: clean_text(x))
    if large != 'large':
        x_train= bag_of_words(x_train_df)
    else:
         x_train= bag_of_words_large(x_train_df)
    return x_train



#building the neural net
from keras import Sequential
from keras.layers import Dense
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.model_selection import cross_val_score
from keras.utils import to_categorical


    
x_train_df = pd.read_csv('hair_dryer_review.csv')
y_train_df = pd.read_csv('hair_dryer_label.csv')


# 1.2 LOGISTIC REGRESSION
y_tr = y_train_df.to_numpy()
# RUN TWICE
x_train = generate_train_and_test_data(x_train_df,'large')


C_grid = np.logspace(-9, 6, 31)
logistic_train_error = []
logistic_test_error = []
for c in C_grid:
    clf_logistic = sklearn.linear_model.LogisticRegression(random_state=0, solver='liblinear', C =c )
    clf1 = sklearn.model_selection.cross_validate(clf_logistic, x_train, y_tr, cv=3,return_train_score=True)
    logistic_train_error.append(np.average(clf1['train_score']))
    logistic_test_error.append(np.average(clf1['test_score']))
print(logistic_train_error,logistic_test_error) 
best_C = C_grid[np.argmax(np.array(logistic_test_error))] 
# best_C = 315227.77
clf_logistic = sklearn.linear_model.LogisticRegression(random_state=0, solver='liblinear', C =best_C ).fit(x_train, y_tr)

# LOGISTIC PLOT 
plt.plot(C_grid,logistic_train_error,label='train')
plt.plot(C_grid,logistic_test_error,label='test')
#plt.xlim([0, 400000])
plt.xlabel("C_grid")
plt.ylabel("Average Score")
plt.legend()
plt.show()























