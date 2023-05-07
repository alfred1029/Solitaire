/* This file include the function of redo, undo and saveProess*/
#include <iostream>
#include <vector>
#include "card.h" //for Card
#include "redoUndo.h" // singleProcess

bool detectPreviousCommand(string command, string previousCommand){
    //if previous command is undo or redo, and current command is not undo and redo (for example previous command = undo, current command = H7)
    //then we need to delete old processes
    //if previous command is not undo or redo, and current command is any valid command,
    //then don't need to delete old processes, as user just want to undo or redo
    //overall, if previous command is undo or redo, then current command must be undo or redo,
    //otherwise we need to delete old processes.
    if(previousCommand == "undo" && (command != "redo" && command != "undo")){
        //going to delete exceed process
        return true;
    }
    else if(previousCommand == "redo" && (command != "redo" && command != "undo")){
        //going to delete exceed process
        return true;
    }      
    else{
        //not to delete exceed process
        return false;
    }
}
void saveProcess(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap, vector<singleProcess> &processes){
    //for each game loop, we save the game data (cards location, card status and pointer to card) into processes 
    singleProcess newProcess;
    newProcess.table = table;
    newProcess.cardMap = cardMap;
    newProcess.ptr = p;
    processes.push_back(newProcess);
}


void deleteProcess(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap, vector<singleProcess> &processes){
    //when we need to delete old processes, we delete the elements from processes.
    //the elements will be start from the index of current move
    int oldStep = processes.size() - p.move - 1;
    for(int i=0; i<oldStep; i++){
        processes.pop_back();
    }
    
}


void undo(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap, vector<singleProcess> &processes){
    //when user input u, the program will call undo function
    //this function help user return to previous step
    //to implement this function we find the previous step's data from processes
    //then we pass the previous step data to current data
    int move = p.move - 1;
    table = processes[move].table;
    p = processes[move].ptr;
    cardMap = processes[move].cardMap;
}


void redo(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap, vector<singleProcess> &processes){
    //when user input r, the program will call redo function
    //this function help user return to older step
    //to implement this function we find the older step's data from processes
    //then we pass the older step data to current data
    int move = p.move+1;
    table = processes[move].table;
    p = processes[move].ptr;
    cardMap = processes[move].cardMap;
}
