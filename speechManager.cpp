#include"speechManager.h"
#include"speaker.h"
#include<string>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<utility>

SpeechManager::SpeechManager(){
    //初始化
    this->initSpeech();
    //创建选手
    this->creatSpeaker();

    this->loadRecord();

}

void SpeechManager::showMenu(){
    cout<<"****************************************"<<endl;
    cout<<"----------- 欢迎参加演讲比赛 -----------"<<endl;
    cout<<"----------- 1、开始演讲比赛 -----------"<<endl;
    cout<<"----------- 2、查看往届记录 -----------"<<endl;
    cout<<"----------- 3、清空比赛记录 -----------"<<endl;
    cout<<"----------- 0、退出比赛程序 -----------"<<endl;
    cout<<"****************************************"<<endl;
    cout<<endl;
}

void SpeechManager::exitSystem(){
    cout<<"欢迎下次使用！"<<endl;
    exit(0);
}

void SpeechManager::initSpeech(){
    this->v12.clear();
    this->v6.clear();
    this->v3.clear();
    this->m_Speaker.clear();

    this->m_Index=1;

    this->m_Record.clear();
}

void SpeechManager::creatSpeaker(){
    string namespeed="ABCDEFGHIJKL";

    for(int i=0;i<namespeed.size();i++){
        string name="选手";
        name+=namespeed[i];

        Speaker sp;
        sp.m_Name=name;

        for(int j=0;j<2;j++){
            sp.m_Score[j]=0;
        }

        this->v12.push_back(i+10001);
        this->m_Speaker.insert(pair<int,Speaker>(i+10001,sp));
    }
}

