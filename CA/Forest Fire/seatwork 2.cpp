#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
//3.26  Simulate the formation and spread of forest fire by CA
//3.27  update    :   fix bugs , a new way show result ('T' = tree, '#' = burning, ' ' = open area , add count(NUM_open NUM_trees NUM_burning)
char change(int a)
{
    char ans;
    if(a==0)
        ans = ' ';
    else if(a==1)
        ans = 'T';
    else
        ans = '#';
    return ans;
}

int main ()
{
    double p=0.3, f=0.005, maxn=RAND_MAX;  //p=probability of growing a new tree in open area, f=probability of lighting a tree up
    int t=0, N=25, M=30, i, j, num[2];               //t=time(a specific unit of time, N=max time, M=max area
    int s[N+5][M+5][M+5];                   //s=the forest:0==open area, 1==a tree(or tree area), 2==a burning tree(burning area)
    memset(s,0,sizeof(s));                  //initialization
    for (i=1 ; i<= M;i++)
        for(j=1;j<=M;j++)
        {
            s[t][i][j]=1;                   //initialization all trees started
            //s[t][i][j]=rand()%3;          //initialization random started
        }
    while(t<=N)                             //main part
    {
        system("CLS");
        printf("t=%d NUM_open=%d NUM_trees=%d NUM_burning=%d\n",t+1,num[0],num[1],num[2]);
        for(i=1;i<=M;i++)
        {
            for(j=1;j<=M;j++)
            {
                printf("%c",change(s[t][i][j]));
            }
            printf("\n");
        }

        for (i=1 ; i<= M;i++)
        {
            for(j=1;j<=M;j++)               //each area (using matlabs' Matrix Operation will be faster but we know the matlab file will be much larger)
            {
                double fire=rand()/maxn;    //if fire<f    lighting up!
                double grow=rand()/maxn;    //if grow<p    growing up!
                if(s[t][i][j]==2)
                {
                    s[t+1][i][j]=0;   //case 0    after burned, a the area become an open area
                }
                else if(s[t][i][j]==0 && grow<p)
                {
                    s[t+1][i][j]=1;    //case 1    growing up!
                }
                else if(s[t][i][j]==1)      //case 1
                {
                    if(fire<f)
                    {
                        s[t+1][i][j]=2;
                    }
                    else
                    {
                        if(s[t][i-1][j]==2||s[t][i-1][j-1]==2||s[t][i-1][j+1]==2||s[t][i][j-1]==2||s[t][i][j+1]==2||s[t][i+1][j]==2||s[t][i+1][j+1]==2||s[t][i+1][j-1]==2)
                        {
                            s[t+1][i][j]=2; //a tree will be lighted if it is near by a burning tree
                        }
                        else
                        {
                            s[t+1][i][j]=1;
                        }
                    }

                }
               // printf("%c",change(s[t+1][i][j]));  //there are better ways to show the result and the change
            }
            //printf("\n");
        }

        num[0]=num[1]=num[2]=0; //  count
        for(i=1;i<=M;i++)
        {
            for(j=1;j<=M;j++)
            {
                num[s[t][i][j]]++;
            }
        }
        t++;
        Sleep(1000);
    }
    return 0;
}
