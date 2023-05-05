/*  The initiation of table and deck */
#include <iostream>
#include <vector>       // for std::vector
#include <random>       // for std::mt19937
#include <algorithm>    // for std::shuffle
#include "card.h"       // for Card
#include "initTable.h"  // for initTable
#include <sstream>
#include <fstream>

using namespace std;

// initialize a random deck
void initRandomDeck(Card deck[]) {

    // initialize a deck
    for (int i = 0; i < 52; ++i) {
        deck[i].rank = i % 13 + 1;
        deck[i].suit = Card::Suit(i / 13);
        deck[i].shown = false;
    }
    // create a random device
    random_device rd;
    mt19937 g(rd());
    // shuffle the deck
    shuffle(deck, deck + 52, g);

}

// initialize a winnable deck (to be debugged)
void initWinnableDeck(Card deck[]){
    ifstream fin;
    fin.open("winningDeck.txt");
    if (fin.fail()){
        cout << "Error in opening file!\nPlease try again!" << endl;
        exit(1);
    }else{
        int randomLine;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 265);
        randomLine = dis(gen);
        string line;
        string word;
        int num = 0;
        // read the line
        randomLine = 1;
        for (int i = 0; i < randomLine; ++i){
            getline(fin, line);
            // convert the line to a card
            istringstream iss(line);
            string token;
            if( i == randomLine - 1){
                int j = 0;
                while (getline(iss, token, ',')){
                    // fill the card into the deck
                    num = stoi(token)-1;
                    deck[j].rank = num % 13 + 1;
                    deck[j].suit = Card::Suit(num / 13);
                    deck[j].shown = false;
                    j++;
                }
            }
        }
    }
}

// initialize the game table
void initTable(vector<vector<Card>> &table, vector<CardMap> &cardMap, Card deck[]){

    // Fill the deck into game table, 7 columns (column 0 - 6), from 1 to 7 cards
    // The last card (size -1) of each column is shown
    // The filling method may need to be changed if we implement the winnable deck
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j <= i; ++j) {
            // fill the card into the table
            table[i].push_back(deck[i*(i+1)/2+j]);
            // fill the cardMap with the card
            cardMap[table[i].back().rank-1 + table[i].back().suit*13] = {i, j};
            // show the last card
            if (i == j) {
                table[i][j].shown = true;
            }
        }
    }
    // fill the remaining cards into the stock (column 7)
    for (int i = 0; i < 24; ++i) {
        table[7].push_back(deck[28+i]);
        // fill the cardMap with the card
        cardMap[deck[28+i].rank-1 + deck[28+i].suit*13] = {7, i};
    }
    // Initialize the stack (column 8) as empty
    for (int i = 0; i < 4; ++i) {
        table[8].push_back({0, Card::Suit(i), false});
    }
}