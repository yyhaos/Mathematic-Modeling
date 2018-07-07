function [ k_ans ] = k( dis )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
if(dis==0)
   dis=1; 
end
k_ans = 1/((dis)^(0.25));

end

