function [ s_t_r,s_t_g,s_p_r,s_p_g] = S_tp_rg(t,W0,P0,k,g,r,Start,Interval )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
%模拟算出灵敏度 S(t,r)
%4.4养猪问题 4.数学建模p19-p
r_change            =   r + 0.01*r;
dr                  =   r-r_change;
g_change            =   g + 0.01*g;
dg                  =   g-g_change;

H                   =   Harvest(t,W0,P0,k,g,r);
[M,I]               =   Find_M(t,H,Start,Interval);

H                   =   Harvest(t,W0,P0,k,g,r_change);
[M_change,I_change] =   Find_M(t,H,Start,Interval);
dM                  =   M-M_change;
dI                  =   I-I_change;
s_t_r               =   dI*r/dr/I;
s_p_r               =   dM*r/dr/M;

H                   =   Harvest(t,W0,P0,k,g_change,r);
[M_change,I_change] =   Find_M(t,H,Start,Interval);
dM                  =   M-M_change;
dI                  =   I-I_change;
s_t_g               =   dI*g/dg/I;
s_p_g               =   dM*g/dg/M;

end

