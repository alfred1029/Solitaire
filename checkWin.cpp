//check if the game is won or there are no more available moves
#include<vector>
using namespace std;

//check if the game has won
void checkWin(vector<vector<Card>> &table) {
  
  //if the top card of all stacks (column 8) is K, the game is won
  for (int i = 0; i < 4; i++) {
    if (table[8][i].rank != 13) {
      return false;
    }
  }
  return true;
}


//check if there are no more available moves
void moveAvailable(vector<vector<Card>> &table) {
  
  //if there are unshown cards in the stock, cards can be drawn (i.e. moves are available)
  if (table[7].size() > 0) {
    return true;
  }
  
  //check if cards can be stacked
  else: 
  
  //select two cards being shown from the end of each column
  for (int i = 0; i < 9; i++) {
    
    //skip if the column is empty
    if (table[i].size() > 0) {
      continue;
    }
    
    for (int j = 0; j < 9; j++) {
      
      //skip if the column is empty
      if (table[j].size() == 0) {
        continue;
      }
      
      Card card1 = table[i][table[i].size() - 1];
      Card card2 = table[j][table[j].size() - 1];
        
      //if the card 2 is opposite color and its rank is one less than the card 1's rank
      if (((card1.suit +1)%2 == (card2.suit)%2) && (card1.rank == card2.rank + 1)) {
        return true;
      }
    }
  }
  return false;
}
      
