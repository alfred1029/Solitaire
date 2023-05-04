/*  checkInput.cpp
    1.  checkValid
    2.  findTarget    
    3.  findStack
    4.  convertCard
*/

#include "card.h"
#include "checkInput.h"
#include <vector>
#include <string>

using namespace std;

/*  Function to check if the input is valid and pass it to corresponding function */
int checkValid(vector<vector<Card>> &table, vector<CardMap> &cardMap, int &column, int &row, string input){
    int valid = -1;
    if (input.substr(0, 2) == "10"){
                input = 't' + input.substr(2); 
    }
    switch (input.length()){
        case 1:
            // if input == 'f', flip the stock
            if (tolower(input[0]) == 'f'){
                // valid = 1 means flip deck
                valid = 1;
            }
            break;
        case 2:
            // convert the string card to integer
            int card = convertCard(input);
            // if the card is valid
            if (card != -1){
                column = cardMap[card].column;
                row = cardMap[card].row;
                // valid = 2 means move card to column
                valid = 2;
            }
            break;
        case 3:
            if (tolower(input[2]) != 's')
                break; 
            // if input[2] == s
            int card = convertCard(input);
            // if the card is valid
            if (card != -1){
                column = cardMap[card].column;
                row = cardMap[card].row;
                // valid = 3 means move card to stack
                valid = 3;
            }
    }
    return valid;
}

/* Function to find the stack */
int findStack (vector<vector<Card>> &table, int &column, int &row){
    int target = -1;
    Card::Suit suit = table[column][row].suit;
    // if the rank is one greater than card in stack with the same suit, set target to the stack
    if (table[8][suit].rank == table[column][row].rank - 1){
        target = 8;
    }
    return target;
}

/* Function to find the target column */
int findTarget (vector<vector<Card>> &table, int &column, int &row){
    int target = -1;
    for (int i = 0; i < 7 && target == -1; ++i){
        // search for the column that is not empty
        if (table[i].size() > 0){
            // if the card is opposite color and rank is one less than the last card in the column, set target to the column
            if ((table[i][table[i].size() - 1].suit -1)%2 == (table[column][row].suit)%2 && table[i][table[i].size() - 1].rank == table[column][row].rank + 1){
                target = i;
            }
        }
        //  else check if the card is king, set target to the column
        else{
            if (table[column][row].rank == 13){
                target = i;
            }
        }
    }
    // if target is still -1, check if it can be moved to the stack
    if (target == -1){
        target = findStack(table, column, row);
    }
    return target;
}

/* Function to convert card to integer */
int convertCard (string card){
    int rank = -1;
    int suit = -1;
    switch (card[0]){
        case 'a':
            rank = 1;
            break;
        case '2':
            rank = 2;
            break;
        case '3':
            rank = 3;
            break;
        case '4':
            rank = 4;
            break;
        case '5':
            rank = 5;
            break;
        case '6':
            rank = 6;
            break;
        case '7':
            rank = 7;
            break;
        case '8':
            rank = 8;
            break;
        case '9':
            rank = 9;
            break;
        case 't':
            rank = 10;
            break;
        case 'j':
            rank = 11;
            break;
        case 'q':
            rank = 12;
            break;
        case 'k':
            rank = 13;
            break;
    }
    switch (tolower(card[1])){
        case 'd':
            suit = 0;
            break;
        case 'c':
            suit = 1;
            break;
        case 'h':
            suit = 2;
            break;
        case 's':
            suit = 3;
            break;
    }
    if (rank == -1 || suit == -1){
        return -1;
    }
    return rank + suit * 13;
}


