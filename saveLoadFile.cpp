#include "saveLoadFile.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "redoUndo.h"
#include "saveLoadFile.h"

using namespace std;

void saveGame(const vector<vector<Card> > &table, const Ptr &p, const vector<CardMap> &cardMap){
    ofstream saveFile;
    saveFile.open("saveGame.txt");
    if(saveFile.fail()){
        //fail to open saveGame, do not exist
        ofstream outfile("saveGame.txt");//create a saveGame.txt file
        //write process into saveGame.txt
        //output table to save
        saveFile<<"table"<<endl;
        for (int i=0; i<9; i++){
            for(int j=0; j<table[i].size(); j++){
                saveFile << table[i][j].rank;
                saveFile << table[i][j].suit;
                saveFile << table[i][j].shown <<endl;
            }
        }

        //output cardMap to save
        saveFile<<"cardMap"<<endl;
        for (int i=0; i<cardMap.size(); i++){
            saveFile << cardMap[i].column << ' ' << cardMap[i].row <<endl;
        }
        //output p to save
        saveFile<<"p"<<endl;
        saveFile << p.column << ' ' << p.row << ' ' << p.target;
        saveFile << p.next << ' ' << p.move << ' ' << p.score << endl;
    }
    else{
        //open saveGame, do exist
        //write process into saveGame.txt
        //output table to save
        saveFile<<"table"<<endl;
        for (int i=0; i<9; i++){
            for(int j=0; j<table[i].size(); j++){
                saveFile << table[i][j].rank <<' ';
                saveFile << table[i][j].suit <<' ';
                saveFile << table[i][j].shown <<endl;
            }
        }

        //output cardMap to save
        saveFile<<"cardMap"<<endl;
        for (int i=0; i<cardMap.size(); i++){
            saveFile << cardMap[i].column << ' ' << cardMap[i].row <<endl;
        }
        //output p to save
        saveFile<<"ptr value"<<endl;
        saveFile << p.column << ' ' << p.row << ' ' << p.target <<' ';
        saveFile << p.next << ' ' << p.move << ' ' << p.score << endl;
    } 
    
    saveFile.close();
}

void loadGame(const vector<vector<Card> > &table, const Ptr &p, const vector<CardMap> &cardMap){

}