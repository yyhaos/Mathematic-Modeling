#later we choose Excel to deal with the graphs
#because the output of this program is urgly
import matplotlib.pyplot as plt
file = open('need2.txt','r')
year = []
years = []
data_ticks = []
maxn = 200000
minn = 40000
for i in range (1960,2010,10):
    year.append(i)
year.append(2009)
for j in range (1960,2010):
    years.append(j)
for s in range (minn,maxn,20000):
    data_ticks.append(s)
print(data_ticks)
print(year)

data = []
for i in range(0,50):
    data.append(0)
for line in file :
    lines = line.split()
    print(lines)
    state_name = lines[1]
        #if(lines[2]!='2009'):
            #print(lines[2]+' '+lines[3])
            #data.append(float(lines[3]))
            #continue
    data[int(lines[2])-1960]+=float(lines[3])
print(data)
plt.plot(years,data)
plt.xlim(1955,2015)
plt.xticks(year)
#plt.ylim(minn,maxn)
#plt.yticks(data_ticks)
plt.show()
data=[]
