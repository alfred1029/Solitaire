#ifndef CARD_H
#define CARD_H

struct Card{
    // define rank, suit, shown status of each card
    int rank; //1 for A, 11 for J, 12 for Q, 13 for K
    enum Suit {Diamond, Club, Heart, Spade}; //Spade, Club, Heart, Diamond is the winnable deck order
    Suit suit;
    bool shown; //true for shown, false for not shown
};

struct CardMap{
    // define the map of each card
    int column;
    int row;
};

struct Ptr{
    // define the pointer to the table
    int column;
    int row;
    int target;
    int next;
    int move;
    int score;
    // define the constructor
    Ptr(){
        column = 0;
        row = 0;
        target = -1;
        next = 0;
        move = 0;
        score = 0;
    };
    Ptr(int n, int m, int s){
        column = 0;
        row = 0;
        target = -1;
        next = n;
        move = m;
        score = s;
    };
};

#endif
