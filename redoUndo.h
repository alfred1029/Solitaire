#ifndef REDOUNDO_H
#define REDOUNDO_H

#include "card.h"
#include <vector>

using namespace std;

struct singleProcess{
    vector<vector<Card>> table;
    vector<CardMap> cardMap;
    Ptr ptr;
};


void redo(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap, vector<singleProcess> &processes);
void undo(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap, vector<singleProcess> &processes);
void saveProcess(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap, vector<singleProcess> &processes);
void deleteProcess(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap, vector<singleProcess> &processes);

#endif
