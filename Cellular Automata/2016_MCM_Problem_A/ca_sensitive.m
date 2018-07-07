for tk=(1:0.05:1.35)

    len_max_x=140;
    len_max_y=80;
    len_max_z=70;
    num_cell=len_max_x*len_max_y*len_max_z;
    len_cell=0.01; % unit m


    V_water=0.000001; % unit m3/s
    V_hub=num_cell*len_cell*len_cell*len_cell;
    len_cell_add=0.01;
    V_add=len_cell_add*len_cell_add*len_cell_add*1000;
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

    K=0.6 * tk; % unit W/K/m
    K_air=15 * tk; % unit W/K/m

    time_max=600;
    time_mutiple = 2;

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

        for x=(1:len_max_x)
            for y=(1:len_max_y)
                for z=(1:len_max_z)

                    %判断是否是人区域
                    if(x<person_x && y>person_y_l && y<person_y_r)
                        tem_hub(x,y,z)=36.5;
                        continue;
                    end
                    if(x<person_x_foot && y>person_y_l && y<person_y_r && z<=person_z)
                        tem_hub(x,y,z)=36.5;
                        continue;
                    end

                    %计算离出水口的距离 以算出K值
                    dis=(x-position_hot(1,1))^2+(y-position_hot(1,2))^2+(z-position_hot(1,3))^2;

                    if(dis==0)  %如果是进水口 跳过
                        continue;
                    end

                    if(tem_hub(x,y,z)>tem_initail_hot)  %如果太靠近进水口 跳过
                        continue;
                    end

                    %计算傅里叶定律里的温度改变
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

                    %计算温度改变总和
                    change_tem=(change_k/C/m_cell+tem_f*num_cell*k(dis)/k_balance)*time_mutiple;  % unit K
                    tem_hub(x,y,z) = tem_hub(x,y,z)+change_tem;

                    %统计平均水温
                    tem_average_water=tem_average_water+tem_hub(x,y,z);
                    v_water=v_water+1;
                end
            end
        end
        tem_hub(position_hot(:,1),position_hot(:,2),position_hot(:,3))=tem_initail_hot;
        if(tem_average_water/v_water>37)
            end_time=[end_time,time]
            break;
        end
    end
    tem_hub;
    finish=1
end
end_time