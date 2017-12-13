#make a text file which consists of quentions.

import io
from operator import eq #for compare "?"

fii=open("titles.txt","r",encoding="utf8")
for line in fii.readlines():
    title=line[:-1]
    try:
        title_real=title[1:]
        title_qna=title+"qna.txt"
        f= open(title_real,"r",encoding="utf8")
        ff=open(title_qna,"w",encoding="utf8")
    except FileNotFoundError:
        title_qna=title+"qna.txt"
        f=open(title,"r",encoding="utf8")
        ff=open(title_qna,"w",encoding="utf8")

    Qflag = 0

    for line in f.readlines():
        if line.find('-') != -1:
            if line.find('- ') != -1:
                line = line[2:] #delete '- '
            else:
                line = line[1:] #delete '-'
        
        if line.find('&') != -1:
            line = ""
            

        if line.find('?') != -1: #find question sentence
            ff.write(line)
            Qflag = 1 #flag means that next sentence will be an answer for this sentence

        elif Qflag == 1: #answer(predicted)
            if line[:-1]=="":
                Qflag = 1
            else:
                ff.write(line)
                Qflag = 0 #For finding other questions

    f.close()
    ff.close()
fii.close()