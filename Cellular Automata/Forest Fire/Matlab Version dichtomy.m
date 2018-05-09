%3.29 : use dichtomy to conculate the min q that can burn the forest over;
%q = the probability that a tree be lighted near a burning tree ; burn the forest over = NUM_onceburned >= 0.9*forest_size
%NUM_onceburned = initiate the number of points where trees thst are burned for the first time

close all; 
clc;
clear;
figure;
N=300;%size of forest
K=round(N/2);%(K,K)set the outbreak point of fire initially
p=0.0001;%the probability of an tree grows in an open area
q=0.4;%the probability that a tree be lighted near a burning tree
S_cont=ones(N+2,N+2); %to count the number of points where trees thst are burned for the first time
S=ones(N);
S(K,K)=2;%(K,K)set the outbreak point of fire initially
Sk=zeros(N+2);
Sk(2:N+1,2:N+1)=1;%the forest is full of trees( , 0 = open area , 2 = burning tree)
Sk(K,K)=2;%(K,K)set the outbreak point of fire initially
%draw pic
C=zeros(N+2,N+2,3);
R=zeros(N+0);
G=zeros(N+0);
R(S==2)=1;
G(S==1)=1;
C(2:N+1,2:N+1,1)=R;% 2 = burning tree
C(2:N+1,2:N+1,2)=G;%1=tree
ti=0;

%NUMs to conut
NUM_burning=1;%initiate the number of burning trees
NUM_burned=0;%initiate the number of burned trees
NUM_open=0;%initiate the number of the points of open area
NUM_onceburned=0;%initiate the number of points where trees thst are burned for the first time

%to find out the threhold of q which can promise most of the points have been on fire
left=0;
right=1;
mid=(right+left)/2.0;
%using dichtomy

%before the fire ends
while(right-left>0.0001)
    flag=0;
    i=5;
    q=mid;
    while(i>0)
        Sk=zeros(N+2);
        Sk(2:N+1,2:N+1)=1;%the forest is full of trees( , 0 = open area , 2 = burning tree)
        Sk(K,K)=2;%(K,K)set the outbreak point of fire initially
        i=i-1;
        NUM_burning=1;
        S_cont=ones(N+2,N+2); %to count the number of points where trees thst are burned for the first time
        while NUM_burning>0
            %NUM_burning;
            ti=ti+1;
            St=Sk;
            %update NUMs
            NUM_burned=NUM_burned+sum(Sk(:)==2);
            NUM_burning=NUM_burning-sum(Sk(:)==2);
            NUM_onceburned=sum(S_cont(:)==0);
            %when the tree was on fire
            St(Sk==2)=0;
            %there is a happy tree
            Su=zeros(N+2);
            Sf=Sk;
            Sf(Sf<1.5)=0;
            Sf=Sf/2;
            Su(2:N+1,2:N+1)=Sf(1:N+0,1:N+0).*(rand(N)<q)+Sf(1:N+0,2:N+1).*(rand(N)<q)+Sf(1:N+0,3:N+2).*(rand(N)<q)+Sf(2:N+1,1:N+0).*(rand(N)<q)+Sf(2:N+1,3:N+2).*(rand(N)<q)+Sf(3:N+2,1:N+0).*(rand(N)<q)+Sf(3:N+2,2:N+1).*(rand(N)<q)+Sf(3:N+2,3:N+2).*(rand(N)<q);
            St((Su>0.5)&(St==1))=2;
            
            NUM_burning=NUM_burning+sum(St(:)==2);
            
            S_cont(St(:)==2)=0;%when the point has been on fire give it a label

            Se=Sk(2:N+1,2:N+1);
            Se(Se<0.5)=4;
            Se(Se<3)=0;
            Se(Se>3)=1;
            St(2:N+1,2:N+1)=St(2:N+1,2:N+1)+Se.*(rand(N+0)<p);
            Sk=St; 
            NUM_open=sum(Sk(:)==1);
            R=zeros(N+2);
            G=zeros(N+2);
            R(Sk==2)=1;
            G(Sk==1)=1;
            C(:,:,1)=R;
            C(:,:,2)=G;
            NUM_onceburned;
        end
        if(NUM_onceburned>0.9*N*N) 
            flag=flag+1;
        end
        %flag
    end
    if(flag<3)
        left=mid;
        mid=(left+right)/2.0;
        flag=0;
    else
        right=mid;
        mid=(left+right)/2.0;
        flag=0;
    end
    mid
end
mid



