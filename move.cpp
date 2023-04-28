/* Include the move function of card */
#include "card.h"
#include "move.h"
#include <vector>

using namespace std;

/* Function to move the card from column to column */

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


