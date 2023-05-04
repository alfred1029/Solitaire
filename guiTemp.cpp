#include<iostream>
#include<string>
#include"card.h"
#include"guiTemp.h"

using namespace std;

// GUI for testing
void printTable(vector<vector<Card>> &table, int move = 0, int score = 0) {
    cout << "Move: " << move << "       Score: " << score << endl;
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
        cout << "Column [" << i + 1 << "] : ";
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

// convert card to string
string getString(Card &t) {
    string card;
    switch (t.suit) {
        case Card::Suit::Spade:
            // Spade character: ♠
            card = "♠";
            break;
        case Card::Suit::Heart:
            // Heart character: ♥
            card = "♥";
            break;
        case Card::Suit::Diamond:
            // Diamond character: ♦
            card = "♦";
            break;
        case Card::Suit::Club:
            // Club character: ♣
            card = "♣";
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