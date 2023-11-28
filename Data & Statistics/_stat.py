# %%
import math
import matplotlib
import os
import pandas as pd


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

def partition(data, step, str1, str2):
    
    retval = []
    retyear = []
    start = 0
    for n in range(0, 4):
        subpart = count[n] / step
        start = _sum(count, n)

        while(start <= (_sum(count, n) + count[n])):
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

# file [["salary"]]. plot(kind="hist",bins = step(0, mean(file["salary"]), 1000) , rwidth =0.8)
# file [["remote_ratio"]]. plot(kind="hist",bins = step(0, max(file["remote_ratio"]), 21) , rwidth =0.8)
# file [["salary_in_usd"]]. plot(kind="hist",bins = step(0, mean(file["salary_in_usd"]), 1000) , rwidth =0.8)
# file [["work_year"]]. plot(kind="hist",bins = step(min(file["work_year"]), max(file["work_year"]), 10) , rwidth =0.8)

file = file.sort_values (["work_year"], ascending =[1])
count = [file['work_year'].value_counts().at[i] for i in range(2020, 2024)]

strx = "work_year"
stry = "salary"
stry2 = "salary_in_usd"

stepsize = 10

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


datum = partition(_tempdata, stepsize, stry, strx)

normalized_data = {}
normalized_data [stry]    = [datum[0][i] for i in range(0, len(datum[0]))]
normalized_data [strx] = [datum[1][i] for i in range(0, len(datum[1]))]
    

# print(normalized_data)

fnormal = pd.DataFrame(data = normalized_data)

fnormal.plot(kind = "line", x = strx, y = stry)

# print(tempdata[strx])
# print(len(tempdata["salary"]))
 
# print(tempdata)

# workyear = [i for i in range(0, int(2.5))]

# print(workyear)

# file.plot(kind = "line", x = "work_year", y = "remote_ratio")


#file [["salary"]].quantile(0.1, axis = 0, numeric_only = False, interpolation='linear')



# imax = 0

# file[["salary", "remote_ratio", "salary_in_usd", "work_year"]].describe()

# file.describe().loc[['max', 'min']]

# file.describe()

# file.describe().quantile(step(0, 1, 10 + 1))



# file[["salary", "salary_in_usd", "remote_ratio"]].describe().quantile([.10, .25, .50, .75, 1.00])
# %%
