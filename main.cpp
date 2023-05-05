#include<iostream>
#include<string>
#include<vector>
#include "guiTemp.h"
#include "initTable.h"
#include "move.h"
#include "checkInput.h"
#include "card.h"
#include "redoUndo.h"

using namespace std;

// This is temporary main function for development of game functions
int main(){
    //store process
    vector<singleProcess> processes;
    // initialize table, cardMap, deck
    vector<vector<Card>> table(9);
    vector<CardMap> cardMap(52);
    Card * deck = new Card[52];
    // randomize deck
    initRandomDeck(deck);
    initTable(table, cardMap, deck);
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
        //save process
        saveProcess(table, ptr, cardMap, processes);
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
                deleteProcess(table, ptr, cardMap, processes);
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
            case 4:
                //if valid == 4, redo the process
                redo(table, ptr, cardMap, processes);
                break;
            case 5:
                //if valid == 5, undo the process
                undo(table, ptr, cardMap, processes);
                break;
            default:
                // if valid == -1, print invalid input
                cout << "Invalid input!" << endl;
        }
    } 
    return 0;
}