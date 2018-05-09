function [ myans ] = suit( aa,i,j,maxx,mysize)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
temd=0;
dis=0;
a=0;
for ii=(i-mysize:i+mysize)
    for jj=(j-mysize:j+mysize)
       if ii>0 && ii<maxx && jj>0 && jj<maxx 
           if aa(ii,jj)>0 
                temd = d(ii,jj,i,j);
                dis=dis + 1/temd;
                a = a + 1/temd*aa(ii,jj);
           end
       end
    end
end
myans=a/dis;


end

