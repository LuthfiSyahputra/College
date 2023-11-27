
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





data = [2, 43, 5, 4]
sorting.quickSort(data, 0, len(data) - 1)



for i in range(0, 4):
    print(data[i])
# print(mean(data))

