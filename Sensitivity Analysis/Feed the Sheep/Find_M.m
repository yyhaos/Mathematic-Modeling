function [ M,I ] = Find_M( t,H,Start,Interval )
%UNTITLED10 Summary of this function goes here
%   Detailed explanation goes here
%找出一个数组里的最大值 和取最大值的t
[M,I]=max(H);
M;
I=Start+Interval*(I-1);

end

