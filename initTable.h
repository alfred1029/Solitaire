#ifndef INITTABLE_H
#define INITTABLE_H

#include <vector>
#include "card.h"

using namespace std;

vector<Card> initRandomDeck();
vector<vector<Card>> initTable(vector<Card> &deck);

#endif