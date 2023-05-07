#include"card.h"
#include <ncurses.h>
#include"gui.h"
#include <vector>
#include <string>
#include "checkInput.h"

using namespace std;

// This function will draw the top part of the card
// ╭─────╮
// │7   ♦│ for 7 of Diamond
void drawCardTop(Card &card, WINDOW * &window, int y){
    // set solor if card red
    if (card.suit%2==0 && card.shown)
        wattron(window, COLOR_PAIR(1));
    // draw the top part of the card
    // if the card is not shown, draw the dashed line
    mvwprintw(window, y, 0, "╭─────╮");
    if(!card.shown){
        mvwprintw(window, y+1, 0, "│     │");
    }
    // if the card is shown, draw the rank and suit
    else{
        if (card.rank == 10){
            mvwprintw(window, y+1, 0, "│10  %lc│", SUIT[card.suit]);  
        }
        else{
            mvwprintw(window, y+1, 0, "│%c   %lc│", RANK[card.rank], SUIT[card.suit]);
        }
    }
    // reset color
    wattroff(window, COLOR_PAIR(1));
}

// This function will draw the rest part of the card, for the card is not under another card
// Pass the <vector<vector<Card>>> table, and the window to draw, the start position of y, the card
// The card will look like this
// │    │
// └────┘
void drawCardBottom(Card &card, WINDOW * &window, int y){
    // set solor if card red
    if (card.suit%2==0 && card.shown)
        wattron(window, COLOR_PAIR(1));
    // draw the rest part of the card
    mvwprintw(window, y, 0, "│     │");
    mvwprintw(window, y+1, 0, "│     │");
    mvwprintw(window, y+2, 0, "╰─────╯");
    // reset color
    wattroff(window, COLOR_PAIR(1));

}
void updateStock(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr){
    // draw the stock deck
    wclear(window);
    int y = 0;
    Card card = {0,Card::Suit(1),false};
    drawCardTop(card, window, y);
    drawCardBottom(card, window, y+2);
    y += 5;
    for (int i = 0; i < table[7].size(); ++i){
        if (table[7][i].shown == true) {
            drawCardTop(table[7][i], window, y);
            card = table[7][i];
            y += 2;
        }
    }
    if (y>5){
        drawCardBottom(card, window, y);
    }
    // refresh the stock window
    wrefresh(window);
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
    wclear(window);
    int y = 0;
    for (int i = 0; i < 4; ++i){
        drawCardTop(table[8][i], window, y);
        drawCardBottom(table[8][i], window, y+2);
        y += 5;
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
    wclear(window);
    int y = 0;
    Card card = {0,Card::Suit(0),false};
    for (int i = 0; i < table[column].size(); ++i){
        drawCardTop(table[column][i], window, y);
        y += 2;
    }
    // draw the rest part of the card
    if (table[column].size() != 0)
        drawCardBottom(table[column].back(), window, y);
    // refresh the column window
    wrefresh(window);
}

// This function will draw the Top status window
// Pass the Ptr &ptr, the move and score

void updateTopStatus(WINDOW * &window, Ptr &ptr){
    // draw the top status window
    // draw the move and score
    wclear(window);
    mvwprintw(window, 0, 0, "Move: %d", ptr.move);
    mvwprintw(window, 0, 20, "Score: %d", ptr.score);
    mvwprintw(window, 0, 55, "SOLITAIRE");
    // refresh the top status window
    wrefresh(window);
}

// This function will draw the bottom status window
// Pass the message string

void updateBottomStatus(WINDOW * &window, string message){
    wclear(window);
    // draw the bottom status window
    mvwprintw(window, 0, 0, message.c_str());
    // refresh the bottom status window
    wrefresh(window);
}

// This function will listen to the keyboard input and output a string
// Pass the window to listen
// Return the string

string listenInput(WINDOW * &window){
    // listen to the keyboard input
    refresh();
    wclear(window);
    char input;
    string temp;
    for (int i = 1; i < 4; ++i){
        input = wgetch(window);
        temp += input;
        wdelch(window);
        switch (i)
        {
            case 1:
                if (temp == "f" || temp == "e" || temp == "u" || temp == "u")
                    return temp;
                break;
            case 2:
                if (convertCard(temp) != -1)
                    return temp;
                break;
            case 3:
                return temp;
            default:
                break;
        }
    }
    wrefresh(window);
    return temp;
}