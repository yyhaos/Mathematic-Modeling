%��ʼ��
Start=0;
End=20;
Interval =0.0001;
t=[Start:Interval:End];

%��ʼ����
W0 =100; %��ĳ�ʼ����     ����
P0 =7.5;%��ĳ�ʼ�۸�     Ԫ/����
k =7.1;  %ÿ�����ϻ���     Ԫ/��
g =2 ; %w����������     ����/��
r =-0.06;  %�۸�仯������    Ԫ/��

H=Harvest(t,W0,P0,k,g,r);   %�ҳ����ֵ���������
[M,I]=Find_M(t,H,Start,Interval);
tar_M=M; %��������Ҫ��

%���ĳ�ʼ����
k =8;  %ÿ�����ϻ���     Ԫ/��
g =2.2 ; %w����������     ����/��
H2=Harvest(t,W0,P0,k,g,r);  %�ҳ����ֵ���������
[M2,I2]=Find_M(t,H2,Start,Interval);

plot(t,H,'red',t,H2,'green');

%�����ȷ���
k =7.1;  %ÿ�����ϻ���     Ԫ/��
g =2 ; %w����������     ����/��
%[s_t_r,s_t_g,s_p_r,s_p_g]=S_tp_rg(t,W0,P0,k,g,r,Start,Interval)
%[s_t_k,s_p_k]   =   S_tp_k(t,W0,P0,k,g,r,Start,Interval)

%�ҳ���С��������
k =8;  %ÿ�����ϻ���     Ԫ/��
for g_change=(2:0.001:3)
    H3=Harvest(t,W0,P0,k,g_change,r);   %�ҳ����ֵ���������
    [M,I]=Find_M(t,H3,Start,Interval);
    if tar_M<=M
        g_change
       plot(t,H,'red',t,H3,'green');
        [s_t_r,s_t_g,s_p_r,s_p_g]=S_tp_rg(t,W0,P0,k,g_change,r,Start,Interval)
        [s_t_k,s_p_k]   =   S_tp_k(t,W0,P0,k,g_change,r,Start,Interval)
        break;
    end
   
end
