# %%
import math
import matplotlib
import os
import pandas as pd
import random

_str_ = [
    "work_year",
    "salary",
    "salary_in_usd",
    "remote_ratio"
]

strx = "work_year"
stry  = _str_[2]
stry2 = _str_[2]

STEPSIZE = 175

def _sum(x, n) -> int:
    retval = 0
    for i in range(0, n):
        retval += x[i]
        
    return retval

def absolute(x):
    if(x < 0):
        return -x
    else:
        return x

def mean(X, start, end):
    sum = float(0)
    for i in range(start, end):
        sum += X[i]

    return (sum / (end - start))

def variance(X):
    varSum = float(0)
    XMean = mean(X)


    for i in range(0, len(X)):
        varSum = varSum + ((X[i] - XMean) ** 2)

    return (varSum / len(X))

def standardDeviation(X):
    return math.sqrt(variance(X))

def step(min, max, n):
    retval = [min]
    n -= 1
    for i in range(1, n + 1):
        retval.append(min + ( i*((max - min)/n)))
        
    return retval

def partition(data, step, dx, countdx, str1, str2):
    
    retval = []
    retyear = []
    start = 0
    for n in range(0, dx):
        subpart = count[n] / step
        start = _sum(countdx, n)

        while(start <= (_sum(countdx, n) + countdx[n])):
            end = (start + subpart)
            
            if (end >= len(data[str1])): end = len(data[str1])
            if (start == end): break

            retval.append(mean(data[str1], int(start), int(end)))
            retyear.append(data[str2][int(start)])
       
            start = end
            
        
    return [retval, retyear]
        

                
            
            
file = pd.read_csv("salaries.csv")

datashape = [file.shape[0], file.shape[1]]
filesize = os.path.getsize("salaries.csv")

# print(filesize)

# file [["salary_in_usd"]]. plot(kind="hist",
#                                bins = step(0, int( max(file["salary_in_usd"]) ), 300),
#                                rwidth =0.8)



# file [["salary"]]. plot(kind="hist",bins = step(0, mean(file["salary"]), 1000) , rwidth =0.8)
# file [["remote_ratio"]]. plot(kind="hist",bins = step(0, max(file["remote_ratio"]), 21) , rwidth =0.8)
# file [["salary_in_usd"]]. plot(kind="hist",bins = step(0, max(file["salary_in_usd"], 1000)) , rwidth =0.8)
# file [["work_year"]]. plot(kind="hist",bins = step(min(file["work_year"]), max(file["work_year"]), 10) , rwidth =0.8)

# print( int( max(file["salary"]) ) + 90)

file = file.sort_values (["work_year"], ascending =[0])
count = [file['work_year'].value_counts().at[i] for i in range(2020, 2024)]





_tempdata = {}
_tempdata [strx] = [0 for i in range(0, file.shape[0])]
_tempdata [stry] = [0 for i in range(0, file.shape[0])]
                       


for n in range(2019, 2023):
    year = float(n)
    subval = float((1 / count[n - 2019]))
    end = _sum(count, n - 2018)
    i = _sum(count, n - 2019)

    while (i < end):
        _tempdata[strx][i] = year
        year += subval
        i += 1

for n in range(0, len(file[stry])):
    _tempdata[stry][n] = file[stry2][n]


datum = partition(_tempdata, STEPSIZE, 2023 - 2019, count, stry, strx)

normalized_data = {}
normalized_data [stry] = [datum[0][i] for i in range(0, len(datum[0]))]
normalized_data [strx] = [datum[1][i] for i in range(0, len(datum[1]))]
    

# print(normalized_data)

fnormal = pd.DataFrame(data = normalized_data)


# file.plot(kind = "line", x = "remote_ratio", y = "remote_ratio")

size = len(file["remote_ratio"])



_remote_ratio = [file["remote_ratio"][n] for n in range(0, size)]
for i in range(0, size):
    _remote_ratio[i] *= random.random()


file.plot(kind="scatter", x= "work_year", y= "remote_ratio")





_qnt_data = {}
_qnt_data ["work_year"]     = fnormal["work_year"]
_qnt_data ["remote_ratio"]  = _remote_ratio
_qnt_data ["salary"]        = file["salary"]
_qnt_data ["salary_in_usd"] = file["salary_in_usd"]
qnt_data = pd.DataFrame(data = _qnt_data)

_str_ = ["work_year", "salary", "salary_in_usd", "remote_ratio"]

for a in range(0, len(_qnt_data)):
    for b in range(a, len(_qnt_data)):
        if(a == b): pass
        else:
            corr = file[_str_[a]].corr(file[_str_[b]])
            qnt_data.plot(kind="scatter", x=_str_[a], y= _str_[b])
            qnt_data.plot(kind="scatter", x=_str_[b], y= _str_[a])

            if (corr > 0.5):
                print(_str_[a] + " berbanding lurus dengan " + _str_[b])
            elif (corr < -0.5):
                print(_str_[a] + " berbanding terbalik dengan " + _str_[b])
            else:
                print(_str_[a] + " tidak berkolerasi dengan " + _str_[b])

qnt_data.corr(method = "pearson")
qnt_data.corr(method = "kendall")













# file.plot(kind = "line", x = "work_year", y = "remote_ratio")


#file [["salary"]].quantile(0.1, axis = 0, numeric_only = False, interpolation='linear')



# imax = 0

# file[["salary", "remote_ratio", "salary_in_usd", "work_year"]].describe()

# file.describe().loc[['max', 'min']]

# file.describe()

# file.describe().quantile(step(0, 1, 10 + 1))



# file[["salary", "salary_in_usd", "remote_ratio"]].describe().quantile([.10, .25, .50, .75, 1.00])
# %%
