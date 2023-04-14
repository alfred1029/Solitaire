#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

//structure of each card
struct Card {
    int number; //1 for A, 11 for J, 12 for Q, 13 for K
    string suit;// contian Heart, Diamond, Club and Spade
    bool shown;//ture for shown, false for not shown
};


//Function to initialize the deck
vector<Card> initialization() {
    vector<Card> deck;
    for (int i = 1; i <= 13; i++) {  
        deck.push_back({ i, "Heart", false });
        deck.push_back({ i, "Diamond", false });
        deck.push_back({ i, "Club", false });
        deck.push_back({ i, "Spade", false });
    }
    return deck;
}   
//Function to shuffle the deck
void shuffleDeck(vector<Card> &Deck){
    random_device rd;
    mt19937 g(rd());
    shuffle(Deck.begin(), Deck.end(), g);
}

//Function to deal the cards
void dealCards(vector<Card>& Deck, vector<vector<Card>>& displayCard, vector<Card>& stock){
    // Deal the cards to the displayCard 
    for (int i = 0; i < 7; i++) {
        displayCard.push_back({});
        for (int j = 0; j < i + 1; j++) {
            Card cd = Deck.back();
            Deck.pop_back();
            if(j == i){
                cd.shown = true;
            }
            displayCard[i].push_back(cd);
        }
    }
    // Deal the remaining cards to the stock
    stock = Deck;
}

//Function to print deck and stock
void printDeckAndStock(vector<vector<Card>>& displayCard, vector<Card>& stock) {
    // Print the displayCard
    for (int i = 0; i < 7; i++) {
        cout << "Column " << i+1 << ": ";
        for (int j = 0; j < displayCard[i].size(); j++) {
            if (displayCard[i][j].shown) {
                cout << displayCard[i][j].suit[0] << displayCard[i][j].number << " ";
            }
            else
                cout << "X ";
        }
        cout << endl;
    }
    // Print the stock
    cout << "Stock: ";
    for (int i = 0; i < stock.size(); i++) {
        cout << "X ";
    }
    cout << endl;
}

int main() {
    //Creat and shuffle the deck
    vector<Card> Deck = initialization();
    shuffleDeck(Deck);

    //Deal the cards and whether shown or not
    vector<vector<Card>> displayCard; //vector that contain vectors of Cards (like 2D array)
    vector<Card> stock;
    dealCards(Deck, displayCard, stock);
    
    //Print the board
    printDeckAndStock(displayCard, stock);

    return 0;
}