# -*- coding: UTF-8 -*-
from __future__ import division
import numpy as np
import matplotlib.pyplot as plt

try:
    xrange
except NameError:
    xrange = range

def add_intercept(X_):
    m, n = X_.shape
    X = np.zeros((m, n + 1))
    X[:, 0] = 1
    X[:, 1:] = X_
    return X

def load_data(filename):
    D = np.loadtxt(filename)
    Y = D[:, 0]
    X = D[:, 1:]
    return add_intercept(X), Y

def calc_grad(X, Y, theta):
    m, n = X.shape
    grad = np.zeros(theta.shape)

    margins = Y * X.dot(theta)
    probs = 1. / (1 + np.exp(margins))
    grad = -(1./m) * (X.T.dot(probs * Y))

    return grad

def logistic_regression(X, Y):
    m, n = X.shape


    theta = np.zeros(n)
    learning_rate = 10

    i = 0
    max_training_rounds = 1000000
    fig, axes = plt.subplots(2, 2, figsize=(9, 6))
    axes = axes.ravel()
    diff = []
    while True and i <= max_training_rounds:
        i += 1
        prev_theta = theta
        grad = calc_grad(X, Y, theta)
        theta = theta  - learning_rate * (grad)
        norm = np.linalg.norm(prev_theta - theta)

        diff.append(norm)

        if i % 10000 == 0:
            print('Finished {0} iterations; Diff theta: {1}; theta: {2}; Grad: {3}'.format(
                i, norm, theta, grad))

            '''
            for j in range(m):
                if Y[j] == 1:
                    axes[int(i / 10000 - 1)].scatter(X[j][1], X[j][2], color='red')
                else:
                    axes[int(i / 10000 - 1)].scatter(X[j][1], X[j][2], color='blue')
            x = np.arange(0, 1, 0.1)
            axes[int(i/10000-1)].plot(x, -(theta[0] + theta[1] * x) / theta[2])
            '''
        if norm < 1e-15:
            print('Converged in %d iterations' % i)
            break

    #plt.xlabel('Training Rounds')
    #plt.ylabel('Theta Difference')
    #plt.plot(np.arange(i)+1,np.array(diff))

    plt.show()
    return

def main():
    print('==== Training model on data set A ====')
    Xa, Ya = load_data('data_a.txt')
    logistic_regression(Xa, Ya)

    print('\n==== Training model on data set B ====')
    Xb, Yb = load_data('data_b.txt')
    logistic_regression(Xb, Yb)

    return

if __name__ == '__main__':
    main()
