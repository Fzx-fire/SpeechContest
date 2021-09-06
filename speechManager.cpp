#include"speechManager.h"
#include"speaker.h"
#include<string>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<utility>

SpeechManager::SpeechManager(){
    //��ʼ��
    this->initSpeech();
    //����ѡ��
    this->creatSpeaker();

    this->loadRecord();

}

void SpeechManager::showMenu(){
    cout<<"****************************************"<<endl;
    cout<<"----------- ��ӭ�μ��ݽ����� -----------"<<endl;
    cout<<"----------- 1����ʼ�ݽ����� -----------"<<endl;
    cout<<"----------- 2���鿴�����¼ -----------"<<endl;
    cout<<"----------- 3����ձ�����¼ -----------"<<endl;
    cout<<"----------- 0���˳��������� -----------"<<endl;
    cout<<"****************************************"<<endl;
    cout<<endl;
}

void SpeechManager::exitSystem(){
    cout<<"��ӭ�´�ʹ�ã�"<<endl;
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
        string name="ѡ��";
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
    cout<<"�� "<<this->m_Index<<" ��ѡ�ֳ�ǩ"<<endl;
    cout<<"------------"<<endl;
    cout<<"��ǩ���ݽ�˳������:"<<endl;

    if(this->m_Index==1){//����ǵ�һ�ֶ�v12����
        random_shuffle(v12.begin(),v12.end());//ϴ��
        for(vector<int>::iterator it=v12.begin();it!=v12.end();it++){
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    else{//�ڶ��ֶ�v6����

        random_shuffle(v6.begin(),v6.end());//ϴ��
        for(vector<int>::iterator it=v6.begin();it!=v6.end();it++){
            cout<<*it<<" ";
        }
        cout<<endl;

    }
    cout<<"------------"<<endl;
    system("pause");
}

void SpeechManager::speechContest(){
    cout<<"�� "<<this->m_Index<<" �ֱ�����ʼ"<<endl;
    cout<<endl;
    //6��һ��
    multimap<double,int,greater<double>> groupScore;

    int num=0; //��¼��Ա����

    vector<int> v_src; //����ѡ������
    if(this->m_Index==1){

        v_src=v12;
    }
    else{
        v_src=v6;
    }

    for(vector<int>::iterator it=v_src.begin();it!=v_src.end();it++){
        num++;
        //��ί���
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

        //ƽ���ַŵ�map����
        this->m_Speaker[*it].m_Score[this->m_Index-1]=avg;

        //����ַŵ�С��������
        groupScore.insert(make_pair(avg,*it));

        if(num%6==0){
            cout<<"�� "<<num/6<<" ���������"<<endl;

            for(multimap<double,int,greater<double>>::iterator it=groupScore.begin();it!=groupScore.end();it++){
                cout<<"��ţ�"<<it->second<<" ������"<<this->m_Speaker[it->second].m_Name<<" �ɼ���"<<it->first<<endl;
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
    cout<<"�� "<<this->m_Index<<" �ֱ�������"<<endl;
    system("pause");
}

void SpeechManager::showScore(){
    cout<<"�� "<<this->m_Index<<" ��ѡ�ֽ�����Ϣ"<<endl;
    vector<int> v;

    if(this->m_Index==1){
        v=v6;
    }
    else{
        v=v3;
    }

    for(vector<int>::iterator it=v.begin();it!=v.end();it++){
        cout<<"��ţ�"<<*it<<" ������"<<m_Speaker[*it].m_Name<<" �ɼ���"<<m_Speaker[*it].m_Score[this->m_Index-1]<<endl;
    }
    cout<<endl;

    system("pause");
    system("cls");
    this->showMenu();

}

void SpeechManager::startSpeech(){
    //��һ��
    this->speechDraw();

    this->speechContest();

    this->showScore();

    //�ڶ���

    this->m_Index++;

    this->speechDraw();

    this->speechContest();

    this->showScore();

    //��������
    this->saveRecord();

    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();

    cout<<"����������"<<endl;
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

    cout<<"��¼�ѱ���"<<endl;

    this->fileEmpty=false;
}

void SpeechManager::loadRecord(){
    ifstream ifs("data/speech.csv",ios::in);

    if(!ifs.is_open()){
        this->fileEmpty=true;
        cout<<"�ļ�������"<<endl;
        ifs.close();
        return ;
    }

    char ch;
    ifs>>ch;
    if(ifs.eof()){
        cout<<"�ļ�Ϊ��"<<endl;
        this->fileEmpty=true;
        ifs.close();
        return ;
    }

    //�ļ���Ϊ��
    this->fileEmpty=false;

    ifs.putback(ch);//����ȡ�ĵ����ַ��Ż�

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
        cout<<it->first<<" �ھ���ţ�"<<it->second[0]<<" �÷֣�"<<it->second[1]<<endl;
    }
*/
}

void SpeechManager::showRecord(){
    if(this->fileEmpty){
        cout<<"�ļ������ڻ��ļ�Ϊ��"<<endl;
    }
    else{
        for(int i=0;i<m_Record.size();i++){
            cout<<"�� "<<i+1<<" ��"
                <<"�ھ���ţ�"<<this->m_Record[i][0]<<" �÷�"<<this->m_Record[i][1]<<" "
                <<"�Ǿ���ţ�"<<this->m_Record[i][2]<<" �÷�"<<this->m_Record[i][3]<<" "
                <<"������ţ�"<<this->m_Record[i][4]<<" �÷�"<<this->m_Record[i][5]<<endl;

        }
    }

    system("pause");
    system("cls");
}

void SpeechManager::clearRecord(){
    cout<<"ȷ����գ�y/n"<<endl;

    char ch;
    cin>>ch;

    if(ch=='y'){

        ofstream ofs("data/speech.csv",ios::trunc);
        ofs.close();

        this->initSpeech();
        this->creatSpeaker();
        this->loadRecord();

        cout<<"��ճɹ���"<<endl;
    }

    system("pause");
    system("cls");
}

SpeechManager::~SpeechManager(){

}
