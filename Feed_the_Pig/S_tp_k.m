function [s_t_k,s_p_k] = S_tp_k(t,W0,P0,k,g,r,Start,Interval )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
%模拟算出灵敏度 S(t,r)
%4.4养猪问题 4.数学建模p19-p
k_change            =   k + 0.01*k;
dk                  =   k-k_change;

H                   =   Harvest(t,W0,P0,k,g,r);
[M,I]               =   Find_M(t,H,Start,Interval);

H                   =   Harvest(t,W0,P0,k_change,g,r);
[M_change,I_change] =   Find_M(t,H,Start,Interval);
dM                  =   M-M_change;
dI                  =   I-I_change;
s_t_k               =   dI*k/dk/I;
s_p_k               =   dM*k/dk/M;

end
