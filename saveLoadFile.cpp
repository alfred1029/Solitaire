#include "saveLoadFile.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "redoUndo.h"
#include <string>
#include <vector>
#include <algorithm>
#include "card.h"
#include <sstream>

using namespace std;

void saveGame(const vector<vector<Card> > &table, const Ptr &p){
    ofstream saveFile;
    saveFile.open("saveGame.txt", ios::trunc); //open new file, delete old file

    for (int i = 0; i < table.size(); i++){
        for (int j = 0; j < table[i].size(); j++){
            saveFile << table[i][j].rank << ' ';
            saveFile << table[i][j].suit << ' ';
            saveFile << table[i][j].shown << ' ';
            saveFile << i << ' ';
            saveFile << j << endl;
        }
    }

    saveFile << "Score/Move...: " << p.score << " " << p.move << " " << p.next << " " << p.target << " " << p.row << " " << p.column << endl;
    saveFile.close();
}


void loadGame(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap){
    ifstream loadFile;
    loadFile.open("saveGame.txt");

    Card subTable [9][28];
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 28; ++j) {
        subTable[i][j] = {-1,Card::Suit(0),-1};
        }
    }
    string line;
    string rank;
    int intrank, suit, shown, column, row;
    while (getline(loadFile, line)){
        istringstream iss(line);
        iss >> rank >> suit;
        if (rank == "Score/Move...:"){
            iss >> p.score >> p.move >> p.next >> p.target >> p.row >> p.column;
            break;
        }
        intrank = stoi(rank);
        iss >> shown >> column >> row;
        subTable[column][row].rank = intrank;
        subTable[column][row].suit = Card::Suit(suit);
        subTable[column][row].shown = shown;
        cardMap[intrank-1] = {column, row};
        table[column].push_back(subTable[column][row]);
    }

    loadFile.close();
}