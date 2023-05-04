#ifndef CHECKINPUT_H
#define CHECKINPUT_H

#include "card.h"
#include "checkInput.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*  Function to check if the input is valid and pass it to corresponding function */
int checkValid(vector<vector<Card>> &table, vector<CardMap> &cardMap, Ptr &p, string input);
/*  Function to find the stack */
void findStack (vector<vector<Card>> &table, Ptr &p);
/*  Function to find the target */
void findTarget (vector<vector<Card>> &table, Ptr &p);
/*  Function to convert card to integer */
int convertCard(string input);

#endif