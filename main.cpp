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

using namespace std;

// This function will setup the windows
void setupWindow(WINDOW * &topStatus, WINDOW * &stock, WINDOW * &stack, WINDOW * column[], WINDOW * &bottomStatus, WINDOW * &inputWindow){
    topStatus = newwin(1, 90, 0, 0);
    // initialize the stock window with 16 rows and 10 columns, start at (2,0)
    stock = newwin(16, 10, 2, 0);
    // initialize the stack window with 20 rows and 10 columns, start at (2,80)
    stack = newwin(20, 10, 2, 80);
    // initialize the column window 0-6 with 36 rows and 10 columns each, start at (2,10)
    for (int i = 0; i < 7; i++){
        column[0] = newwin(36, 10, 2, (i+1)*10);
    }
    // initialize the bottom status window with 1 row and 90 columns, start at (38,0)
    bottomStatus = newwin(1, 90, 38, 0);
    // initialize the input window with 1 row and 90 columns, start at (39,0)
    inputWindow = newwin(1, 90, 39, 0);
}

// This function will delete the windows
void deleteWindow(WINDOW * &topStatus, WINDOW * &stock, WINDOW * &stack, WINDOW * column[], WINDOW * &bottomStatus, WINDOW * &inputWindow){
    delwin(topStatus);
    delwin(stock);
    delwin(stack);
    for (int i = 0; i < 7; i++){
        delwin(column[i]);
    }
    delwin(bottomStatus);
    delwin(inputWindow);
}

int main(){
    string difficulty = "easy";
    /*
    std::cout << "Please select difficulty: easy, medium, hard, expert" << endl;
    cin >> difficulty;
    if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard" && difficulty != "expert") {
        std::cout << "Invalid difficulty!" << endl;
        return 0;
    }*/
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
    // init start screen GUI
    static WINDOW *logo , *menu , *background, *diffMenu;
    // initialize the logo window with 17 row and 95 columns, start at (3,12)
    logo = newwin(9, 95, 8, 12);
    // initialize the background with 15 row and 40 columns, start at (18,40)
    background = newwin(15, 40, 18, 40);
    // initialize difficulty selection
    diffMenu = newwin(15, 26, 20, 47);
    // refresh the screen
    refresh();
    // print the logo
    printLogo(logo);
    // print the background
    printBackground(background);
    // print the menu
    while (true) {
        // initialize the menu window with 15 row and 40 columns, start at (20,40)
        menu = newwin(15, 26, 20, 47);
        printMenu(menu);
        refresh();
        int diff= printDifficulty(diffMenu);
        if (diff == 0){
            difficulty = "easy";
            break;
        }
        else if (diff == 1){
            difficulty = "medium";
            break;
        }
        else if (diff == 2){
            difficulty = "hard";
            break;
        }
        else if (diff == 3){
            difficulty = "expert";
            break;
        }
        wclear(diffMenu);
    }
    refresh();
    noecho();
    wclear(logo);
    wclear(background);
    wclear(menu);
    endwin();
    

    // store process
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
    string command="000", previousCommand="000", message="Welcome my friend!";
    char input[100];
    int valid;
    //save the initial process
    saveProcess(table, ptr, cardMap, processes);
    std::cout << processes.size() << endl;
    // game loop


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
    noecho();
    // refresh the windows
    refresh();

    // update the top status window
    updateTopStatus(topStatus, ptr);
    // update the stock window
    updateStock(table, stock, ptr);
    // update the column window
    for (int i = 0; i < 7; i++){
        updateColumn(table, column[i], ptr, i);
    }
    // update the stack window
    updateStack(table, stack, ptr);
    // update the bottom status window
    updateBottomStatus(bottomStatus, message);

    //cursor shown
    echo();
    //move the cursor to the input window
    wmove(inputWindow, 0, 0);
    //get user input
    getch();

    while (command == "exit")
    {
        //move the cursor to the input window
        wmove(inputWindow, 0, 0);
        //get user input
        wgetstr(inputWindow, input);

        command = input;

        valid = checkValid(table, cardMap, ptr, input);
/*
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
        */
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
    }
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