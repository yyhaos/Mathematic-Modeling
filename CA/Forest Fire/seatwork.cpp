#include<bits/stdc++.h>
using namespace std;
//Simulate the formation and spread of forest fire by CA
int main ()
{
    double p=0.3, f=0.05, maxn=RAND_MAX;  //p=probability of growing a new tree in open area, f=probability of lighting a tree up
    int t=0, N=25, M=3, i, j;               //t=time(a specific unit of time, N=max time, M=max area
    int s[N+5][M+5][M+5];                   //s=the forest:0==open area, 1==a tree(or tree area), 2==a burning tree(burning area)
    memset(s,0,sizeof(s));                  //initialization random started
    for (i=0 ; i<= M+1;i++)
        for(j=0;j<=M+1;j++)
            s[t][i][j]=rand()%3;
    while(t<=N)                             //main part
    {
        printf("t=%d\n",t+1);
        for (i=1 ; i<= M;i++)
        {
            for(j=1;j<=M;j++)               //each area (using matlabs' Matrix Operation will be faster but we know the matlab file will be much larger)
            {
                double fire=rand()/maxn;    //if fire<f    lighting up!
                double grow=rand()/maxn;    //if grow<p    growing up!
                if(s[t][i][j]==2) s[t+1][i][j]=0;   //case 0    after burned, a the area become an open area
                else if(s[t][i][j]==0 && grow<p) s[t+1][i][j]=1;    //case 1    growing up!
                else if(s[t][i][j]==1)      //case 1
                {
                    if(fire<f) s[t+1][i][j]=2;
                    else
                    {
                        if(s[t][i-1][j]==1||s[t][i-1][j-1]==1||s[t][i-1][j+1]==1||s[t][i][j-1]==1||s[t][i][j+1]==1||s[t][i+1][j]==1||s[t][i+1][j+1]==1||s[t][i+1][j-1]==1)
                            s[t+1][i][j]=2; //a tree will be lighted if it is near by a burning tree
                    }
                }
                printf("%d",s[t+1][i][j]);  //there are better ways to show the result and the change
            }
            printf("\n");
        }
        t++;
    }
    return 0;
}
