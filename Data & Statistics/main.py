
import math
import sorting
import csv_man


def absolute(x):
    if(x < 0):
        return -x
    else:
        return x

def mean(X):
    sum = float(0)
    for i in range(0, len(X)):
        sum += X[i]

    return (sum / len(X))

def variance(X):
    varSum = float(0)
    XMean = mean(X)


    for i in range(0, len(X)):
        varSum = varSum + ((X[i] - XMean) ** 2)

    return (varSum / len(X))

def standardDeviation(X):
    return math.sqrt(variance(X))

def _strseek(collection, str):
    if(len(str) == 0): return -2
    for i in range(0, len(collection)):
        if(collection[i] == str): return i
    return -1

def qualitative_count(data, n):
    frequency = []

    for i in range(0, n):
        retval = _strseek(category, data[i])
        if(retval == -1) 


def step()


a = csv_man.csv("salaries.csv", ",", 1000)
col = a.getncol(4, 1000)

csv_man.strtoint(col)

print(mean(col))
