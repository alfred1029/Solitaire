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
    string command="000", previousCommand="000";
    int valid;
    //save the initial process
    saveProcess(table, ptr, cardMap, processes);
    cout << processes.size() << endl;
    // game loop
    while (command != "e")
    {
        // print table and ask for command
        printTable(table, ptr);
        // get command and check if it is valid
        cin >> command;
        cout << command << " "<<previousCommand<<endl;
        //check if command is valid
        valid = checkValid(table, cardMap, ptr, command);

        //detect command and previous command
        if (detectPreviousCommand(command, previousCommand)){
            //delete exceed process
            deleteProcess(table,ptr,cardMap,processes); 
            cout << "delete succeed" << endl;
        }

        cout << "before move++"<<ptr.move<<' '<<processes.size()<<endl;

        // if valid, pass it to corresponding function
        switch (valid){
            case 1:
                // if valid == 1, flip the stock deck
                flipStock(table, ptr);//ptr.move++
                //save process
                saveProcess(table, ptr, cardMap, processes);
                break;
            case 2:
                // if valid == 2, move card to column
                findTarget(table, ptr);
                if (ptr.target == -1){
                    cout << "No possible move!" << endl;
                    break;
                }
                moveCard(table, cardMap, ptr);//ptr.move++
                //save process
                saveProcess(table, ptr, cardMap, processes);
                break;
            case 3:
                cout << "valid = 3" << endl;
                // if valid == 3, move card to stack
                findStack(table, ptr);
                if (ptr.target == -1){
                    cout << "No possible move!" << endl;
                    break;
                }
                moveCard(table, cardMap, ptr);//move++
                //save process
                saveProcess(table, ptr, cardMap, processes);
                break;
            case 4:
                //if valid == 4, redo the process
                if(ptr.move <processes.size())
                    redo(table, ptr, cardMap, processes);
                cout<<"redo successful!"<<endl;
                break;
            case 5:
                //if valid == 5, undo the process
                if(ptr.move >= 0)
                    undo(table, ptr, cardMap, processes);
                cout<<"undo successful!"<<endl;
                break;
            default:
                // if valid == -1, print invalid input
                cout << "Invalid input!" << endl;
        }
        cout<<"after move++"<<ptr.move<<' '<<processes.size()<<endl;
        previousCommand = command;
    } 
    return 0;
}