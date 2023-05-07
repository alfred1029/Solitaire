#include<iostream>
#include<string>
#include<vector>
#include "gui.h"
#include "guiTemp.h"
#include "initTable.h"
#include "move.h"
#include "checkInput.h"
#include "card.h"
#include "redoUndo.h"
#include <locale.h>
#include "checkWin.h"
#include "saveLoadFile.h"
#include "leaderboard.h"

using namespace std;

int main(){

    string userName = "My friend";
    string difficulty;
    std::cout << "Please select difficulty: easy, medium, hard, expert" << endl;
    cin >> difficulty;
    if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard" && difficulty != "expert") {
        std::cout << "Invalid difficulty!" << endl;
        return 0;
    }

    //store process
    vector<singleProcess> processes;

    // initialize table, cardMap, deck
    vector<vector<Card>> table(9);
    vector<CardMap> cardMap(52);
    Card * deck = new Card[52];
    // initialize a winnable deck (to be debbuged)
    initWinnableDeck(deck, difficulty);
    initTable(table, cardMap, deck);
    std::cout << "Deck initialized!" << endl;
    // free memory from deck
    delete [] deck;
    deck = nullptr;
    // Ptr p to store the information of the table
    // command to store user input
    // valid to check if command is valid and pass it to corresponding function
    Ptr ptr;
    string command="000", prevCommand="000", message="Welcome my friend! Please enter command:";
    char yesNo;
    int valid;
    //save the initial process
    saveProcess(table, ptr, cardMap, processes);
    // game loop

    // ------------------------------------------ GUI ------------------------------------------
    // ---------------------------------initialize the screen-----------------------------------
    // set locale to support unicode
    setlocale(LC_ALL,"");
    // initialize the screen
    initscr();
    // hide the cursor
    curs_set(0);
    // initialize the color
    start_color();
    // initialize the color pair, RED for hearts and diamonds, BLACK for spades and clubs
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_BLACK, -1);

    // initialize the windows
    static WINDOW *topStatus, *stock, *stack, *column[7], *bottomStatus, *inputWindow;
    // initialize the top status window with 1 row and 90 columns, start at (0,0)
    topStatus = newwin(1, 90, 0, 0);
    // initialize the stock window with 36 rows and 10 columns, start at (2,0)
    stock = newwin(36, 10, 2, 0);
    // initialize the stack window with 36 rows and 10 columns, start at (2,80)
    stack = newwin(36, 10, 2, 80);
    // initialize the column window 0-6 with 36 rows and 10 columns each, start at (2,10)
    column[0] = newwin(36, 10, 2, 10);
    column[1] = newwin(36, 10, 2, 20);
    column[2] = newwin(36, 10, 2, 30);
    column[3] = newwin(36, 10, 2, 40);
    column[4] = newwin(36, 10, 2, 50);
    column[5] = newwin(36, 10, 2, 60);
    column[6] = newwin(36, 10, 2, 70);
    // initialize the bottom status window with 1 row and 90 columns, start at (38,0)
    bottomStatus = newwin(1, 90, 38, 0);
    // initialize the input window with 1 row and 90 columns, start at (39,0)
    inputWindow = newwin(1, 90, 39, 0);
    // refresh the windows
    refresh();

    // update the top status window
    updateTopStatus(topStatus, ptr);
    // update the stock window
    updateStock(table, stock);
    // update the column window
    for (int i = 0; i < 7; i++){
        updateColumn(table, column[i], i);
    }
    // update the stack window
    updateStack(table, stack);
    // update the bottom status window
    updateBottomStatus(bottomStatus, message);

    //cursor shown

    command = listenInput(inputWindow);

    while (true)
    {   
        //get user input
        valid = checkValid(table, cardMap, ptr, command);
        // if the prevCommand is undo or redo, current command is not undo or redo, delete exceed process
        if (valid != -1){
            if (detectPreviousCommand(command, prevCommand)){
                //delete exceed process
                deleteProcess(table,ptr,cardMap,processes); 
            }
        }
        // if command is valid, execute the command
        switch (valid){
            case 1:
                // if valid == 1, flip the stock deck
                flipStock(table, ptr);//ptr.move++
                //save process
                saveProcess(table, ptr, cardMap, processes);
                updateStock(table, stock);
                updateTopStatus(topStatus, ptr);
                break;
            case 2:
                // if valid == 2, move card to column
                findTarget(table, ptr);
                if (ptr.target == -1){
                    message = "No possible move! " + userName + ", Please enter command:";
                    updateBottomStatus(bottomStatus, message);
                    break;
                }
                moveCard(table, cardMap, ptr);//ptr.move++
                //save process
                saveProcess(table, ptr, cardMap, processes);
                updateTopStatus(topStatus, ptr);
                if (ptr.target == 8)
                    updateStack(table, stack);
                else
                    updateColumn(table, column[ptr.target], ptr.target);
                if (ptr.column == 7)
                    updateStock(table, stock);
                else
                    updateColumn(table, column[ptr.column], ptr.column);
                break;
            case 3:
                // if valid == 3, move card to stack
                findStack(table, ptr);
                if (ptr.target == -1){
                    message = "No possible move! " + userName + ", Please enter command:";
                    updateBottomStatus(bottomStatus, message);
                    break;
                }
                moveCard(table, cardMap, ptr);//move++
                //save process
                saveProcess(table, ptr, cardMap, processes);
                updateTopStatus(topStatus, ptr);
                if (ptr.target == 8)
                    updateStack(table, stack);
                else
                    updateColumn(table, column[ptr.target], ptr.target);
                if (ptr.column == 7)
                    updateStock(table, stock);
                else
                    updateColumn(table, column[ptr.column], ptr.column);
                break;
            case 4:
                //if valid == 4, redo the process
                if(ptr.move < processes.size()-1){
                    redo(table, ptr, cardMap, processes);
                    updateTopStatus(topStatus, ptr);
                    // update the stock window
                    updateStock(table, stock);
                    // update the column window
                    for (int i = 0; i < 7; i++){
                        updateColumn(table, column[i], i);
                    }
                    // update the stack window
                    updateStack(table, stack);
                    // update the bottom status window
                    message = "Redo successful! " + userName + ", Please enter command:";
                    updateBottomStatus(bottomStatus, message);
                }
                else{
                    message = "No more redo! " + userName + ", Please enter command:";
                    updateBottomStatus(bottomStatus, message);
                }
                break;
            case 5:
                //if valid == 5, undo the process
                if(ptr.move > 0){
                    undo(table, ptr, cardMap, processes);
                    updateTopStatus(topStatus, ptr);
                    // update the stock window
                    updateStock(table, stock);
                    // update the column window
                    for (int i = 0; i < 7; i++){
                        updateColumn(table, column[i], i);
                    }
                    // update the stack window
                    updateStack(table, stack);
                    // update the bottom status window
                    message = "Undo successful! " + userName + ", Please enter command:";
                    updateBottomStatus(bottomStatus, message);
                    break;
                }
                else{
                    message = "No more Undo! " + userName + ", Please enter command:";
                    updateBottomStatus(bottomStatus, message);
                    break;
                }
            case 6:
                //if valid == 6, exit the game
                message = "My friend, " + userName + ", Are you sure you want to exit? (y/n)";
                updateBottomStatus(bottomStatus, message);
                wclear(inputWindow);
                yesNo = wgetch(inputWindow);
                if (tolower(yesNo) == 'y'){
                    //exit the game
                    message = "Bye! " + userName + ", See you next time!";
                    updateBottomStatus(bottomStatus, message);
                    napms(500);
                    delwin(topStatus);
                    delwin(stock);
                    delwin(stack);
                    for (int i = 0; i < 7; i++){
                        delwin(column[i]);
                        delwin(bottomStatus);
                        delwin(inputWindow);
                        endwin();
                        exit(0);
                    }
                }
                else{
                    message = "Welcome back! " + userName + ", Please enter command:";
                    updateBottomStatus(bottomStatus, message);
                }
                break;
            case 7:
                saveGame(table, ptr, cardMap, processes);
                message = "Game saved!" + userName + ", exit the game? (y/n)";
                updateBottomStatus(bottomStatus, message);
                wclear(inputWindow);
                yesNo = wgetch(inputWindow);
                if (tolower(yesNo) == 'y'){
                    //exit the game
                    message = "Bye! " + userName + ", See you next time!";
                    updateBottomStatus(bottomStatus, message);
                    napms(500);
                    delwin(topStatus);
                    delwin(stock);
                    delwin(stack);
                    for (int i = 0; i < 7; i++){
                        delwin(column[i]);
                        delwin(bottomStatus);
                        delwin(inputWindow);
                        endwin();
                        exit(0);
                    }
                }
                else{
                    message = "Welcome back! " + userName + ", Please enter command:";
                    updateBottomStatus(bottomStatus, message);
                }
                break;
            default:
                // if valid == -1, print invalid input
                message = "Invalid input! " + userName + ", Please enter command:";
                updateBottomStatus(bottomStatus, message);
                break;
        }
        if (checkWin(table)){
            message = "Congratulations! You win! " + userName + ", Restart the game? (y/n)";
            updateBottomStatus(bottomStatus, message);
            wclear(inputWindow);
            yesNo = wgetch(inputWindow);
            if (tolower(yesNo) == 'y'){
                //reset the game
                //resetGame(table, ptr, cardMap, processes);
                // update the top status window
                updateTopStatus(topStatus, ptr);
                // update the stock window 
                updateStock(table, stock);
                // update the column window
                for (int i = 0; i < 7; i++){
                    updateColumn(table, column[i], i);
                }
                // update the stack window
                updateStack(table, stack);
                // update the bottom status window
                message = "Game restarted! " + userName + ", Please enter command:";
                updateBottomStatus(bottomStatus, message);
            }
            else{
                break;
            }
        }
        //save the last command
        prevCommand = command;
        // listen to the user input
        command = listenInput(inputWindow);
    }
 /*       
        // print table and ask for command
        printTable(table, ptr);
        // get command and check if it is valid
        cin >> command;
        std::cout << command << " "<<previousCommand<<endl;
        //check if command is valid
        valid = checkValid(table, cardMap, ptr, command);

        //detect command and previous command
        if (detectPreviousCommand(command, previousCommand)){
            //delete exceed process
            deleteProcess(table,ptr,cardMap,processes); 
            std::cout << "delete succeed" << endl;
        }

        std::cout << "before move++"<<ptr.move<<' '<<processes.size()<<endl;

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
                    std::cout << "No possible move!" << endl;
                    break;
                }
                moveCard(table, cardMap, ptr);//ptr.move++
                //save process
                saveProcess(table, ptr, cardMap, processes);
                break;
            case 3:
                std::cout << "valid = 3" << endl;
                // if valid == 3, move card to stack
                findStack(table, ptr);
                if (ptr.target == -1){
                    std::cout << "No possible move!" << endl;
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
                std::cout<<"redo successful!"<<endl;
                break;
            case 5:
                //if valid == 5, undo the process
                if(ptr.move >= 0)
                    undo(table, ptr, cardMap, processes);
                std::cout<<"undo successful!"<<endl;
                break;
            default:
                // if valid == -1, print invalid input
                std::cout << "Invalid input!" << endl;
        }
        std::cout<<"after move++"<<ptr.move<<' '<<processes.size()<<endl;
        previousCommand = command;
*/
    message = "Bye! " + userName + ", See you next time!";
    updateBottomStatus(bottomStatus, message);
    napms(500);

    // free memory from table
    delwin(topStatus);
    delwin(stock);
    delwin(stack);
    for (int i = 0; i < 7; i++){
        delwin(column[i]);
    }
    delwin(bottomStatus);
    delwin(inputWindow);
    endwin();

    return 0;
}