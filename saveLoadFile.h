#ifndef SAVELOADFILE_H
#define SAVELOADFILE_H

#include <fstream>//work with file
#include <ostream>//write data to file
#include "card.h"//for different card types
#include "redoUndo.h"//for singleProcess tyep

using namespace std;

void saveGame(const vector<vector<Card>> &table, const Ptr &p, const vector<CardMap> &cardMap);
void loadGame(const vector<vector<Card>> &table, const Ptr &p, const vector<CardMap> &cardMap);

#endif
