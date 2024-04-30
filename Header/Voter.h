#ifndef Voter_h
#define Voter_h
typedef enum {
    eAPP_VOTE, eMANUAL_VOTE, eASSISTED_APP_VOTE
} VotingType;
#include <stdio.h>
#include "Person.h"
#include "Time.h"
typedef struct {
    Person*     pPerson; //pointer to person
    Time*       votingTimes;//all the times that the voter can be vote
    int         timeCount;//how many times we have
    int         hasVoted;
    VotingType  voteType;//Manual , app , on app with help
    int theVote;
}Voter;

//--Functions--//
void    initVoter(Voter* pVoter);
int     addVotingTime(Voter* pVoter , Time* votingTime);
int     deleteVotingTime(Voter* pVoter,Time* votingTime);
void    markAsVoted(Voter* pVoter,Time finalVotingTime);
void    PrintVoter(const Voter voter);
void    freeVoter(Voter Voter);
#endif /* Voter_h */
