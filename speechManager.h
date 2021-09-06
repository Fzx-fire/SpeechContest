#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
#include<fstream>

using namespace std;

//演讲比赛管理类
class SpeechManager{
public:
    SpeechManager();

    void showMenu();
    void exitSystem();
    void initSpeech();
    void creatSpeaker();
    void startSpeech();
    void speechDraw();
    void speechContest();
    void showScore();
    void saveRecord();
    void loadRecord();
    void showRecord();
    void clearRecord();



    ~SpeechManager();
public:
    //比赛选手 12人
    vector<int> v12;

    //第一轮晋级 6人
    vector<int> v6;

    //胜利前三名
    vector<int> v3;

    //存放编号 以及 选手
    map<int,Speaker> m_Speaker;

    //记录比赛轮数
    int m_Index;

    bool fileEmpty;

    map<int,vector<string>> m_Record;
};

