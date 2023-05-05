//to generate new leaderboard

#include "card.h"
#include "leaderboard.h"
#include <fstream>
#include <vector>
#include <algorithm>


void leaderboard(Ptr &p) {
  
  ifstream oldScores;
  ofstream newScores;
  
  //create a vector to carry old and new scores to be sorted
  vector<int> temp;
  
  //open old leaderboard
  oldScores.open("scores.txt");
  
  //read all old scores from the leaderboard (read "scores.txt" line by line until its end)
  while(oldScores >> oldScore) {
    
    //append old scores to a temporary vector
    temp.push_back(oldScore);
    
  }
  
  //append the new score to the temporary vector
  temp.push_back(p.score);
  
  //sort the scores in the temporary vector in descending order
  sort(temp.begin(), temp.end());
  
  //keep top 10 scores (if there are more than 10 score records, remove the lowest score)
  if (temp.size() > 10) {
    temp.pop_back();
  }
  
  //close the old leaderboard
  oldScores.close();
  
  //open the new leaderboard, clearing "scores.txt"
  newScores.open("scores.txt");
  
  //append the top scores to the new leaderboard
  for (int i = 0; i < temp.size(); i++) {
    newScores << temp[i] << endl;
  }
  
  newScores.close();
  
  return;
}
