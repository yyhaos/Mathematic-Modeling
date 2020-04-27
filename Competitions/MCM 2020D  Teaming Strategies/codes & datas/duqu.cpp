#include<bits/stdc++.h>
#include<string>
using namespace std;
//author: team #2005895

//#define test 1

#ifdef test
char pe_name[]="passingevents_short.csv";
char fe_name[]="fullevents_short.csv";
#else
char pe_name[]="passingevents.csv";
char fe_name[]="fullevents.csv";
#endif //short test.
char ma_name[]="matches.csv";

ifstream pe_fin(pe_name);
ifstream fe_fin(fe_name);
ifstream ma_fin(ma_name);

template <class Type>
Type stringToNum(const string str){
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

struct single_pass
{
    int ma_num;
    string teamID;
    string OrP;
    string DeP;
    string Per;
    float ETime;
    string EType;
    string ESubType;
    int ES_x,ES_y,ED_x,ED_y;
    single_pass(){}
    single_pass(int _ma_num,string _teamID,string _OrP,string _DeP,string _Per,
                float _ETime,string _EType,string _ESubType,int _ES_x,int _ES_y,int _ED_x,int _ED_y){
                ma_num=_ma_num,teamID=_teamID,OrP=_OrP,DeP=_DeP,Per=_Per,
                ETime=_ETime,EType=_EType,ESubType=_ESubType,ES_x=_ES_x,ES_y=_ES_y,ED_x=_ED_x,ED_y=_ED_y;
            }
    void show()
    {
        cout<<ma_num<<'\t'<<teamID<<'\t'<<OrP<<'\t'<<DeP<<'\t'<<Per<<'\t'<<ETime<<'\t'
        <<EType<<'\t'<<ESubType<<'\t'<<ES_x<<'\t'<<ES_y<<'\t'<<ED_x<<"\t"<<ED_y<<endl;
    }
}sp[1000005];
int s_cnt=0;

struct Player
{
    string name;
    string Team;
    float su_chuan;
    int cnt;
    float pos_x;
    float pos_y;
    Player(){cnt=0;pos_x=0,pos_y=0;su_chuan=0;}
}player[500];
map<string,int> pn;
int p_cnt=1;

struct Match
{
    int MatchID;
    string Opp;
    string Res;
    int Wsco,Lsco;
    string Side;
    string CoachID;
    Match(){}
    Match(int _MatchID,string _Opp,string _Res,int _Wsco,int _Lsco, string _Side,
          string _CoachID){
            MatchID=_MatchID;Opp=_Opp;Res=_Res;Wsco=_Wsco;Lsco=_Lsco;Side=_Side;CoachID=_CoachID;
          }
    void show()
    {
        cout<<MatchID<<"\t"<<Opp<<'\t'<<Res<<'\t'<<Wsco<<"\t"<<Lsco<<'\t'<<Side<<'\t'<<CoachID<<'\n';
    }
}ma[50];

struct tricon
{
    int a,b,c,cnt;
    tricon(){}
    tricon(int _a,int _b,int _c,int _cnt=0)
    {cnt=_cnt;
        a=_a,b=_b,c=_c;
        if(a>b)
            swap(a,b);
        if(a>c)
            swap(a,c);
        if(b>c)
            swap(b,c);
    }
    friend bool operator < (tricon x,tricon y){
        if(x.a!=y.a)return x.a<y.a;
        if(x.b!=y.b)return x.b<y.b;
        return x.c<y.c;
    }
    friend bool mycmp(tricon x,tricon y);
}tr[625000];
bool mycmp(tricon x,tricon y){
        return x.cnt>y.cnt;
}
int t_cnt=0;
map<tricon,int> tn;

int m_cnt=0;

int Ma_all[500][500];
//int Ma_sus[500][500];
int shiwu[500];
void init()
{
    memset(Ma_all,0,sizeof(Ma_all));
    s_cnt=0;
}

void read_pe();// 读取passingevent.csv 或 passingevent_short.csv 与 read_fe()冲突
void read_fe();// 读取fullevent.csv 或 fullevent_short.csv 与 read_pe()冲突
void read_ma();// 读取matches.csv

void get_all();// 读取全部比赛
void myget(int tar);// 读取指定比赛

int hus[40];
int hth=1;

map<int,int> zn;
struct Zheng
{
    int name,win,lose,cnt;
    Zheng(){}
    Zheng(int _na,int _w,int _l,int _cnt)
    {
        name=_na;win=_w;lose=_l;cnt=_cnt;
    }
} zheng[50];
int z_cnt=1;

struct Crucial
{
    int cnt=0;
    int cnt2=0;
    vector<string> name;
    vector<int> x;
    vector<int> y;
}cr[1000];
int c_cnt=0;
vector<int> ssx,ssx2;
vector<int> ssy,ssy2;
int ss_cnt=0,ss_cnt2=0;
struct Dyadic
{
    int x,y,cnt=0;
    friend bool operator < (Dyadic a,Dyadic b){
        return a.cnt>b.cnt;
    }
    Dyadic(){}
}dy[3000];
int d_cnt=0;
struct Duel
{
    int cnt=0,den=0,dens=0,att=0,atts=0;
    void show()
    {
        cout<<cnt<<"\t"<<den<<"\t"<<dens<<"\t"<<att<<"\t"<<atts<<"\n";
    }
}du[1000];

int ma_re[3][3];// flex
int ma_re2[3][3];// ment

void get_pass_duel();
int main ()
{
    memset(ma_re2,0,sizeof(ma_re2));
    memset(ma_re,0,sizeof(ma_re));
    memset(shiwu,0,sizeof(shiwu));
    memset(du,0,sizeof(du));

   // read_pe();
    read_fe();
    read_ma();
    get_all();

freopen("Matrix_all_pass.txt","w",stdout);//输出到txt

    for(int i=0;i<m_cnt;i++)
    {int fi;
            if(ma[i].Res[0]=='w')
                fi=0;
            else if(ma[i].Res[0]=='l')
                fi=2;
            else fi=1;
            if(ma[i].Side[0]=='h')
                ma_re2[0][fi]++;
            else if(ma[i].Side[0]=='a')
                ma_re2[1][fi]++;
    }

    cout<<"match_flex\twin\ttie\tloss\n";
    for(int i=0;i<3;i++)
    {
        if(i==0)cout<<"home\t";
        else cout<<"away\t";
        for(int j=0;j<3;j++)
        {
            cout<<ma_re2[i][j]<<"\t";
        }
        cout<<"\n";
    }
    for(int j=1;j<=19;j++)
    {
        string tar=string("Opponent")+to_string(j);
        int fi=-1;
        for(int i=0;i<m_cnt;i++)
        {
            //fi=-1;
            if(ma[i].Opp==tar)
            {
                if(fi==-1)
                {
                    if(ma[i].Res[0]=='w')
                        fi=0;
                    else if(ma[i].Res[0]=='l')
                        fi=2;
                    else fi=1;
                }
                else
                {
                    if(ma[i].Res[0]=='w')
                        ma_re[fi][0]++;
                    else if(ma[i].Res[0]=='l')
                        ma_re[fi][2]++;
                    else ma_re[fi][1]++;
                }
            }
        }
    }
    cout<<"match\twin2\ttie2\tloss2\n";
    for(int i=0;i<3;i++)
    {
        if(i==0)cout<<"win1\t";
        else if(i==2)cout<<"loss1\t";
        else cout<<"tie2\t";
        for(int j=0;j<3;j++)
        {
            cout<<ma_re[i][j]<<"\t";
        }
        cout<<"\n";
    }
    for(int i=1;i<s_cnt-1;i++)
    {
        if(sp[i].EType=="Duel" )
        {
            int now=pn[sp[i].OrP];
            du[ now ].cnt++;
            if( sp[i-1].teamID==sp[i].teamID )
            {
                du[now].den++;
                if(sp[i+1].teamID==sp[i].teamID)
                {
                    du[now].dens++;
                }
            }
            if(sp[i-1].teamID!=sp[i].teamID)
            {
                du[now].att++;
                if(sp[i+1].teamID==sp[i].teamID)
                {
                    du[now].atts++;
                }
            }
        }
    }
//    cout<<"name\tcnt\tdenfend\tdenfend_sus\tattack\tattack_sus\n";
    for(int i=1;i<hth;i++)
    {
        cout<<player[hus[i]].name<<"\t";
        du[hus[i]].show();
    }
cout<<"123123"<<endl;
int j_cnt=50;
    for(int i=0;i<s_cnt;i++)
    {
        string tmpteam="Huskies";
        if(sp[i].EType=="Shot" && sp[i].teamID==tmpteam)
        {
//            cout<<i<<endl;
j_cnt--;
if(j_cnt<0)break;
            cr[c_cnt].x.push_back(100);
            cr[c_cnt].y.push_back(50);
            cr[c_cnt].cnt++;
            cr[c_cnt].cnt2++;
            cr[c_cnt].cnt2++;
            ss_cnt2++;
            ssx2.push_back(sp[i].ES_x);
            ssy2.push_back(sp[i].ES_y);
            cr[c_cnt].x.push_back(sp[i].ES_x);
            cr[c_cnt].y.push_back(sp[i].ES_y);
            cr[c_cnt].name.push_back(sp[i].OrP);
            for(int k=i-1;k>=i-6 ;k-- )
            {
                cr[c_cnt].x.push_back(sp[k].ED_x);
                cr[c_cnt].x.push_back(sp[k].ES_x);
                cr[c_cnt].y.push_back(sp[k].ED_y);
                cr[c_cnt].y.push_back(sp[k].ES_y);
                cr[c_cnt].cnt2++;
                cr[c_cnt].cnt2++;
                cr[c_cnt].name.push_back(sp[k].OrP);
                cr[c_cnt].cnt++;
                if(sp[k].teamID!=tmpteam || sp[k].EType!="Pass")
                {
                    if(sp[k].teamID!=tmpteam)
                    {
                        ssx.push_back(sp[k].ED_x);
                        ssy.push_back(sp[k].ED_y);ss_cnt++;
                    }
                    cr[c_cnt].cnt2--;
                    break;
                }
            }
            c_cnt++;
        }
    }
     int cur[500];
     memset(cur,0,sizeof(cur));
     for(int i=0;i<c_cnt;i++)
     {
         int len=cr[i].name.size();
         for(int k=0;k<len;k++)
         {
             cur[pn[cr[i].name[k]]]++;
         }
     }
     cout<<"cru\n";
     for(int i=1;i<hth;i++)
     {
        cout<<player[hus[i]].name<<"\t"<<cur[hus[i]]<<"\n";
     }

//    cout<<"Crucial\n";
//    for(int i=0;i<c_cnt;i++)
//    {
////        cout<<cr[i].cnt2<<":\t";
//        for(int k=0;k<cr[i].cnt2-1;k++)
//        {
//            cout<<cr[i].x[k+1]<<"\t"<<cr[i].y[k+1]<<'\t'<<cr[i].x[k]<<"\t"<<cr[i].y[k]<<
//            "\n";
//        }
//    }
    cout<<"sandian\n";
    for(int i=0;i<ss_cnt;i++)
    {
        cout<<ssx[i]<<"\t"<<ssy[i]<<endl;
    }
    cout<<"sandian2\n";
    for(int i=0;i<ss_cnt2;i++)
    {
        cout<<ssx2[i]<<"\t"<<ssy2[i]<<endl;
    }

cout<<"name\tcount\twin\tlose\n";
    for(int i=1;i<=38;i++)
    {
        myget(i);
        int tz=0;
        for(int j=0;j<12;j++)
        {
            if(player[hus[j]].name.find("M")!=string::npos)
            {
                tz+=10;
            }
            else if(player[hus[j]].name.find("F")!=string::npos)
            {
                tz+=1;
            }
            else if(player[hus[j]].name.find("D")!=string::npos)
            {
                tz+=100;
            }
        }
        if(zn[tz]==0)
        {
            zn[tz]=z_cnt;
            zheng[z_cnt]=Zheng(tz,0,0,0);
            z_cnt++;
        }
//        cout<<tz<<" "<<z_cnt<<endl;
        zheng[zn[tz]].cnt++;
        if(ma[i].Res.find("w")!=string::npos)
        zheng[zn[tz]].win++;
        if(ma[i].Res.find("o")!=string::npos)
        zheng[zn[tz]].lose++;
    }


    cout<<"name\tcount\twin\tlose\n";
    for(int i=1;i<z_cnt;i++)
    {
        cout<<zheng[i].name<<"\t"<<zheng[i].cnt<<"\t"<<zheng[i].win<<"\t"<<zheng[i].lose<<endl;
    }

    //myget(1);
    get_all();
//int hus[40];
    //int th=1;

    // tricon
    for(int i=0;i<s_cnt-1;i++)
    {
        if(sp[i].teamID == sp[i+1].teamID && sp[i].teamID=="Huskies"&&sp[i].EType=="Pass"&&sp[i+1].EType=="Pass" )
        {
            if(pn[sp[i+1].DeP]!=pn[""])
            tn[tricon(pn[sp[i].OrP],pn[sp[i].DeP],pn[sp[i+1].DeP])]++;
        }
    }
    for(int i=1;i<hth;i++)
    {
        for(int j=i+1;j<hth;j++)
        {
            for(int k=j+1;k<hth;k++)
            {
                if(player[hus[i]].name.find("F")!=string::npos)
                tr[t_cnt++]=tricon(hus[i],hus[j],hus[k],tn[tricon(hus[i],hus[j],hus[k])]);
            }
        }
    }

    sort(tr,tr+t_cnt,mycmp);
    cout<<"triadic configurations with Forwards\n";
    cout<<"player1\tplayer2\tplayer3\tcnt\n";
    for(int i=0;i<30;i++)
    {
        cout<<player[tr[i].a].name<<"\t"<<player[tr[i].b].name<<"\t"<<player[tr[i].c].name<<"\t"<<tr[i].cnt<<endl;
    }

    cout<<"所有传球数\n\t";
    for(int i=1;i<hth;i++)
    {
        cout<<player[hus[i]].name<<'\t';
    }cout<<endl;

    for(int i=1;i<hth;i++)
    {
        cout<<player[hus[i]].name<<"\t";
        for(int j=1;j<hth;j++)
        {
//            if(player[j].Team=="Huskies")
            cout<<Ma_all[hus[i]][hus[j]]<<"\t";
            //if(player[hus[i]].Team=="Huskies" && player[hus[j]].Team=="Huskies")
            dy[d_cnt].x=hus[i];dy[d_cnt].y=hus[j];dy[d_cnt].cnt=Ma_all[hus[i]][hus[j]];
            d_cnt++;
        }
        cout<<"\n";
    }
    sort(dy,dy+d_cnt);
    cout<<"top passing\n";
    for(int i=0;i<20;i++)
    {
        cout<<player[dy[i].x].name<<"\t"<<player[dy[i].y].name<<"\t"<<dy[i].cnt<<"\n";
    }
    cout<<"失败传球数:\n";
    for(int i=1;i<hth;i++)
    {
        cout<<player[hus[i]].name<<'\t';
    }cout<<endl;
    for(int i=1;i<hth;i++)
    {
        cout<<shiwu[hus[i]]<<'\t';
    }cout<<endl;

    cout<<"Position:\n\t";
    for(int i=1;i<hth;i++)
    {
        cout<<player[hus[i]].name<<'\t';
    }cout<<endl;
    cout<<"x:\t";
    for(int i=1;i<hth;i++)
    {
        cout<<player[hus[i]].pos_x<<'\t';
    }cout<<endl;
cout<<"y:\t";
    for(int i=1;i<hth;i++)
    {
        cout<<player[hus[i]].pos_y<<'\t';
    }cout<<endl;

    pe_fin.close();
    fe_fin.close();
    ma_fin.close();
}

void read_pe()
{
    cout<<"read passing events\n"<<endl;
    init();
    string tmp;
    getline(pe_fin,tmp);
    while(pe_fin.good())
    {
        int _ma_num;
        string _teamID,_OrP,_DeP,_Per;
        float _ETime;
        string _EType,_ESubType;
        int _ES_x, _ES_y, _ED_x, _ED_y;

        getline(pe_fin,tmp,',');
        _ma_num=stringToNum<int>(tmp);
        getline(pe_fin,tmp,',');
        _teamID=tmp;
        getline(pe_fin,tmp,',');
        _OrP=tmp;
        getline(pe_fin,tmp,',');
        _DeP=tmp;
        getline(pe_fin,tmp,',');
        _Per=tmp;
        getline(pe_fin,tmp,',');
        _ETime=stringToNum<float>(tmp);
//        getline(pe_fin,tmp,',');
//        _EType=tmp;
        _EType="Pass";
        getline(pe_fin,tmp,',');
        _ESubType=tmp;
        getline(pe_fin,tmp,',');
        _ES_x=stringToNum<int>(tmp);
        getline(pe_fin,tmp,',');
        _ES_y=stringToNum<int>(tmp);
        getline(pe_fin,tmp,',');
        _ED_x=stringToNum<int>(tmp);
        getline(pe_fin,tmp,'\n');
        _ED_y=stringToNum<int>(tmp);
        sp[s_cnt]=single_pass(_ma_num,_teamID,_OrP,_DeP,_Per,_ETime,
                                _EType,_ESubType,_ES_x,_ES_y,_ED_x,_ED_y);
//        sp[s_cnt].show();
        s_cnt++;
    }
}
void read_fe()
{
    cout<<"read full events\n"<<endl;
    init();
    string tmp;
    getline(fe_fin,tmp);
    while(fe_fin.good())
    {
        int _ma_num;
        string _teamID,_OrP,_DeP,_Per;
        float _ETime;
        string _EType,_ESubType;
        int _ES_x, _ES_y, _ED_x, _ED_y;

        getline(fe_fin,tmp,',');
        _ma_num=stringToNum<int>(tmp);
        getline(fe_fin,tmp,',');
        _teamID=tmp;
        getline(fe_fin,tmp,',');
        _OrP=tmp;
        getline(fe_fin,tmp,',');
        _DeP=tmp;
        getline(fe_fin,tmp,',');
        _Per=tmp;
        getline(fe_fin,tmp,',');
        _ETime=stringToNum<float>(tmp);
        getline(fe_fin,tmp,',');
        _EType=tmp;
//        _EType="Pass";
        getline(fe_fin,tmp,',');
        _ESubType=tmp;
        getline(fe_fin,tmp,',');
        _ES_x=stringToNum<int>(tmp);
        getline(fe_fin,tmp,',');
        _ES_y=stringToNum<int>(tmp);
        getline(fe_fin,tmp,',');
        _ED_x=stringToNum<int>(tmp);
        getline(fe_fin,tmp,'\n');
        _ED_y=stringToNum<int>(tmp);
        sp[s_cnt]=single_pass(_ma_num,_teamID,_OrP,_DeP,_Per,_ETime,
                                _EType,_ESubType,_ES_x,_ES_y,_ED_x,_ED_y);
//        sp[s_cnt].show();
        s_cnt++;
    }

}
void read_ma()// 读取matches.csv
{
    string tmp;
    getline(ma_fin,tmp);
    m_cnt=0;
    while(ma_fin.good())
    {
       // cout<<"1\n";
        int _MatchID;
        string _Opp,_Res;
        int _Wsco;int _Lsco; string _Side;string _CoachID;

        getline(ma_fin,tmp,',');
        _MatchID=stringToNum<int>(tmp);
        getline(ma_fin,tmp,',');
        _Opp=tmp;
        getline(ma_fin,tmp,',');
        _Res=tmp;
        getline(ma_fin,tmp,',');
        _Wsco=stringToNum<int>(tmp);
        getline(ma_fin,tmp,',');
        _Lsco=stringToNum<int>(tmp);
        getline(ma_fin,tmp,',');
        _Side=tmp;
        getline(ma_fin,tmp,'\n');
        _CoachID=tmp;
        ma[m_cnt]=Match(_MatchID,_Opp,_Res,_Wsco,_Lsco,_Side,_CoachID);
        m_cnt++;
    }
    for(int i=0;i<s_cnt;i++)
    {
        if(pn[sp[i].OrP]==0)
        {
            player[p_cnt].name=sp[i].OrP;
            player[p_cnt].Team=sp[i].teamID;
            pn[sp[i].OrP]=p_cnt++;
        }
        if(pn[sp[i].DeP]==0)
        {
            player[p_cnt].name=sp[i].DeP;
            player[p_cnt].Team=sp[i].teamID;
            pn[sp[i].DeP]=p_cnt++;
        }
    }
}
void get_all()
{
    memset(shiwu,0,sizeof(shiwu));
  //  z_cnt=1;
  //  zn.clear();
    memset(Ma_all,0,sizeof(Ma_all));
    cout<<"get all games\n";
    p_cnt=1;
    //memset(player,0,sizeof(player));
    pn.clear();
    for(int i=0;i<s_cnt;i++)
    {
        if(pn[sp[i].OrP]==0)
        {
            player[p_cnt].name=sp[i].OrP;
            player[p_cnt].Team=sp[i].teamID;
            player[p_cnt].cnt=0;
            pn[sp[i].OrP]=p_cnt++;
        }
        if(pn[sp[i].DeP]==0)
        {
            player[p_cnt].name=sp[i].DeP;
            player[p_cnt].Team=sp[i].teamID;
            player[p_cnt].cnt=0;
            pn[sp[i].DeP]=p_cnt++;
        }
    }

    player[pn[""]].Team="";
    player[p_cnt].name=string("gate");
    player[p_cnt].Team=string("Huskies");
    hth=1;
    for(int i=0;i<s_cnt;i++)
    {
        int p1=pn[sp[i].OrP];
        int p2=pn[sp[i].DeP];
        if(sp[i].EType=="Pass" || sp[i].EType=="Shot")
        {
            if(sp[i].EType=="Shot")
            {
                p2=p_cnt;
                sp[i].ED_x=100;
                sp[i].ED_y=50;
            }
            //Ma_all[p1][p_cnt]++;
            Ma_all[p1][p2]++;
            if(  p2==pn[""])
            {
                shiwu[p1]++;
            }
//            cout<<p2<<" "<<pn[""]<<" "<<player[pn[""]].name<<" "<<sp[i].DeP<<endl;
            int p1n=player[p1].cnt;//统计位置
            player[p1].pos_x=1.0*player[p1].pos_x*p1n/(p1n+1)+ 1.0*sp[i].ES_x/(p1n+1);
            player[p1].pos_y=1.0*player[p1].pos_y*p1n/(p1n+1)+1.0* sp[i].ES_y/(p1n+1);
            int p2n=player[p2].cnt;
            player[p2].pos_x=1.0*player[p2].pos_x*p2n/(p2n+1)+1.0* sp[i].ED_x/(p2n+1);
            player[p2].pos_y=1.0*player[p2].pos_y*p2n/(p2n+1)+ 1.0*sp[i].ED_y/(p2n+1);
            player[p1].cnt++;
            player[p2].cnt++;
        }
    }

    for(int i=1;i<=p_cnt;i++)
    {
        if(player[i].Team=="Huskies")
        {
            //cout<<th++<<":"<<player[i].name<<"\t";
            hus[hth++]=i;
        }
    }
}
void myget(int tar)
{
    memset(shiwu,0,sizeof(shiwu));
    //z_cnt=1;
    //zn.clear();
    memset(Ma_all,0,sizeof(Ma_all));
    cout<<"get "<<tar<<" game"<<endl;
    p_cnt=1;
   // memset(player,0,sizeof(player));
    pn.clear();
    for(int i=0;i<s_cnt;i++)
    {
        if(sp[i].ma_num!=tar)continue;
        if(sp[i].ma_num>tar)break;
        if(pn[sp[i].OrP]==0)
        {
            player[p_cnt].name=sp[i].OrP;
            player[p_cnt].Team=sp[i].teamID;
            player[p_cnt].cnt=0;
            pn[sp[i].OrP]=p_cnt++;
        }
        if(pn[sp[i].DeP]==0)
        {
            player[p_cnt].name=sp[i].DeP;
            player[p_cnt].cnt=0;
            player[p_cnt].Team=sp[i].teamID;
            pn[sp[i].DeP]=p_cnt++;
        }
    }
    player[pn[""]].Team="";
    player[p_cnt].name=string("gate");
    player[p_cnt].Team=string("Huskies");
    hth=1;

    for(int i=0;i<s_cnt;i++)
    {
        if(sp[i].ma_num!=tar)continue;
        if(sp[i].ma_num>tar)break;
        int p1=pn[sp[i].OrP];
        int p2=pn[sp[i].DeP];
        if(sp[i].EType=="Pass" || sp[i].EType=="Shot")
        {
            if(sp[i].EType=="Shot")
            {
                p2=p_cnt;
                sp[i].ED_x=100;
                sp[i].ED_y=50;
            }
            //Ma_all[p1][p_cnt]++;
            Ma_all[p1][p2]++;
            if( p2==pn[""])
            {
                shiwu[p1]++;
            }
            int p1n=player[p1].cnt;//统计位置
            player[p1].pos_x=1.0*player[p1].pos_x*p1n/(p1n+1)+ 1.0*sp[i].ES_x/(p1n+1);
            player[p1].pos_y=1.0*player[p1].pos_y*p1n/(p1n+1)+1.0* sp[i].ES_y/(p1n+1);
            int p2n=player[p2].cnt;
            player[p2].pos_x=1.0*player[p2].pos_x*p2n/(p2n+1)+1.0* sp[i].ED_x/(p2n+1);
            player[p2].pos_y=1.0*player[p2].pos_y*p2n/(p2n+1)+ 1.0*sp[i].ED_y/(p2n+1);
            player[p1].cnt++;
            player[p2].cnt++;
        }
    }

    for(int i=1;i<=p_cnt;i++)
    {
        if(player[i].Team=="Huskies")
        {
            //cout<<th++<<":"<<player[i].name<<"\t";
            hus[hth++]=i;
        }
    }
}

void get_pass_duel()
{
        cout<<"Pass\n";

        float pre=0;
    for(int i=0;i<s_cnt;i++)
    {
        if(sp[i].EType=="Pass")
        {
            if(sp[i].Per=="1H")
            {
                cout<<sp[i].ETime<<endl;
                pre=sp[i].ETime;
            }
            else
                cout<<sp[i].ETime+pre<<endl;
        }
    }
cout<<"Duel\n";
    for(int i=0;i<s_cnt;i++)
    {
        if(sp[i].EType=="Duel")
        {
            if(sp[i].Per=="1H")
            {
                cout<<sp[i].ETime<<endl;
                pre=sp[i].ETime;
            }
            else
                cout<<sp[i].ETime+pre<<endl;
        }
    }

}
