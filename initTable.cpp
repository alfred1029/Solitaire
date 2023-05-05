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
void initWinnableDeck(Card deck[], string difficulty){
    ifstream fin;
    fin.open("winningDeck.txt");
    if (fin.fail()){
        cout << "Error in opening file!\nPlease try again!" << endl;
        exit(1);
    }else{
        int randomLine;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1501, 1871);
        if (difficulty == "easy"){
            uniform_int_distribution<> dis(0, 200);
        }
        else if(difficulty == "medium"){
            uniform_int_distribution<> dis(201, 800);
        }
        else if(difficulty == "hard"){
            uniform_int_distribution<> dis(801, 1500);
        }
        randomLine = dis(gen);
        string line;
        string word;
        int num = 0;
        // read the line
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
                    // the code initially change 1 to Ace, 2 to 2, 13 to King, etc.
                    // but the winnableDeck.txt file is using 1 to 2, 2 to 3, 12 to K, 13 to Ace, etc.
                    //Diamond, Club, Heart, Spade(to be changed)
                    if (num / 13 == 0){
                        num += 39;
                    }else if (num / 13 == 3){
                        num -= 39;
                    }
                    deck[j].suit = Card::Suit(num / 13); //0-12, 13-25, 26-38, 39-51 to (Spades, Clubs, Hearts, then Diamonds)
                    num = num+1 % 13;
                    deck[j].rank = num % 13 + 1;
                    deck[j].shown = false;
                    j++;
                }
            }
        }
    }
    fin.close();
}

// initialize the game table
void initTable(vector<vector<Card>> &table, vector<CardMap> &cardMap, Card deck[]){

    // Fill the deck into game table, 7 columns (column 0 - 6), from 1 to 7 cards
    // The last card (size -1) of each column is shown
    // The filling method may need to be changed if we implement the winnable deck
    // fill the remaining cards into the stock (column 7)

    for(int i = 0; i<7; ++i){
        for (int j = i; j < 7; ++j){
            // fill the card into the table
            table[j].push_back(deck[27-(7*i-i*(i+1)/2+j)]);
            // fill the cardMap with the card
            cardMap[table[j].back().rank-1 + table[j].back().suit*13] = {j,i};
            // show the last card
            if (j == i){
                table[i][j].shown = true;
            }
        }
    }

    for (int i = 0; i < 24; ++i) {
        table[7].push_back(deck[i+28]);
        // fill the cardMap with the card
        cardMap[deck[i+28].rank-1 + deck[i+28].suit*13] = {7, i};
    }
    // Initialize the stack (column 8) as empty
    for (int i = 0; i < 4; ++i) {
        table[8].push_back({0, Card::Suit(i), false});
    }
}