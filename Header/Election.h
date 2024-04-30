//
//  election.h
//  FinalProject
//
//  Created by Guy on 01/04/2024.
//

#ifndef election_h
#define election_h

#include <stdio.h>
#include <stdlib.h>
#include "VoterManager.h"
#include "Candidate.h"
#include "Date.h"

typedef struct
{
    VoterManager* voters;
    Candidate*   allCandidates;
    Date          electionDate;
    int           isElectionOpen;
    int           numOfCandidates;
} Election;


//--Functions--//

void         initElection(Election* pElection);
int          addCandidate(Election* pElection);// for the admins
int          generateVoterTurnoutReport(Election* pElection);
int          totalVotes(Election* pElection);
Candidate*   findCandidateByID(Election* pElection, char* ID);
void         printElection(const Election election);
void         freeCandidateArr(Candidate* arr, int size);
void         freeVoterManagerArr(VoterManager* pManager);
void         freeElection(Election* pElection);
#endif /* election_h */
