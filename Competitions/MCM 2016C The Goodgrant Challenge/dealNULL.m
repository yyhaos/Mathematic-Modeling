starti=2;
startj=2;
maxi=114;
maxj=7803;
BeforeNull(2,16)
ct=0;
ct2=0;
ct3=0;
for i=(starti:1:starti+maxi) %line
    cont=0;
    for j=(startj:1:startj+maxj) %arrow
        if(isnan(BeforeNull(j,i)))
            cont=cont+1;
        end
    end
    if(cont>maxj/2)
        i
        ct=ct+1;
    else if(cont>maxj/10)
        ct2=ct2+1;
        else
        ct3=ct3+1;
        end
    end
end
ct
ct2
ct3