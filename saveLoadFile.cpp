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


// save the game into saveGame.txt
// Input: vector<vector<Card> > table, the vector storing the cards on the game table
//        Ptr p, struct storing the score, move, next, target, row, column, defined in card.h
// Output: void, the saveGame.txt will be overwritten
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

// load the game from saveGame.txt
// Input: vector<vector<Card> > &table, the vector storing the cards on the game table
//        Ptr &p, struct storing the score, move, next, target, row, column, defined in card.h
//        vector<CardMap> &cardMap, the vector storing the cardMap, defined in card.h
// Output: void, the table, p and cardMap will be updated from information in saveGame.txt
int loadGame(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap){
    ifstream loadFile;
    loadFile.open("saveGame.txt");
    if (loadFile.fail()){
        return 1;
    }

    Card subTable [9][28];
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 28; ++j) {

        subTable[i][j] = {-1,Card::Suit(0),false};
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
        bool show;
        if (shown == 1){
            show = true;
        }
        else{
            show = false;
        }
        subTable[column][row].rank = intrank;
        subTable[column][row].suit = Card::Suit(suit);
        subTable[column][row].shown = static_cast<bool>(shown);
        cardMap[intrank-1 + suit*13] = {column, row};
        table[column].push_back(subTable[column][row]);
        // reset stock deck
        p.next = 0;
        p.target = 0;
        p.row = 0;
        p.column = 0;
        p.move = 0;
        for (int i = 0; i < table[7].size(); ++i) {
            table[column][i].shown = false;
        }
    }

    loadFile.close();

    return 0;
}