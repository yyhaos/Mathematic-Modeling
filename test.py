import numpy as np

max_size=4
initial_tem=20
max_time=500
heat_tem=100
A=0.0004
K1=0.6 #water
K2=0.010 #air
air_tem=20
heat_point=[max_size/2,max_size/2,max_size-1]
C=4.2
M=8
dx=0.02
v=initial_tem * np.ones((max_size,max_size,max_size))
print(v)
for time in range(max_time):
    print(time)
    if time == 0:
        v[(int)(heat_point[0]),(int)(heat_point[1]),(int)(heat_point[2])]=heat_tem
        print(v[(int)(heat_point[0]),(int)(heat_point[1]),(int)(heat_point[2])])
    else:
        tem_v=np.ones((max_size,max_size,max_size))
        for x in range(max_size):
            for y in range(max_size):
                for z in range(max_size):
                    q_change=0
                    if(x>0):
                       q_change += (v[x-1,y,z]-v[x,y,z])*A *K1/dx
                    if(y>0):
                        q_change += (v[x,y-1,z]-v[x,y,z])*A *K1/dx
                    if(z>0):
                        q_change += (v[x,y,z-1]-v[x,y,z])*A *K1/dx
                    if(x<max_size-1):
                        q_change += (v[x+1,y,z]-v[x,y,z])*A *K1/dx
                    if(y<max_size-1):
                        q_change += (v[x,y+1,z]-v[x,y,z])*A *K1/dx
                    if(z<max_size-1):
                        q_change += (v[x,y,z+1]-v[x,y,z])*A *K1/dx
                    if(z==max_size-1):
                        q_change += (air_tem-v[x,y,z])*A *K1
                    tem_v_change=q_change/C/M
                    #print(tem_v_change)
                    tem_v[x,y,z]=tem_v_change+v[x,y,z]
        tem_v[(int)(heat_point[0]),(int)(heat_point[1]),(int)(heat_point[2])]=heat_tem
        v=tem_v
print(v)
        #draw(v)
       
