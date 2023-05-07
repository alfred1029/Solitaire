# ENGG1340 project group 69

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
- 1. Stacks can only be built in ascending sequence. 
(i.e. The rank of a card must be greater than the card below it by 1.)
- 2. All cards in a stack must belong to the same suit. 
- 3. An Ace card can be moved to an empty stack. 

Building a column: 
- 1. Columns can only be built in descending sequence. 
(i.e. The rank of a card must be less than the card below it by 1.)
- 2. Columns must be built in alternating colors of red and black. 
(i.e. A card of suit diamonds/hearts should be stacked on a card of suit clubs/spades, and vice versa.)
- 3. A King card can be moved to an empty column. 

Drawing cards from the stock: 
- 1. Only one card can be drawn at a time. 
- 2. Only the most recently drawn card can be moved. 
- 3. Only the three most recently drawn cards are shown. 
- 4. If the card drawn cannot be placed, the player should move it to the wastepile and draw again. 
- 5. When all cards in the stockpile have been drawn, the wastepile is cycled. 

How to play: 
1. Flip the stock deck 
 -enter 'f' 
2. Move card  
 -enter types {d,c,h,s} for Diamond, Club, Heart, Spade  
 -enter number {2,3,4,5,6,7,8,9,10,j,q,k,a}  
 for example 2d for 2 of Diamond and qc for Queen of Club   
3. Undo  
 -enter 'undo'  
4. Redo  
 -enter 'redo'  
5. Save game progress (Please do not delete the saveGame.txt or else the game progress will be deleted)  
 -enter 'save'  
6. Exit wihout saving  
 -enter 'exit  

Scoring method: 

- +5 points: when a card is moved to a column
- +20 points: when a card is moved to a stack
- -100 points: when the wastepile is recycled

## Game features
List of features: 
- Table setup
- Card movement
- Save game
- Load game
- Redo move
- Undo move
- Scorekeeping
- Leaderboard

## Meeting project requirements 
<details>

<summary>
1. Generation of random game sets or events
</summary>
After the seven columns have been filled in a triangular arrangement, the remaining cards in the deck are shuffled to generate the stockpile, such that cards are drawn in random order. This is implemented using the <random> library to create a random device to shuffle the deck array. 
</details>
<details>

<summary>
2. Data structures for storing game status
</summary>
The position of each card is stored in the struct “CardMap”, containing its column and row. 
The layout of the table is stored using a 2D vector “table”, which contains “Card” variables. Each row in the vector represents a column, the stack, or the stock. Each value in a row stores a “Card”. The struct “Card” contains information about a card’s rank, suit, and whether it is faceup or facedown (i.e. whether it is shown or not). 
</details>
<details>

<summary>
3. Dynamic memory management
</summary>
When the game is played, the 2D vector “table” and struct “CardMap” are updated while the game is running to store the current layout of the table and the current position of each card to reflect the current status of the game. 
</details>
<details>

<summary>
4. File input/output
</summary>
When the game is saved, the game status data is written into a text file. When the game is loaded, the data is read from the text file to construct the table layout. 

When the game ends, the 10 highest historical scores are read from the text file “leaderboard.txt” to form a vector. The new score is appended to the vector. The vector is sorted in descending order and the 10 highest scores in the vector overwrite “leaderboard.txt”. If less than 10 scores are recorded in “leaderboard.txt”, the new score is simply inserted into it in descending order. 
</details>
<details>

<summary>
5. Program codes in multiple files
</summary>
Program functions are stored separately in different files, including “checkInput.cpp”, “checkWin.cpp”, “initTable.cpp”, “leaderboard.cpp”, “main.cpp”, “move.cpp”, “randomPosition.cpp”, etc. 
</details>

## Used C/C++ library list

- ```iostream```  
  for standard input and output 
- ```vector```  
  to store element for example storing the deck, columns etc. 
- ```map```  
  to store element for example mapping leaderboard name with score and mapping the struct Card with its location 
- ```string``` 
- ```ncurses.h```  
  for gui 
- ```menu.h```  
  for gui 
- ```random```  
  for initializing random deck and choosing random winnable deck from data base 
- ```algorithm```  
  mainly using for sorting vector such as the score of leaderboard 
- ```sstream```  
  for performing extraction mainly using isstringstream to splitting text from files 
- ```fstream```  
  for file input and output in initializing winnable deck, saveLoad, leaderboard 
- ```locale.h```  
  for enabling UTF-8 output in ncurses

## Compilation and execution instruction
The is no additional configuration required.
However, running in Windows should be avoided. Only run on Linux/UNIX based systems.
```
make run
```
if the make fail, please install ncurses library:
- MacOS
```brew install ncurses```
- Linux
```sudo apt-get install libncursesw```

## Group members
Cheung Yan Shek, UID: 3036065575, Github username: namelessxxv

Hong Hiu Shun, UID: 3036065422, Github username: THA114514

Hui Lok Samuel, UID: 3036059980, Github username: creampithon

Wong Wai Chung, UID: 3036068618, Github username: alfred1029

Wun Ally Lok Yin, UID: 3036068589, Github username: allywun
