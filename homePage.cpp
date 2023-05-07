#include <iostream>
#include "homePage.h"

using namespace std;

void startHomePage(string& command){
    cout<<"======================== Welcome to the Solitaire! ========================"<<endl;
    cout<<"     1. Start"<<endl;
    cout<<"     2. Leader board(No implement)"<<endl;
    cout<<"     3. How to Play(No adding it)"<<endl;
    cout<<"     Exit "<<endl;
    cout<<"=========================================================================="<<endl;
    cout<<"Please enter command(1,2,3,Exit):";
    cin>>command;
}

void startGame(string &command){
    cout<<"================================ Start game  ================================"<<endl;
    cout<<"     1. New Game"<<endl;
    cout<<"     2. Load Game(No implement)"<<endl;
    cout<<"     3. Back"<<endl;
    cout<<"=========================================================================="<<endl;
    cout<<"Please enter command(1,2,3):";
    cin>>command;
}

void hpNewGame(string& command){
    cout<<"================================ New game  ================================="<<endl;
    cout<<"     1. Change User"<<endl;
    cout<<"     2. Difficulty "<<endl;
    cout<<"     3. Back"<<endl;
    cout<<"=========================================================================="<<endl;
    cout<<"Please enter command(1,2,3):";
    cin>>command;
}

void hpLoadGame(){
    cout<<"================================ Load game  ================================"<<endl;
    cout<<"     Loading…Please Wait"<<endl;
    cout<<"     Load Successfully"<<endl;
    cout<<"     Game Started !!!"<<endl;
    cout<<"============================================================================"<<endl;
}

void hpInputUserName(string &userName){
    cout << "================================ Change User ================================" << endl;
    cout << "   Please enter your new name: ";
    cin >> userName;
    cout << "   Storing user name..." << endl;
    cout << "   Stored successfully!" << endl;
    cout << "===========================================================================" << endl;
}

void hpDifficulty(string& command){
    cout << "============================== Choosing Difficulty =============================" << endl;
    cout<<"     1. Easy "<<endl;
    cout<<"     2. Medium"<<endl;
    cout<<"     3. Difficult"<<endl;
    cout<<"     4. Expert"<<endl;
    cout<<"     5. Back"<<endl;
    cout << "==========================================================================" << endl;
    cout<<"Please enter command(1,2,3,4,5):";
    cin>>command;
}

void hpLeaderBoard(){
    cout<<"================================ Leader Board ================================"<<endl;
}

void hpHowToPlay(){
    cout<< "================================ How to Play ================================"<<endl;
}
