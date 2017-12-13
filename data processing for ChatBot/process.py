import sys

total = len(sys.argv)
if total != 3:
    print ("USE: ./process.py input_file output_file")
    exit(0)

input_file_name = sys.argv[1]
output_file_name = sys.argv[2]

f_out = open(output_file_name, 'w')

with open(input_file_name) as f_in:
    #remove blank lines
    lines = filter(None, (line.rstrip() for line in f_in))

    #remove unnecessary lines and write it to a new file
    for line in lines:
        if input_file_name.endswith('.smi'):
            # <SAMI>, <HEAD>, <TITLE>, <BODY>, <SYNC Start=1124> 
            if line.startswith('<') or line.startswith('{') or line.startswith('#'):
                continue
            #    color:white;
            if line.endswith(';') or line.endswith('}') or line.endswith('-->'):
                continue
            #</SAMI>, </BODY>
            if line.endswith('BODY>') or line.endswith('SAMI>'):
                continue
            if line.endswith('<br>'):
                line = line[:-4]
                line = line + ' '
                f_out.write(line)
                continue
        if input_file_name.endswith('.srt'):
            # for srt 
            if line.isdigit() and len(line) < 4:
                continue
            # 00:00:12,340 
            if line.startswith('0'):
                continue
            if line.startswith('<font'):
                continue
        f_out.write(line + '\r\n')

f_in.close()
f_out.close()