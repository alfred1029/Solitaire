/* The initiation of table and deck */
#include <iostream>
#include <vector>       // for std::vector
#include <random>       // for std::mt19937
#include <algorithm>    // for std::shuffle
#include "card.h"       // for Card
#include "initTable.h"  // for initTable

using namespace std;

// initialize a random deck
vector<Card> initRandomDeck() {

    // initialize a deck
    vector<Card> deck(52);
    for (int i = 0; i < 52; ++i) {
        deck[i] = {i % 13 + 1, Card::Suit(i / 13), false};
    }

    // shuffle the deck
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);

    //return the deck
    return deck;
}

// initialize a winnable deck (to be implemented)

// initialize the game table
vector<vector<Card>> initTable(vector<Card> &deck){

    // Fill the deck into game table, 7 columns (column 0 - 6), from 1 to 7 cards
    // The last card (size -1) of each column is shown
    // The filling method may need to be changed if we implement the winnable deck
    vector<vector<Card>> table(8);
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j <= i; ++j) {
            table[i].push_back(deck[i*(i+1)/2+j]);
            if (i == j) {
                table[i][j].shown = true;
            }
        }
    }

    // fill the remaining cards into the stock (column 7)
    for (int i = 0; i < 24; ++i) {
        table[7].push_back(deck[28+i]);
    }

    // empty the deck
    deck.clear();

    // return the table
    return table;
}