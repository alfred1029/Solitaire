#include<iostream>
#include<string>
#include"guiTemp.h"
#include"initTable.h"

using namespace std;

int main(){
    vector<Card> deck = initRandomDeck();
    vector<vector<Card>> table = initTable(deck);
    int move = 0;
    int score = 0;
    printTable(table, move, score);
    return 0;
}