#ifndef CARD_H
#define CARD_H

struct Card{
    // define rank, suit, shown status of each card
    int rank; //1 for A, 11 for J, 12 for Q, 13 for K
    enum Suit {Diamond, Club, Heart, Spade};
    Suit suit;
    bool shown; //true for shown, false for not shown
};

struct CardMap{
    // define the map of each card
    int column;
    int row;
};

#endif
