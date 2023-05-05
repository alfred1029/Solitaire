/* This the gui implementation of solitaire games using ncurses */
#include<iostream>
#include<string>
#include"card.h"
#include"initTable.h"
#include"checkInput.h"
#include"move.h"
#include"gui.h"
#include<ncurses.h>

using namespace std;

//  This function will draw the game table
//  On the top center of the screen, it will show the move and score of the game, the variable is stored in Ptr
//  On the left side of the screen, it will show the stock deck, the shown card of stock deck from top to bottom
//  The variable is stored in Table[7], only show shown = true
//  If the stock deck is empty, it will show a blank space with dashed line
//  On the right side of the screen, it will show the four stacks
//  The variable is stored in Table[8], {0,1,2,3} represents {diamond, club, heart, spade}, if rank = 0, it will show a blank space with dashed line
//  If the stack is empty, it will show a blank card with the corresponding suit
//  In the middle of the screen, it will show the seven columns
//  The variable is stored in Table[0-6]
//  If the column is empty, it will show a blank space with dashed line
//  If the column is not empty, it will show the cards from top to bottom, from index 0 to index size()-1
//  If shown = false, it will show a blank card
//  If shown = true, it will show the corresponding card
//  If the card is under another card, it will only show one line of the card, with the rank and suit if shown = true
//  If the card is on the top, it will show the whole card
//  There is a line output at the bottom of the screen, which will show the error message, if the user's input is invalid
//  The cursor will be on the bottom of the screen, and it will move according to the user's input
//  The allowed user's input is: 'f' for flip stock deck, 'e' for exit the game, 's' for save the game, 'l' for load the game, 'r' for redo, 'u' for undo
//  user can input the rank and suit of the card to move the card, for example, "ad" means involve move the ace of diamond and pass to moveCard function
//  for the allowed input of moveCard function, please refer to convertCard(string) of checkInput.cpp

//  define the windows

int main(){
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

    // initialize the table
    // initialize table, cardMap, deck
    // Ptr p to store the information of the table
    vector<vector<Card> > table(9);
    vector<CardMap> cardMap(52);
    Card * deck = new Card[52];
    Ptr ptr;
    // randomize deck
    initRandomDeck(deck);
    initTable(table, cardMap, deck);
    // free memory from deck
    delete [] deck;
    deck = nullptr;
    // command to store user input
    // valid to check if command is valid and pass it to corresponding function
    string command;
    char * message = new char[90];
    int valid;
    // update the windows
    
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

}

// This function will draw the top part of the card, for the card is under another card
// Pass the <vector<vector<Card>>> table, and the window to draw, the start position of x and y, the column and row of the card
// The card will look like this
// ╭────╮  for shown = false 
// │    │
//  ╭────╮  for shown = true, e.g 7 of spade
//  │7  ♠│
void drawCardTop(Card &card, WINDOW * &window, int y){
    // draw the top part of the card
    // if the card is not shown, draw the dashed line
    if(!card.shown){
        mvwprintw(window, y, 0, "╭────╮");
        mvwprintw(window, y+1, 0, "│    │");
    }
    // if the card is shown, draw the rank and suit
    else{
        mvwprintw(window, y, 0, "╭────╮");
        mvwprintw(window, y+1, 0, "│%c  %c│", RANK[card.rank], SUIT[card.suit]);
    }
}

// This function will draw the rest part of the card, for the card is not under another card
// Pass the <vector<vector<Card>>> table, and the window to draw, the start position of y, the card
// The card will look like this
// |    |
// ╰────╯
void drawCardBottom(WINDOW * &window, int y){
    // draw the rest part of the card
    mvwprintw(window, y, 0, "│    │");
    mvwprintw(window, y+1, 0, "╰────╯");
}

// This function will draw the stock deck
// Pass the <vector<vector<Card>>> table, and the window to draw, Ptr &ptr
// The window will look like this
// ╭────╮
// │    │
// │    │
// ╰────╯
// ╭────╮
// │7  ♠│
// ╭────╮
// │8  ♠│
// ╭────╮
// │9  ♠│
// │    │
// ╰────╯
void updateStock(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr){
    // draw the stock deck
    int y = 0;
    Card card = {0,0,false};
    if (ptr.next != table[7].size()){
        drawCardTop(card, window, y);
        drawCardBottom(window, y+2);
    }
    y += 4;
    for (int i = 0; i < table[7].size(); ++i){
        if (table[7][i].shown == true) {
            drawCardTop(table[7][i], window, y);
            y += 2;
        }
    }
    drawCardBottom(window, y+2);
    // refresh the stock window
    
}

// This function will draw the stack deck
// Pass the <vector<vector<Card>>> table, and the window to draw, Ptr &ptr
// The window will look like this
// ╭────╮
// │   ♦│
// │    │
// ╰────╯
// ╭────╮
// │   ♣│
// │    │
// ╰────╯
// ╭────╮
// │   ♥│
// │    │
// ╰────╯
// ╭────╮
// │   ♠│
// │    │
// ╰────╯
void updateStack(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr){
    // draw the stack deck
    int y = 0;
    for (int i = 0; i < 4; ++i){
        drawCardTop(table[8][i], window, y);
        drawCardBottom(window, y+2);
        y += 4;
    }
    // refresh the stack window
    wrefresh(window);
}

// This function will draw the column deck
// Pass the <vector<vector<Card>>> table, and the window to draw, Ptr &ptr, the column number
// The window will look like this
// ╭────╮
// │    │
// ╭────╮
// │    │
// ╭────╮
// │9  ♠│
// │    │
// ╰────╯

void updateColumn(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr, int column){
    // draw the column deck
    int y = 0;
    Card card = {0,Card::Suit(0),false};
    for (int i = 0; i < table[column].size(); ++i){
        drawCardTop(table[column][i], window, y);
        y += 2;
    }
    // draw the rest part of the card
    if (table[column].size() != 0)
        drawCardBottom(window, y+2);
    // refresh the column window
    wrefresh(window);
}

// This function will draw the Top status window
// Pass the Ptr &ptr, the move and score

void updateTopStatus(WINDOW * &window, Ptr &ptr){
    // draw the top status window
    // draw the move and score
    mvwprintw(window, 0, 0, "Move: %d", ptr.move);
    mvwprintw(window, 0, 20, "Score: %d", ptr.score);
    // refresh the top status window
    wrefresh(window);
}

// This function will draw the bottom status window
// Pass the message string

void updateBottomStatus(WINDOW * &window, char * message){
    // draw the bottom status window
    mvwprintw(window, 0, 0, message);
    // refresh the bottom status window
    wrefresh(window);
}





