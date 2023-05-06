#ifndef GUI_H
#define GUI_H

#include<vector>
#include<string>
#include"card.h"
#include<ncurses.h>

using namespace std;

//static WINDOW *topStatus, *stock, *stack, *column[7], *bottomStatus, *input;
static const wchar_t SUIT[4] = {L'\u2666', L'\u2663', L'\u2665', L'\u2660'};
static char RANK[14] = {' ', 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

//void setupWindow(WINDOW * &topStatus, WINDOW * &stock, WINDOW * &stack, WINDOW * column[], WINDOW * &bottomStatus, WINDOW * &input);
//void deleteWindow(WINDOW * &topStatus, WINDOW * &stock, WINDOW * &stack, WINDOW * column[], WINDOW * &bottomStatus, WINDOW * &input);
void drawCardTop(Card &card, WINDOW * &window, int y);
void drawCardBottom(WINDOW * &window, int y);
void updateStock(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr);
void updateStack(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr);
void updateColumn(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr, int column);
void updateTopStatus(WINDOW * &window, Ptr &ptr);
void updateBottomStatus(WINDOW * &window, string message);

#endif