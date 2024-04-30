#ifndef ElectionToFile_h
#define ElectionToFile_h

#include <stdio.h>
#include "Election.h"

//--Functions--//
int     writeElectionToTxt(const Election* election,const char* electionFile,const char* CandidatesFile);
int     writeElectionToBinary(const Election* election,const char* electionFile,const char*   CandidatesFile);
int     readElectionFromTxt(Election* election,const char* electionFile,const char* CandidatesFile);
int     readElectionFromBinary(Election* election,const char* electionFile,const char* CandidatesFile);
#endif /* ElectionToFile_h */
