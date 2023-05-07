#include<iostream>
#include<string>
#include"card.h"
#include"guiTemp.h"

using namespace std;

// This is the GUI for testing purpose, it will print the table with stock deck, stack deck and 7 columns, the score and move
// Input: vector<vector<Card>> &table, the table to print
//        Ptr &p, struct Ptr defined in initTable.h, contains the score and move
// Output: Void, no modification of elements, only cout the table, score and move
void printTable(vector<vector<Card>> &table, Ptr &p) {
    cout << "Move: " << p.move << "       Score: " << p.score << endl;
    cout << "Stack: ";
    for (int i = 0; i < 4; ++i){
            cout << getString(table[8][i]) << "  ";
    }
    cout << endl;
    cout << "Stock: ";
    for (int i = 0; i < table[7].size(); ++i){
        if (table[7][i].shown == true) {
            cout<< getString(table[7][i]) << "  ";
        }
    }
    cout << endl;
    for (int i = 0; i < 7; ++i) {
        cout << "Column [" << i << "] : ";
        for (int j = 0; j < table[i].size(); ++j) {
            if (table[i][j].shown == true) {
                cout << getString(table[i][j]) << "  ";
            }
            else {
                cout << "X  ";
            }
        }
        cout << endl;
    }
    cout << "Please enter command: ";
}

// getString convert struct Card t to string
// Input: Card &t, the card to convert
// Output: string, the string representation of the card
string getString(Card &t) {
    string card;
    switch (t.suit) {
        case Card::Suit::Spade:
            // Spade character: ♠
            card = "S";
            break;
        case Card::Suit::Heart:
            // Heart character: ♥
            card = "\033[1;31mH\033[0m";
            break;
        case Card::Suit::Club:
            // Club character: ♣
            card = "C";
            break;
        case Card::Suit::Diamond:
            // Diamond character: ♦
            card = "\033[1;31mD\033[0m";
            break;
    }
    switch (t.rank) {
        case 0:
            card += " ";
            break;
        case 1:
            card += "A";
            break;
        case 11:
            card += "J";
            break;
        case 12:
            card += "Q";
            break;
        case 13:
            card += "K";
            break;
        default:
            card += to_string(t.rank);
            break;
    }
    return card;
}