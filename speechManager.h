#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
#include<fstream>

using namespace std;

//�ݽ�����������
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
    //����ѡ�� 12��
    vector<int> v12;

    //��һ�ֽ��� 6��
    vector<int> v6;

    //ʤ��ǰ����
    vector<int> v3;

    //��ű�� �Լ� ѡ��
    map<int,Speaker> m_Speaker;

    //��¼��������
    int m_Index;

    bool fileEmpty;

    map<int,vector<string>> m_Record;
};

