function [ sum ] = mysum( a,i,j,maxx,mysize)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
myans=0;
for ii=(i-mysize:i+mysize)
    for jj=(j-mysize:j+mysize)
       if ii>0 && ii<maxx && jj>0 && jj<maxx 
           if a(ii,jj)>0
             myans=myans+1;
           end
       end
    end
end
sum=myans;
% if sum>0
%     sum
%     i
%     j
% end
end

