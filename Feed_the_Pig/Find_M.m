function [ M,I ] = Find_M( t,H,Start,Interval )
%UNTITLED10 Summary of this function goes here
%   Detailed explanation goes here
%�ҳ�һ������������ֵ ��ȡ���ֵ��t
[M,I]=max(H);
M;
I=Start+Interval*(I-1);

end

