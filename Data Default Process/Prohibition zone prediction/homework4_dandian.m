x=[129 140   108 88 185.5 195 105.5 157.5 107.5 77 81 162 162 117.5];
y=[7.5 141.5 28 147 22.5 137.5 85.5 -6.5 -81 3 56.5 -66.5 84 -38.5];
z=[4    8    6 8 6 8 8 9 9 8 8 9 4 9];
%X1为海底高度矩阵
y=floor(y+82.5);
x=floor(x);
maxx=250;
mysize=7;
X1=zeros(maxx,maxx);
%X1{x,y}=z
for i=(1:14)
   X1(x(i),y(i))=z(i);
end
mymax=-1;
cnt=1;
while mymax~=0 && cnt<maxx*maxx
    cnt
    mymax=0;
    for i=(1:maxx)
        for j=(1:maxx)
            if X1(i,j)==0
    %             dis=0;
    %             a=0;
    %             for k=(1:14)
    %                 tem_d = d(x(k),y(k),i,j);
    %                 dis=dis + 1/tem_d;
    %                 a = a + 1/tem_d*z(k);
    %             end
                tem = mysum(X1,i,j,maxx,mysize);
                mymax = max(tem,mymax);
               % X1(i,j)=a/dis;
            end
        end
    end
    mymax;
    X2=X1;
     for i=(1:maxx)
        for j=(1:maxx)
            if X1(i,j)==0
                tem = mysum(X2,i,j,maxx,mysize);
                if mymax==1 && tem==mymax
                    X1(i,j)=suit(X2,i,j,maxx,mysize);
                    cnt=cnt+1;
                end
                if mymax-tem<mymax*0.40 && mymax>1
                    X1(i,j)=suit(X2,i,j,maxx,mysize);
                    cnt=cnt+1;
                end
            end
        end
     end
end
cnt
xx=1:maxx;
yy=1:maxx;


  % 给出加密的插值坐标
%[a1,a2,Z]=griddata(xx,yy,X1,xx,yy,'cubic');
mesh(xx,yy,10-X1)
%axis([-inf,inf,-inf,inf ,0,10])
%在坐标上进行样条插值
% 
% x=1:500;
% y
% x1=min(x);x2=max(x);
% y1=min(y);y2=max(y);
% [X,Y]=meshgrid(x1:2:x2,y1:2:y2);%给定加密网格点
% [xx,yy,zz]=griddata(x,y,z,X,Y,'cubic');
% %三次多项式插值
% mesh(xx,yy,10-zz), hold on
% %画插值曲面图
% plot3(x,y,10-z,'*'), hold off %标注观测点的高程

%plot(x,y,10-X1) 
%[xx,yy,zz]=griddata(1:500,1:500,X1,X,Y,'cubic');
%scatter3(1:500,1:500,X1)
%三次多项式插值
%[X,Y]=meshgrid(1:500,1:500)
%surf(X,Y,10-X1)
%mesh(xx,yy,10-zz), hold on
