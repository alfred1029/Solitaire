//to store scores
#include <fstream>
#include <vector>
#include <algorithm>
#include "card.h"
#include "leaderboard.h"

void leaderboard(&p) {
  
  ifstream oldScores;
  ofstream newScores;
  vector<int> temp;
  
  oldScores.open("scores.txt");
  
  //append old scores to the temp vector
  while(oldScores >> oldScore) {
    temp.push_back(oldScore);
  }
  
  //append the new score to the vector
  temp.push_back(p.score);
  
  //sort the scores from highest to lowest
  sort(temp.begin(), temp.end());
  
  //if there are more than 10 score records, remove the lowest score
  if (temp.size() > 10) {
    temp.pop_back();
  }
  
  oldScores.close();
  
  newScores.open("scores.txt");
  
  //update the top scores
  for (int = 0; i < temp.size(); i++) {
    newScores << temp[i] << endl;
  }
  
  newScores.close();
  
  return;
}
