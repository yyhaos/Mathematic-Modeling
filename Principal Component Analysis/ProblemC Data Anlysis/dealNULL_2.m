starti=2;
startj=2;
maxi=75;
maxj=7803;
BeforeNull(2,16)
ct=0;
ct2=0;
ct3=0;
for i=(starti:1:starti+maxi) %line
    cont=0;   
    cnt=0;
    average=0;
    for j=(startj:1:startj+maxj) %arrow
        if(isnan(afterNull(j,i)))
            continue;
        else
            cnt=cnt+1;
            average=average+afterNull(j,i);
        end
    end
    average=average/cnt;
    for j=(startj:1:startj+maxj) %arrow
        if(isnan(afterNull(j,i)))
            afterNull(j,i)=average;
        end
    end
end