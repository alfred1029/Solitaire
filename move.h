#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include "card.h"

using namespace std;

void flipStock(vector<vector<Card>> &table);
void moveCard(vector<vector<Card>> &table, vector<CardMap> &cardMap, int column, int row, int target);

#endif