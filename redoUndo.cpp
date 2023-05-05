/* This file include the function of redo, undo and saveProess*/
#include <iostream>
#include <vector>
#include "card.h" //for Card
#include "redoUndo.h" // singleProcess


void saveProcess(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap){
    singleProcess newProcess;
    newProcess.table = table;
    newProcess.cardMap = cardMap;
    newProcess.ptr = p;
    processes.push_back(newProcess);
}


void deleteProcess(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap){
    int oldStep = processes.size() - p.move + 1;
    for(int i=p.move; i<p.move+oldStep; i++){
        processes.pop_back();
    }
    
}


void undo(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap){
    int move = p.move - 1;
    table = processes[move].table;
    p = processes[move].ptr;
    cardMap = processes[move].cardMap;
}


void redo(vector<vector<Card>> &table, Ptr &p, vector<CardMap> &cardMap){
    int move = p.move + 1;
    table = processes[move].table;
    p = processes[move].ptr;
    cardMap = processes[move].cardMap;
}











