%初始化
Start=0;
End=20;
Interval =0.0001;
t=[Start:Interval:End];

%初始条件
W0 =100; %猪的初始重量     公斤
P0 =7.5;%猪的初始价格     元/公斤
k =7.1;  %每天饲料花费     元/天
g =2 ; %w的增加速率     公斤/天
r =-0.06;  %价格变化的速率    元/天

H=Harvest(t,W0,P0,k,g,r);   %找出最大值和最好天数
[M,I]=Find_M(t,H,Start,Interval);
tar_M=M; %第三部分要用

%更改初始条件
k =8;  %每天饲料花费     元/天
g =2.2 ; %w的增加速率     公斤/天
H2=Harvest(t,W0,P0,k,g,r);  %找出最大值和最好天数
[M2,I2]=Find_M(t,H2,Start,Interval);

plot(t,H,'red',t,H2,'green');

%灵敏度分析
k =7.1;  %每天饲料花费     元/天
g =2 ; %w的增加速率     公斤/天
%[s_t_r,s_t_g,s_p_r,s_p_g]=S_tp_rg(t,W0,P0,k,g,r,Start,Interval)
%[s_t_k,s_p_k]   =   S_tp_k(t,W0,P0,k,g,r,Start,Interval)

%找出最小生长速率
k =8;  %每天饲料花费     元/天
for g_change=(2:0.001:3)
    H3=Harvest(t,W0,P0,k,g_change,r);   %找出最大值和最好天数
    [M,I]=Find_M(t,H3,Start,Interval);
    if tar_M<=M
        g_change
       plot(t,H,'red',t,H3,'green');
        [s_t_r,s_t_g,s_p_r,s_p_g]=S_tp_rg(t,W0,P0,k,g_change,r,Start,Interval)
        [s_t_k,s_p_k]   =   S_tp_k(t,W0,P0,k,g_change,r,Start,Interval)
        break;
    end
   
end
