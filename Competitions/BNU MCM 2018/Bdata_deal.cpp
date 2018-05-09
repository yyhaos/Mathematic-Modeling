#include<bits/stdc++.h>
using namespace std;
struct data
{
    int time;
    float Price;
    int Volume;
    float SP[6];
    int SV[6];
    float BP[6];
    int BV[6];
};
int main ()
{
    int N=23,maxn=200000;
    char filename[]="SH601398_1_u.txt";
    //printf("%s",filename);
    freopen(filename,"rb",stdin);
    char title[25][100];
    int tem[25][100];
    for(int i = 0 ; i<N ;i++)
    {
        scanf("%s",title[i]);
        printf("%s\t",title[i]);
    }
    vector <data> datas;
    struct data tem_data;
    tem_data.Volume=0;
    for(int i= 0 ; i<=5 ; i++)
    {
        tem_data.SP[i]=0;
        tem_data.SV[i]=0;
        tem_data.BP[i]=0;
        tem_data.BV[i]=0;
    }
    int tem_time;
    float tem_Price;
    int tem_Volume;
    float tem_SP[6];
    int tem_SV[6];
    float tem_BP[6];
    int tem_BV[6];
    int used[maxn];
    for(int i= 0 ; i<maxn ; i++)
    {
        used[i]=0;
    }
    int flag=1;

    int th=1;
    while(~scanf("%d%f%d%f%f%f%f%f%d%d%d%d%d%f%f%f%f%f%d%d%d%d%d",&tem_time,&tem_Price,&tem_Volume,&tem_SP[1],&tem_SP[2],&tem_SP[3],&tem_SP[4],&tem_SP[5],\
                 &tem_SV[1],&tem_SV[2],&tem_SV[3],&tem_SV[4],&tem_SV[5],\
                 &tem_BP[1],&tem_BP[2],&tem_BP[3],&tem_BP[4],&tem_BP[5],\
                 &tem_BV[1],&tem_BV[2],&tem_BV[3],&tem_BV[4],&tem_BV[5]))
    {
        if(tem_time%10==5)
            continue;
        //printf("%d\n",tem_time);
        if(tem_time!=10309)
        {
            flag=0;
        }
        if(used[tem_time]==0 && flag==0)
        {
            //printf("%d\n",tem_time);
            flag=0;
            datas.push_back(tem_data);
            tem_data.Volume=0;
            for(int i= 0 ; i<=5 ; i++)
            {
                tem_data.SP[i]=0;
                tem_data.SV[i]=0;
                tem_data.BP[i]=0;
                tem_data.BV[i]=0;
            }
        }
        used[tem_time]=1;
        tem_data.time=tem_time;
        tem_data.Price=tem_Price;
        tem_data.Volume+=tem_Volume;
        for(int i= 1 ; i<=5 ; i++)
        {
            tem_data.SP[i]=tem_SP[i];
            tem_data.SV[i]=max(tem_data.SV[i],tem_SV[i]);
            tem_data.BP[i]=tem_BP[i];
            tem_data.BV[i]=max(tem_data.BV[i],tem_BV[i]);
        }
    }
    datas.push_back(tem_data);
    printf("Vector finished\n");
    FILE *fpt;
    fpt = fopen("P_maxBV.txt","w");
    /*
    for (int i = 0; i < datas.size(); i++)
    {
        fprintf(fpt,"%d\t%f\t%d\t%d\n",datas[i].time,datas[i].Price,datas[i].Volume,datas[i].SV[1]-datas[i].BV[1]);
    }
    */

    int tem_i;
    int tem_max_BV[1000][6];
    memset(tem_max_BV,0,sizeof(tem_max_BV));
    int min_Price=9999,max_Price=-1;
    for (int i = 0; i < datas.size(); i++)
    {
        int tem_int_Price=(int)(datas[i].Price*100+0.1);
        min_Price=min(min_Price,tem_int_Price);
        max_Price=max(max_Price,tem_int_Price);
        tem_max_BV[tem_int_Price][0]++;
        //if(tem_max_BV[tem_int_Price][1]<datas[i].BV[1])
        //{
            for(int j=1;j<=5;j++)
                tem_max_BV[tem_int_Price][j]+=datas[i].BV[j];
        //}

    }
    for(int i=min_Price;i<=max_Price;i++)
    {
        fprintf(fpt,"%f\t",((float)i)/100.0);
        if(tem_max_BV[i][1]>0)
        {
            for(int j=1;j<=5;j++)
            {
                fprintf(fpt,"%d\t",tem_max_BV[i][j]/tem_max_BV[i][0]);
            }
            fprintf(fpt,"%d",tem_max_BV[i][0]);
        }
        fprintf(fpt,"\n");
    }
    //fpt.close();
    //int i=0;
    //printf("%d\t%f\t%d\t%d\n",datas[i].time,datas[i].Price,datas[i].Volume,datas[i].SV[1]-datas[i].BV[1]);
    printf("output finished\n");
    return 0;
}

