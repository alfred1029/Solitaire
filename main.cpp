#include<iostream>
#include<string>
#include"guiTemp.h"
#include"initTable.h"
#include"move.h"
#include"checkInput.h"
#include"card.h"

using namespace std;

// This is temporary main function for development of game functions
int main(){
    // initialize table, cardMap, deck, move, score
    vector<vector<Card>> table(9);
    vector<CardMap> cardMap(52);
    Card * deck = new Card[52];
    int move = 0, score = 0;
    // randomize deck
    initRandomDeck(deck);
    initTable(table, cardMap, deck);
    // command to store user input
    // valid to check if command is valid and pass it to corresponding function
    // column and row indicate point which card
    string command;
    int valid, column, row;
    // game loop
    while (command != "e")
    {
        // print table and ask for command
        printTable(table, move, score);
        cout << "Please enter command: ";
        // get command and check if it is valid
        cin >> command;
        valid = checkValid(table, cardMap, column, row, command);
        // if valid, pass it to corresponding function
        switch (valid){
            case 1:
                // if valid == 1, flip the stock deck
                flipStock(table);
                ++move;
                break;
            case 2:
                // if valid == 2, move card to column
                moveCard(table, cardMap, column, row, findTarget(table, column, row));
                ++move;
                break;
            case 3:
                // if valid == 3, move card to stack
                moveCard(table, cardMap, column, row, findStack(table, column, row));
                ++move;
                break;
            default:
                // if valid == -1, print invalid input
                cout << "Invalid input!" << endl;
        }
    } 
    return 0;
}