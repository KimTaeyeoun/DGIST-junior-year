import io

fii=io.open("title_real.txt","r", encoding="utf8")
for line in fii.readlines():
    if line.endswith(".smi"):
        continue
        
    elif line.find('.smi')!=-1:
        title= line.strip().split("\n")
        print(title)
        title_smi=title[0]+".smi"
        title_txt=title[0]+".txt"
        
        try:
            f = io.open(title_smi,"r")
            fi = io.open(title_txt,"w",encoding="utf8")
            print(f)
            try:
                for line in f.readlines():

                    if line.startswith('<font'):
                        line = line[19:]

                        if line.find('<br>')!=-1:
                            line = line[:-5]
                            line=line+'\n'

                        fi.write(line)

                    elif line.find('<br>')!=-1:
                        line = line[:-5]
                        line = line + '\n'

                        fi.write(line)

                    elif line.startswith('<')==False:
                        if line.find('{')==-1 and line.find('>')==-1 and line.find('smi')==-1 and line.find('modified')==-1 and line.find('#')==-1 and line.find(';')==-1: 

                            fi.write(line)
                f.close()
                fi.close()
                print(title_smi, " Done!")
            except UnicodeDecodeError:
                print("Unicode erro in ", title_smi)
        except FileNotFoundError:
            continue
                
        
    elif line.endswith(".srt"):
        continue
    elif line.find(".srt")!=-1:
        title= line.strip().split("\n")
        print(title)
        title_srt=title[0]+".srt"
        title_txt1=title[0]+"N.txt"
        title_txt2=title[0]+".txt"
        
        try:
            f = io.open(title_srt, 'r')
            fmid = io.open(title_txt1, 'w', encoding="utf8") #different lines

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

            fmid = io.open(title_txt1, 'r', encoding="utf8")
            ff = io.open(title_txt2, 'w', encoding="utf8")  #output

            for newline in fmid.readlines():
                #there is always <br>!
                for k in range(0,3):
                    newline = newline[newline.index('<br>')+4:] #delete all words before third <br>
                if newline[-5:-1].find('<br>') != -1:
                    newline = newline[:len(newline)-5] #delete last <br>
                ff.write(newline.replace('<br>', '\n')+'\n')

            fmid.close()
            ff.close()
            print(title_srt," Done!")
        except FileNotFoundError:
            continue
        
fii.close()