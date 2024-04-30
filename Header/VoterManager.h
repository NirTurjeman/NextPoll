//
//  voterManeger.h
//  FinalProject
//
//  Created by Guy on 01/04/2024.
//

#ifndef voterManeger_h
#define voterManeger_h
#define MAX_VOTERS_PER_HOUR 3
#include <stdio.h>
#include "Voter.h"
#include "ResidentComm.h"
typedef enum {
    eSortByID, eSortByName,eSortByAge, eNoSort
} eSortType;
static const char* SortType[eNoSort+1]
        = { "Sort by ID", "Sort by name","Sort by date", "Not sorted" };

typedef struct{
    Voter*  theVoters;
    int     votersCount;
    eSortType  eType;
} VoterManager;

//--Functions--//
int     initVoterManager(VoterManager* pManager,ResidentComm residentsArr);
void    generateVotingTimes(int* votersPerHour, int maxVotersPerHour, Voter* voter);
int     checkValidTimeToVote(Voter* voter);
int     compareByID(const void* voter1,const void* voter2);
int     compareByName(const void* voter1,const void* voter2);
Voter*  findVoterByID(const VoterManager* pManager,char* ID, int(*compare)(const void*, const void*)) ;
int     compareByAge(const void* voter1,const void* voter2);
int     compareByDate(const Date date1,const Date date2);
int     sortVoter(VoterManager* pManager);
int     findVoter(const VoterManager* pManager);
void    generalArrayFunction(void* arr,int arrSize,size_t typeSize,void (*function)(const void*));
void    printVoterArr(const VoterManager* manager);// all printing function needs to be generics
#endif /* voterManeger_h */
