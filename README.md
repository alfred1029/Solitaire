# ENGG1340 project group 69
## To do list

1. Deck initialization  (Random init, Import Winnable Deck) 
  - Random init  
  - Import Winnable Deck
2. GUI (Ncurses.h)
  - Added guiTemp.cpp for testing purpose
  - To be implement: Offical GUI
3. Check valid input  (For current GUI - DONE)
4. Card Movement  DONE
  - column to column  
  - column to stack  
  - deck to column  
  - deck to stack  
5. undo redo (undo redo done)
6. Save load  
7. File input output  
8. Check win/ no more available move  (Ally)  
9. Leaderboard  
10. Score  


## Game description
Introduction

Solitaire is a single-player card game. With cards initially arranged in a triangular pattern, the player draws and moves cards to create sequences among seven piles in descending order and alternating colors. Traditionally played on a physical tabletop, our game uses C++ to implement the game with a computerized version. 

Set-up

Solitaire is played with a single standard 52-card deck. At the start of the game, 28 cards are laid out on the table in a triangular layout in seven columns. (i.e. The first and left-most column has one card, the second column has two cards, …, and the seventh and right-most column has seven cards.) The topmost card of each column is shown and placed face up. The stock is formed by remaining cards, which are placed facedown to be drawn. 

Objective

Cards can only be moved according to a set of specific rules. To win the game, build four stacks, each formed by cards of the same suit piled up in ascending order, from Ace to King. 
Alternatively, revealing all cards in a face-up position in the columns would also signify a win, as the face-up cards can easily be moved to form the four complete stacks. 

## Game rules
Building a stack: 
1. Stacks can only be built in ascending sequence. 
(i.e. The rank of a card must be greater than the card below it by 1.)
2. All cards in a stack must belong to the same suit. 
3. An Ace card can be moved to an empty stack. 

Building a column: 
1. Columns can only be built in descending sequence. 
(i.e. The rank of a card must be less than the card below it by 1.)
2. Columns must be built in alternating colors of red and black. 
(i.e. A card of suit diamonds/hearts should be stacked on a card of suit clubs/spades, and vice versa.)
3. A King card can be moved to an empty column. 

Drawing cards from the stock: 
1. Only one card can be drawn at a time. 
2. Only the most recently drawn card can be moved. 
3. Only the three most recently drawn cards are shown. 
4. If the card drawn cannot be placed, the player should move it to the wastepile and draw again. 
5. When all cards in the stockpile have been drawn, the wastepile is cycled. 

Scoring method: 

- +5 points: when a card is moved to a column
- +20 points: when a card is moved to a stack
- -100 points: when the wastepile is recycled

## Game features
List of features: 
- Table setup
- Save game
- Load game
- Redo move
- Undo move
- Card movement
- Scorekeeping
- Leaderboard

How the project requirements are met: 

1. Generation of random game sets or events

After the seven columns have been filled in a triangular arrangement, the remaining cards in the deck are shuffled to generate the stockpile, such that cards are drawn in random order. This is implemented using the <random> library to create a random device to shuffle the deck array. 

2. Data structures for storing game status

The position of each card is stored in the struct “CardMap”, containing its column and row. 
The layout of the table is stored using a 2D vector “table”, which contains “Card” variables. Each row in the vector represents a column, the stack, or the stock. Each value in a row stores a “Card”. The struct “Card” contains information about a card’s rank, suit, and whether it is faceup or facedown (i.e. whether it is shown or not). 

3. Dynamic memory management

When the game is played, the 2D vector “table” and struct “CardMap” are updated while the game is running to store the current layout of the table and the current position of each card to reflect the current status of the game. 

4. File input/output

When the game is saved, the game status data is written into a text file. When the game is loaded, the data is read from the text file to construct the table layout. 

When the game ends, the 10 highest historical scores are read from the text file “leaderboard.txt” to form a vector. The new score is appended to the vector. The vector is sorted in descending order and the 10 highest scores in the vector overwrite “leaderboard.txt”. If less than 10 scores are recorded in “leaderboard.txt”, the new score is simply inserted into it in descending order. 

5. Program codes in multiple files

Program functions are stored separately in different files, including “checkInput.cpp”, “checkWin.cpp”, “initTable.cpp”, “leaderboard.cpp”, “main.cpp”, “move.cpp”, “randomPosition.cpp”, etc. 

## Used C/C++ library list

- iostream
- vector
- string
- map
- ncurses.h
- menu.h
- random
- algorithm
- sstream
- fstream
- locale.h

## Compilation and execution instruction
## Group members
Cheung Yan Shek, UID: 3036065575, Github username: namelessxxv

Hong Hiu Shun, UID: 3036065422  

Hui Lok Samuel, UID: 3036059980, Github username: creampithon

Wong Wai Chung, UID: 3036068618, Github username: alfred1029

Wun Ally Lok Yin, UID: 3036068589, Github username: allywun
