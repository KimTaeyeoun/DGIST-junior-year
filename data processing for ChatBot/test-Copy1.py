fii=open("title_real.txt","r", encoding="utf8")
for line in fii.readlines():
    if line.endswith(".smi"):
        continue
    else:
        title= line.strip().split("\n")
        title[0]=title[0][1:]
        print(title)
        title_smi=title[0]
        title_txt=title[0]+".txt"

        f= open(title_smi,"r")
        fi=open(title_txt,"w",encoding="utf8")
        
        if title_smi.find('smi')!=-1:

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
            print(title[0]+" done!")
            
        else:
            continue