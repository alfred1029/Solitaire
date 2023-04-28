#include<iostream>
#include<string>
#include"guiTemp.h"
#include"initTable.h"
#include"move.h"

using namespace std;

int main(){
    // This is temporary main function for development of game functions
    vector<Card> deck = initRandomDeck();
    vector<vector<Card>> table = initTable(deck);
    int move = 0, score = 0;
    string command;
    printTable(table, move, score);
    while (command != "e")
    {
        cin >> command;
        if (command == "f"){
            flipStock(table);
            ++move;
        }
        printTable(table, move, score);
    }
    
    return 0;
}