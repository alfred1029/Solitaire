#ifndef CHECKINPUT_H
#define CHECKINPUT_H

#include "card.h"
#include "checkInput.h"
#include <vector>
#include <string>

using namespace std;

int checkValid(vector<vector<Card>> &table, vector<CardMap> &cardMap, int &column, int &row, string input);
int findStack (vector<vector<Card>> &table, int &column, int &row);
int findTarget (vector<vector<Card>> &table, int &column, int &row);
int convertCard(string Card);

#endif