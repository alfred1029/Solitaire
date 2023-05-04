#ifndef CHECKWIN_H
#define CHECKWIN_H

#include <vector>
#include "card.h"

using namespace std;

//Function to check if the game is won
void checkWin(vector<vector<Card>> &table);
//Function to check if there are no more available moves
void moveAvailable(vector<vector<Card>> &table);

#endif
