function [ H ] = Harvest( t,W0,P0,k,g,r )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
%4.4养羊问题 4.数学建模p19-p
t;

 %饲养时间
W =W0+t.*g;
P =P0+t.*r;
R =W.*P;
C =500+t.*k;
H =R-C;
end

