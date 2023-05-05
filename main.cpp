#include<iostream>
#include<string>
#include<vector>
#include"guiTemp.h"
#include"initTable.h"
#include"move.h"
#include"checkInput.h"
#include"card.h"

using namespace std;

// This is temporary main function for development of game functions
int main(){
    string difficulty;
    cout << "Please select difficulty: easy, medium, hard, expert" << endl;
    cin >> difficulty;
    if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard" && difficulty != "expert") {
        cout << "Invalid difficulty!" << endl;
        return 0;
    }
    // initialize table, cardMap, deck
    vector<vector<Card>> table(9);
    vector<CardMap> cardMap(52);
    Card * deck = new Card[52];
    // initialize a winnable deck (to be debbuged)
    initWinnableDeck(deck, difficulty);
    initTable(table, cardMap, deck);
    cout << "Deck initialized!" << endl;
    // free memory from deck
    delete [] deck;
    deck = nullptr;
    // Ptr p to store the information of the table
    // command to store user input
    // valid to check if command is valid and pass it to corresponding function
    Ptr ptr;
    string command;
    int valid;
    // game loop
    while (command != "e")
    {
        // print table and ask for command
        printTable(table, ptr);
        // get command and check if it is valid
        cin >> command;
        valid = checkValid(table, cardMap, ptr, command);
        // if valid, pass it to corresponding function
        switch (valid){
            case 1:
                // if valid == 1, flip the stock deck
                flipStock(table, ptr);
                break;
            case 2:
                // if valid == 2, move card to column
                findTarget(table, ptr);
                if (ptr.target == -1){
                    cout << "No possible move!" << endl;
                    break;
                }
                moveCard(table, cardMap, ptr);
                break;
            case 3:
                cout << "valid = 3" << endl;
                // if valid == 3, move card to stack
                findStack(table, ptr);
                if (ptr.target == -1){
                    cout << "No possible move!" << endl;
                    break;
                }
                moveCard(table, cardMap, ptr);
                break;
            default:
                // if valid == -1, print invalid input
                cout << "Invalid input!" << endl;
        }
    }
    return 0;
}