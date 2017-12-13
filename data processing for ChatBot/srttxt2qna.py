#make a text file which consists of quentions.

import io
from operator import eq #for compare "?"

f = io.open("Harry.txt", "r", encoding="utf8")
ff = io.open("HarryQ.txt", "w", encoding="utf8")

Qflag = 0

for line in f.readlines():
    if line.find('-') != -1:
        if line.find('- ') != -1:
            line = line[2:] #delete '- '
        else:
            line = line[1:] #delete '-'
    
    if line.find('?') != -1: #find question sentence
        print(line)
        Qflag = 1 #flag means that next sentence will be an answer for this sentence
        
    elif Qflag == 1: #answer(predicted)
        print(line)
        Qflag = 0 #For finding other questions

f.close()
ff.close()