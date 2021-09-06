#include <iostream>
#include"speechManager.h"

using namespace std;

int main()
{
    SpeechManager sm;

    int choice=0;

    while(1){

        sm.showMenu();

        cout<<"ÇëÊäÈëÄúµÄÑ¡Ôñ£º"<<endl;
        cin>>choice;

        switch(choice){
            case 1:
                sm.startSpeech();
                break;
            case 2:
                sm.showRecord();
                break;
            case 3:
                sm.clearRecord();
                break;
            case 0:
                sm.exitSystem();
                break;
            default:
                system("cls");
                break;

        }
    }


    return 0;
}
