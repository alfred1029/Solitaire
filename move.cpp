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
#include <iostream>


using namespace std;

/* Function to flip the stock deck */

void flipStock(vector<vector<Card> > &table, Ptr &p){
    // next is the index of next card to be shown
    if (table[7][p.next].shown == false){
        table[7][p.next].shown = true;
    }
    // if there are more than 3 cards shown in stock
    if (p.next - 3 >= 0){
        table[7][p.next - 3].shown = false;
    }
    // if next is not the last card in stock, ++next
    if (p.next < table[7].size() - 1){
        ++p.next;
    }
    // if next is the last card in stock, reset the stock
    else{
        for (int i = 0; p.next - i >= 0 && i < 3; ++i){
            table[7][p.next - i].shown = false;
        }
        p.next = 0;
        if (p.score < 100){
            p.score = 0;
        }
        p.score -= 100;
    }
    ++p.move;
}

/* Function to move card(s) from column to column*/

void moveCard(vector<vector<Card> > &table, vector<CardMap> &cardMap, Ptr &p){
    // fill the taget column with the card(s) from the source column
    if (p.column < 7){
        if (p.target == 8){
            // from column to stack
            table[p.target][table[p.column][p.row].suit].rank += 1;
            cardMap[table[p.column][p.row].rank-1 + 13*table[p.column][p.row].suit] = {p.target, table[p.column][p.row].rank};
            p.score += 15;
        }
        else{ 
            // from column to column
            for (int i = p.row; i < table[p.column].size(); ++i){
                table[p.target].push_back(table[p.column][i]);
                // update the cardMap
                cardMap[table[p.column][i].rank-1 + 13*table[p.column][i].suit] = {p.target, static_cast<int>(table[p.target].size())};
            }
        }
        // remove the card(s) from the source column
        table[p.column].erase(table[p.column].begin() + p.row, table[p.column].end());
        // if the source column is not empty, show the last card
        if (table[p.column].size() > 0){
            if (!table[p.column][p.row - 1].shown){
                table[p.column][p.row - 1].shown = true;
                p.score += 5;
            }
        }
    }
    // fill the target column with the card from the stock
    else{
        if (p.target == 8){
            // from stock to stack
            table[p.target][table[p.column][p.row].suit].rank += 1;
            // update the cardMap
            cardMap[table[p.column][p.row].rank-1 + 13*table[p.column][p.row].suit] = {p.target, table[p.column][p.row].rank};
            p.score += 10;
        }
        else{
            // from stock to column
            table[p.target].push_back(table[p.column][p.row]);
            // update the cardMap
            cardMap[table[p.column][p.row].rank-1 + 13*table[p.column][p.row].suit] = {p.target, static_cast<int>(table[p.target].size())};
            p.score += 5;
        }
        // remove the card from the stock
        table[p.column].erase(table[p.column].begin() + p.row);
        // move the next pointer to the previous card in stock
        for (int i = p.row; i < table[p.column].size(); ++i){
            cardMap[table[p.column][i].rank-1 + 13*table[p.column][i].suit].row -= 1;
        }
        --p.next;
        // the third previous card in stock is not shown
        if (p.next - 3 >= 0){
            table[p.column][p.row - 3].shown = true;
        }
    }
    ++p.move;    
}