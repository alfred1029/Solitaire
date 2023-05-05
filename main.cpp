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
void setupWindow(WINDOW * &topStatus, WINDOW * &stock, WINDOW * &stack, WINDOW * column[], WINDOW * &bottomStatus, WINDOW * &input){
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
    input = newwin(1, 90, 39, 0);
}

// This function will delete the windows
void deleteWindow(WINDOW * &topStatus, WINDOW * &stock, WINDOW * &stack, WINDOW * column[], WINDOW * &bottomStatus, WINDOW * &input){
    delwin(topStatus);
    delwin(stock);
    delwin(stack);
    for (int i = 0; i < 7; i++){
        delwin(column[i]);
    }
    delwin(bottomStatus);
    delwin(input);
}

// This function will draw the top part of the card
// ╭─────╮
// │7   ♦│ for 7 of Diamond
void drawCardTop(Card &card, WINDOW * &window, int y){
    // draw the top part of the card
    // if the card is not shown, draw the dashed line
    mvwprintw(window, y, 0, "+----+");
    if(!card.shown){
        mvwprintw(window, y+1, 0, "|    |");
    }
    // if the card is shown, draw the rank and suit
    else{
        mvwprintw(window, y+1, 0, "|%c  %c|", RANK[card.rank], SUIT[card.suit]);
    }
}
// This is temporary main function for development of game functions
int main(){

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
    string command="000", previousCommand="000", message="Welcome my friend!";
    int valid;
    //save the initial process
    saveProcess(table, ptr, cardMap, processes);
    std::cout << processes.size() << endl;
    // game loop

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
    // initialize the top status window with 1 row and 90 columns, start at (0,0)
    static WINDOW *topStatus, *stock, *stack, *column[7], *bottomStatus, *input;
    topStatus = newwin(1, 90, 0, 0);
    // initialize the stock window with 16 rows and 10 columns, start at (2,0)
    stock = newwin(16, 10, 2, 0);
    // initialize the stack window with 20 rows and 10 columns, start at (2,80)
    stack = newwin(20, 10, 2, 80);
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
    input = newwin(1, 90, 39, 0);

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

    getch();

    delwin(topStatus);
    delwin(stock);
    delwin(stack);
    for (int i = 0; i < 7; i++){
        delwin(column[i]);
    }
    delwin(bottomStatus);
    delwin(input);
    endwin();

    /* elements for gui */

    // -----------------initialize the screen-----------------------------

    /*setlocale(LC_ALL,"");
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
    WINDOW *topStatus, *stock, *stack, *column[7], *bottomStatus, *input;
    setupWindow(topStatus, stock, stack, column, bottomStatus, input);
    noecho();
    
    // refresh the windows
    refresh();

    // ------------------update the windows--------------------------------------
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

    refresh();

    // get input
    getch();

    // ------------------close the window--------------------------------------
    // close the windows
    deleteWindow(topStatus, stock, stack, column, bottomStatus, input);
    // end the screen
    endwin();
    */

    while (command != "e")
    {
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
    } 
    return 0;
}