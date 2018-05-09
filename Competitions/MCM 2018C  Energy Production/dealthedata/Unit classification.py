data = []
file = open('original.txt','r')
file2 = open('4个旧能源end_use的_out.txt','w+')#the flie u want to save the data
file3 = open('target.txt','r')#the kind of data u want to get from the original data

target = []
for k in file3:
    target.append(k[0:5])
print(target)
#print(file)

for line in file:
    lines = line.split()
    #print(lines)
    #print (lines[0])
    if(lines[0] in target):
        #data.append(line)
        file2.write(line)
        continue
    

#line = fo.readline(5)
#print "读取的字符串为: %s" % (line)
print('finish')


# 关闭文件
file.close()
file2.close()
file3.close()

