len_max_x=140;
len_max_y=80;
len_max_z=70;
num_cell=len_max_x*len_max_y*len_max_z;
len_cell=0.01; % unit m


V_water=0.000001; % unit m3/s
V_hub=num_cell*len_cell*len_cell*len_cell;
V_add=len_cell*len_cell*len_cell*1000;
C=4.2; % unit J/g/K
p_water=1000000; % unit g/m^3
m_cell=len_cell*len_cell*len_cell*p_water; % unit g
tem_hub=ones(len_max_x,len_max_y,len_max_z);
tem_initail_cold=20;
tem_initail_hot=50;
tem_initail_air=20;
position_hot=[  len_max_x,len_max_y,len_max_z
                len_max_x,len_max_y,len_max_z-1
                len_max_x,len_max_y,len_max_z-2
                len_max_x,len_max_y,len_max_z-3
                len_max_x,len_max_y,len_max_z-4
                len_max_x,len_max_y,len_max_z-5
                len_max_x,len_max_y,len_max_z-6
                len_max_x,len_max_y,len_max_z-7
%                len_max_x/2,len_max_y/2,len_max_z-1
%                len_max_x/2,len_max_y/2,len_max_z-2
%                len_max_x/2,len_max_y/2,len_max_z-3
%                len_max_x/2,len_max_y/2,len_max_z-4
%               len_max_x/2,len_max_y/2,len_max_z-5
%               len_max_x/2,len_max_y/2,len_max_z-6
%               len_max_x/2,len_max_y/2,len_max_z-7
%               len_max_x/2,len_max_y/2,len_max_z-8
                ];
position_out=[1,1,1];

person_y_l=20;
person_y_r=60;
person_x=30;
person_x_foot=110;
person_z=20;
k_balance=0;
for x=(1:len_max_x)
    for y=(1:len_max_y)
        for z=(1:len_max_z)
            dis=(x-position_hot(1,1))^2+(y-position_hot(1,2))^2+(z-position_hot(1,3))^2;
            if(dis==0)
                continue;
            end
            if(x<person_x && y>person_y_l && y<person_y_r)
                continue;
            end
            if(x<person_x_foot && y>person_y_l && y<person_y_r && z<=person_z)
                continue;
            end
            k_balance=k_balance+k(dis);
        end
    end
end
% f_balance=f_balance*num_cell;
tem_hub=tem_initail_cold*tem_hub;

K=0.6; % unit W/K/m
K_air=150; % unit W/K/m

time_max=300;
time_mutiple = 2;

%draw gif
set(0,'DefaultFigureVisible', 'off')
f=getframe(gcf);  
imind=frame2im(f);
[imind,cm] = rgb2ind(imind,256);
imwrite(imind,cm,'test.gif','GIF', 'Loopcount',inf,'DelayTime',1);

for time = (1:time_max) % unit s
    if(mod(time,10)==0)
        time
    end
    tem_hub_pre=tem_hub;
    tem_hub_pre(position_hot(:,1),position_hot(:,2),position_hot(:,3))=tem_initail_hot;
    tem_average_water=0;
    v_water=0;
    tem_out=tem_hub_pre(position_out(1,1),position_out(1,2),position_out(1,3));
    tem_f=(tem_initail_hot-tem_out)*V_add/V_hub;
    if(time>300 && tem_hub(fix(len_max_x/2),fix(len_max_y/2),fix(len_max_z/2))>37 )
        tem_f=0;
    end
    for x=(1:len_max_x)
        for y=(1:len_max_y)
            for z=(1:len_max_z)
                if(x<person_x && y>person_y_l && y<person_y_r)
                    tem_hub(x,y,z)=36.5;
                    continue;
                end
                if(x<person_x_foot && y>person_y_l && y<person_y_r && z<=person_z)
                    tem_hub(x,y,z)=36.5;
                    continue;
                end
                dis=(x-position_hot(1,1))^2+(y-position_hot(1,2))^2+(z-position_hot(1,3))^2;
                if(dis==0)
                    continue;
                end
                if(tem_hub(x,y,z)>tem_initail_hot)
                    continue;
                end
                change_k=0;
                if(x>1)
                    change_k=change_k-K*(tem_hub_pre(x,y,z)-tem_hub_pre(x-1,y,z));
                end
                if(y>1)
                    change_k=change_k-K*(tem_hub_pre(x,y,z)-tem_hub_pre(x,y-1,z));
                end
                if(z>1)
                    change_k=change_k-K*(tem_hub_pre(x,y,z)-tem_hub_pre(x,y,z-1));
                end
                if(x<len_max_x)
                    change_k=change_k-K*(tem_hub_pre(x,y,z)-tem_hub_pre(x+1,y,z));
                end
                if(y<len_max_y)
                    change_k=change_k-K*(tem_hub_pre(x,y,z)-tem_hub_pre(x,y+1,z));
                end
                if(z<len_max_z)
                    change_k=change_k-K*(tem_hub_pre(x,y,z)-tem_hub_pre(x,y,z+1));
                end
                if(z==len_max_z)
                    change_k=change_k-K_air*(tem_hub_pre(x,y,z)-tem_initail_air);
                end
               
                change_k=(change_k*len_cell); % unit W
                change_tem=(change_k/C/m_cell+tem_f*num_cell*k(dis)/k_balance)*time_mutiple;  % unit K
                tem_hub(x,y,z) = tem_hub(x,y,z)+change_tem;
                tem_average_water=tem_average_water+tem_hub(x,y,z);
                v_water=v_water+1;
            end
        end
    end
    tem_hub(position_hot(:,1),position_hot(:,2),position_hot(:,3))=tem_initail_hot;
    
    %draw gif
    [y,x,z] = meshgrid(1:1:len_max_y,1:1:len_max_x,1:1:len_max_z);
%     [x,y,z] = ndgrid(1:1:len_max_x,1:1:len_max_y,1:1:len_max_z);
    xs = linspace(1,len_max_x,len_max_x);
%     xs = xs([fix(len_max_x/4),fix(len_max_x/4*2),fix(len_max_x/4*3)]);
    xs = xs([fix(len_max_x/3*2),fix(len_max_x/3*1),len_max_x]);
    ys = linspace(1,len_max_y,len_max_y);
    ys = ys([fix(len_max_y/2),len_max_y]);
    zs = linspace(1,len_max_z,len_max_z);
    zs = zs([1,fix(len_max_z/4*2)]);
%     set(gca,'DataAspectRatio',[len_max_x len_max_y len_max_z]);
    slice(y,x,z,tem_hub,ys,xs,zs);
    axis equal;
    xlabel("X");
    ylabel("Y");
    zlabel("Z");
    colorbar
    
    if(time>300 && tem_hub(fix(len_max_x/2),fix(len_max_y/2),fix(len_max_z/2))>37 )
        str=['时间：',num2str(time),' 平均水温：',num2str(tem_average_water/v_water),' 水龙头：关 '];
    else
        str=['时间：',num2str(time),' 平均水温：',num2str(tem_average_water/v_water),' 水龙头：开 '];
    end
    title(str)
    %shading interp
    drawnow%画出动画线
    f=getframe(gcf);  
    imind=frame2im(f);
    [imind,cm] = rgb2ind(imind,256);
    imwrite(imind,cm,'test.gif','GIF','WriteMode','append','DelayTime',0.1);

    if(time==1)
        imwrite(frame2im(getframe(gcf)),'result_1.jpg'); 
    end
    if(time==300)
        imwrite(frame2im(getframe(gcf)),'result_300.jpg');
    end
end
tem_hub;
finish=1