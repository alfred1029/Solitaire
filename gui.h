#ifndef GUI_H
#define GUI_H

#include<iostream>
#include<string>
#include"card.h"
#include"initTable.h"
#include"checkInput.h"
#include"move.h"
#include<ncurses.h>

using namespace std;
static char SUIT[4] = {'♦', '♣', '♥', '♠'};
static char RANK[14] = {' ', 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

void drawCardTop(Card &card, WINDOW * &window, int y);
void drawCardBottom(WINDOW * &window, int y);
void updateStock(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr);
void updateStack(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr);
void updateColumn(vector<vector<Card> > &table, WINDOW * &window, Ptr &ptr, int column);
void updateTopStatus(WINDOW * &window, Ptr &ptr);
void updateBottomStatus(WINDOW * &window, char * message);

#endif