#include<bits/stdc++.h>
using namespace std;
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
int m_cnt=0;

int Ma_all[500][500];
void init()
{
    memset(Ma_all,0,sizeof(Ma_all));
    s_cnt=0;
}

void read_pe();// 读取passingevent.csv 或 passingevent_short.csv 与 read_fe()冲突
void read_fe();// 读取fullevent.csv 或 fullevent_short.csv 与 read_pe()冲突
void read_ma();// 读取matches.csv

int main ()
{
    read_pe();
    //read_fe();
    read_ma();
    for(int i=0;i<m_cnt;i++)
    {
        ma[i].show();
    }
    for(int i=0;i<s_cnt;i++)
    {
        int p1=pn[sp[i].OrP];
        int p2=pn[sp[i].DeP];
        Ma_all[p1][p2]++;
    }
    //freopen("Matrix_all_pass.txt","w",stdout);//输出到txt
    for(int i=1;i<p_cnt;i++)
    {
        if(player[i].Team=="Huskies")
        {
            for(int j=1;j<p_cnt;j++)
            {
                if(player[j].Team=="Huskies")
                cout<<Ma_all[i][j]<<"\t";
            }
            cout<<"\n";
        }
    }
    for(int i=1;i<p_cnt;i++)
    {
        if(player[i].Team=="Huskies")
        {
            cout<<i<<":"<<player[i].name<<"\t";
        }
    }
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
