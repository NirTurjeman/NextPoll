//
//  Voter.c
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "Voter.h"
#include "Time.h"
void    initVoter(Voter* pVoter)//Define the defualt settings.
{
    pVoter->hasVoted=0;
    pVoter->voteType = eAPP_VOTE;
}

int addVotingTime(Voter* pVoter,Time* votingTime)
{
    Time* temp = (Time*)realloc(pVoter->votingTimes, (pVoter->timeCount + 1) * sizeof(Time));
      if (!temp)
          return 0;
    for(int i = 0;i<pVoter->timeCount;i++)
    {
        if(isSameTime(pVoter->votingTimes[i],*votingTime))
        {
            free(temp);
            return 0;
        }
    }
    pVoter->votingTimes = temp;
    pVoter->votingTimes[pVoter->timeCount] = *votingTime;
    pVoter->timeCount++;
    return 1;
}
void    markAsVoted(Voter* pVoter,Time finalVotingTime)
{
    pVoter->hasVoted = 1;
}
int    deleteVotingTime(Voter* pVoter,Time* votingTime)
{
    int index = -1;
    for(int i = 0;i<pVoter->timeCount;i++)
    {
        if(isSameTime(pVoter->votingTimes[i],*votingTime))
            index = i;
    }
    if(index != -1)
    {
        pVoter->votingTimes[index] = pVoter->votingTimes[pVoter->timeCount];
        pVoter->votingTimes = (Time*)realloc(pVoter->votingTimes,(pVoter->timeCount + -1)*sizeof(Time));
        if(!pVoter->votingTimes)
            return 0;
    }
    return 1;
}
void PrintVoter(const Voter voter)
{
    char* voteStatus;
    if(voter.hasVoted)
        voteStatus = "True";
    else
        voteStatus = "False";
    printf("Name: %s\nID: %s \nVote status: %s\n\n",voter.pPerson->name,voter.pPerson->identity.idNumber,voteStatus);
}


void freeVoter(Voter Voter)
{
    freePerson(Voter.pPerson);
    free(Voter.votingTimes);
}
