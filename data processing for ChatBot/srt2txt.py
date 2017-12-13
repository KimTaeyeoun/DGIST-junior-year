#change srt file to text ONLY file

import io

f = io.open('HarryPotterEx.srt', 'r')
fmid = io.open('HarryPotterMid.txt', 'w', encoding="utf8") #different lines

lineN = 0
for line in f.readlines():
    #that is ONE sentence...;
    if lineN == 0:
        fmid.write('<br>'+line[:line.index('<br>'+'1'+'<br>')]+'\n')
        lineN = lineN + 1
    while(line.find('<br>'+str(lineN + 1)+'<br>') != -1):
        fmid.write(line[line.index('<br>'+str(lineN)+'<br>'):line.index('<br>'+str(lineN + 1)+'<br>')]+'\n')
        lineN = lineN + 1
        if lineN > 1293:
            break

f.close()
fmid.close()

fmid = io.open('HarryPotterMid.txt', 'r', encoding="utf8")
ff = io.open('Harry.txt', 'w', encoding="utf8")  #output

for newline in fmid.readlines():
    #there is always <br>!
    for k in range(0,3):
        newline = newline[newline.index('<br>')+4:] #delete all words before third <br>
    if newline[-5:-1].find('<br>') != -1:
        newline = newline[:len(newline)-5] #delete last <br>
    ff.write(newline.replace('<br>', '\n')+'\n')

fmid.close()
ff.close()