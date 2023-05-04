/*  move.cpp contain all the movement function of solitaire games 
    1. flipStock
        - flip the stock deck
    2. move
        1. move card(s) from column to column
        2. move card(s) from column to stack
        3. move card(s) from stock to column
        4. move card(s) from stock to stack
        
*/
#include "card.h"
#include "move.h"
#include <vector>
#include <iterator>

using namespace std;

/* Function to flip the stock deck */

void flipStock(vector<vector<Card>> &table){
    // next is the index of next card to be shown
    static int next = 0;
    if (table[7][next].shown == false){
        table[7][next].shown = true;
    }
    // if there are more than 3 cards shown in stock
    if (next - 3 >= 0){
        table[7][next - 3].shown = false;
    }
    // if next is not the last card in stock, ++next
    if (next < table[7].size() - 1){
        ++next;
    }
    // if next is the last card in stock, reset the stock
    else{
        for (int i = 0; next - i >= 0 && i < 3; ++i){
            table[7][next - i].shown = false;
        }
        next = 0;
    }
}

/* Function to move card(s) from column to column*/

void moveCard(vector<vector<Card>> &table, vector<CardMap> &cardMap, int column, int row, int target){
    // fill the taget column with the card(s) from the source column
    if (column < 7){
        if (target == 8){
            // from column to stack
            table[target][table[column][row].suit].rank += 1;
            cardMap[table[column][row].rank-1 + 13*table[column][row].suit] = {target, table[column][row].rank};
        }
        else{ 
            // from column to column
            for (int i = row; i < table[column].size(); ++i){
                table[target].push_back(table[column][i]);
                // update the cardMap
                cardMap[table[column][i].rank-1 + 13*table[column][i].suit] = {target, static_cast<int>(table[target].size())};
            }
        }
        // remove the card(s) from the source column
        table[column].erase(table[column].begin() + row, table[column].end());
        // if the source column is not empty, show the last card
        if (table[column].size() > 0){
            table[column][row - 1].shown = true;
        }
    }
    // fill the target column with the card from the stock
    else{
        if (target == 8){
            // from stock to stack
            table[target][table[column][row].suit].rank += 1;
            // update the cardMap
            cardMap[table[column][row].rank-1 + 13*table[column][row].suit] = {target, table[column][row].rank};
        }
        else{
            // from stock to column
            table[target].push_back(table[column][row]);
            // update the cardMap
            cardMap[table[column][row].rank-1 + 13*table[column][row].suit] = {target, static_cast<int>(table[target].size())};
        }
        // remove the card from the stock
        table[column].erase(table[column].begin() + row);
        // the third previous card in stock is not shown
        if (row - 3 >= 0){
            table[column][row - 3].shown = true;
        }
    }    
}