void SpeechManager::speechDraw(){
    cout<<"第 "<<this->m_Index<<" 轮选手抽签"<<endl;
    cout<<"------------"<<endl;
    cout<<"抽签后演讲顺序如下:"<<endl;

    if(this->m_Index==1){//如果是第一轮对v12操作
        random_shuffle(v12.begin(),v12.end());//洗牌
        for(vector<int>::iterator it=v12.begin();it!=v12.end();it++){
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    else{//第二轮对v6操作

        random_shuffle(v6.begin(),v6.end());//洗牌
        for(vector<int>::iterator it=v6.begin();it!=v6.end();it++){
            cout<<*it<<" ";
        }
        cout<<endl;

    }
    cout<<"------------"<<endl;
    system("pause");
}

void SpeechManager::speechContest(){
    cout<<"第 "<<this->m_Index<<" 轮比赛开始"<<endl;
    cout<<endl;
    //6人一组
    multimap<double,int,greater<double>> groupScore;

    int num=0; //记录人员个数

    vector<int> v_src; //比赛选手容器
    if(this->m_Index==1){

        v_src=v12;
    }
    else{
        v_src=v6;
    }

    for(vector<int>::iterator it=v_src.begin();it!=v_src.end();it++){
        num++;
        //评委打分
        deque<double> d;
        for(int i=0;i<10;i++){
            double score=(rand()%401+600)/10.f;

            d.push_back(score);
        }

        sort(d.begin(),d.end(),greater<double>());
        d.pop_front();
        d.pop_back();
        double sum=0;
        sum=accumulate(d.begin(),d.end(),0.0f);
        double avg=0;
        avg=sum/(double)d.size();

        //平均分放到map容器
        this->m_Speaker[*it].m_Score[this->m_Index-1]=avg;

        //将打分放到小组容器中
        groupScore.insert(make_pair(avg,*it));

        if(num%6==0){
            cout<<"第 "<<num/6<<" 组比赛名次"<<endl;

            for(multimap<double,int,greater<double>>::iterator it=groupScore.begin();it!=groupScore.end();it++){
                cout<<"编号："<<it->second<<" 姓名："<<this->m_Speaker[it->second].m_Name<<" 成绩："<<it->first<<endl;
            }

            int counts=0;
            for(multimap<double,int,greater<double>>::iterator it=groupScore.begin();it!=groupScore.end() && counts<3;it++,counts++){
                if(this->m_Index==1){
                    v6.push_back((*it).second);
                }else{
                    v3.push_back((*it).second);
                }
            }
            groupScore.clear();
            cout<<endl;
        }
    }
    cout<<"第 "<<this->m_Index<<" 轮比赛结束"<<endl;
    system("pause");
}

void SpeechManager::showScore(){
    cout<<"第 "<<this->m_Index<<" 轮选手晋级信息"<<endl;
    vector<int> v;

    if(this->m_Index==1){
        v=v6;
    }
    else{
        v=v3;
    }

    for(vector<int>::iterator it=v.begin();it!=v.end();it++){
        cout<<"编号："<<*it<<" 姓名："<<m_Speaker[*it].m_Name<<" 成绩："<<m_Speaker[*it].m_Score[this->m_Index-1]<<endl;
    }
    cout<<endl;

    system("pause");
    system("cls");
    this->showMenu();

}

void SpeechManager::startSpeech(){
    //第一轮
    this->speechDraw();

    this->speechContest();

    this->showScore();

    //第二轮

    this->m_Index++;

    this->speechDraw();

    this->speechContest();

    this->showScore();

    //保存数据
    this->saveRecord();

    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();

    cout<<"本届比赛完毕"<<endl;
    system("pause");
    system("cls");

}

void SpeechManager::saveRecord(){
    ofstream ofs;
    ofs.open("data/speech.csv",ios::out | ios::app);

    for(vector<int>::iterator it=v3.begin();it!=v3.end();it++){
        ofs<<*it<<","<<m_Speaker[*it].m_Score[1]<<",";
    }

    ofs<<endl;

    ofs.close();

    cout<<"记录已保存"<<endl;

    this->fileEmpty=false;
}

void SpeechManager::loadRecord(){
    ifstream ifs("data/speech.csv",ios::in);

    if(!ifs.is_open()){
        this->fileEmpty=true;
        cout<<"文件不存在"<<endl;
        ifs.close();
        return ;
    }

    char ch;
    ifs>>ch;
    if(ifs.eof()){
        cout<<"文件为空"<<endl;
        this->fileEmpty=true;
        ifs.close();
        return ;
    }

    //文件不为空
    this->fileEmpty=false;

    ifs.putback(ch);//将读取的单个字符放回

    string data;

    int index=0;
    while(ifs>>data){

        vector<string> v;

        int pos=-1;
        int start=0;

        while(1){
            pos=data.find(",",start);
            if(pos==-1){
                break;
            }

            string tmp=data.substr(start,pos-start);

            v.push_back(tmp);
            start=pos+1;
        }

        this->m_Record.insert(make_pair(index,v));
        index++;

    }
    ifs.close();
/*
    for(map<int,vector<string>>::iterator it=m_Record.begin();it!=m_Record.end();it++){
        cout<<it->first<<" 冠军编号："<<it->second[0]<<" 得分："<<it->second[1]<<endl;
    }
*/
}

void SpeechManager::showRecord(){
    if(this->fileEmpty){
        cout<<"文件不存在或文件为空"<<endl;
    }
    else{
        for(int i=0;i<m_Record.size();i++){
            cout<<"第 "<<i+1<<" 届"
                <<"冠军编号："<<this->m_Record[i][0]<<" 得分"<<this->m_Record[i][1]<<" "
                <<"亚军编号："<<this->m_Record[i][2]<<" 得分"<<this->m_Record[i][3]<<" "
                <<"季军编号："<<this->m_Record[i][4]<<" 得分"<<this->m_Record[i][5]<<endl;

        }
    }

    system("pause");
    system("cls");
}

void SpeechManager::clearRecord(){
    cout<<"确认清空？y/n"<<endl;

    char ch;
    cin>>ch;

    if(ch=='y'){

        ofstream ofs("data/speech.csv",ios::trunc);
        ofs.close();

        this->initSpeech();
        this->creatSpeaker();
        this->loadRecord();

        cout<<"清空成功！"<<endl;
    }

    system("pause");
    system("cls");
}

SpeechManager::~SpeechManager(){

}
