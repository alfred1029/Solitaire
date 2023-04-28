#ifndef GUITEMP_H
#define GUITEMP_H

#include<iostream>
#include<string>
#include"card.h"
#include"initTable.h"

using namespace std;

void printTable(vector<vector<Card>> &table, int move, int score);
string getString(Card &t);

#endif