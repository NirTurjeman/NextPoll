//
//  election.c
//  FinalProject
//
//  Created by Guy on 01/04/2024.
//
#include "Election.h"
#include "CandidateToFile.h"
void initElection(Election* pElection)
{
    pElection->allCandidates = NULL;
    getCorrectDate(&pElection->electionDate);
    pElection->isElectionOpen = 1;
    pElection->numOfCandidates = 0;
}
 
int addCandidate(Election* pElection)
{
        Candidate* pCandidate = (Candidate*)malloc(sizeof(Candidate));
        if (!pCandidate)
            return 0;
        if (!initCandidate(pCandidate,pElection->numOfCandidates+1))
        {
            freeCandidate(pCandidate);
            free(pCandidate);
            return 0;
        }
    pElection->allCandidates = (Candidate*)realloc(pElection->allCandidates,(pElection->numOfCandidates + 1) * sizeof(Candidate));
        if (!pElection->allCandidates)
        {
            freeCandidate(pCandidate);
            free(pCandidate);
            return 0;
        }
    pElection->allCandidates[pElection->numOfCandidates] = *pCandidate;
    pElection->numOfCandidates++;
        return 1;
}

int generateVoterTurnoutReport(Election* pElection) {
    if (!pElection || !pElection->voters || !pElection->voters->theVoters) {
        printf("Invalid election or voter data.\n");
        return 0;
    }

    int votersWhoVoted =totalVotes(pElection);
    for (int i = 0; i < pElection->voters->votersCount; ++i) {
        if (pElection->voters->theVoters[i].hasVoted) {
            ++votersWhoVoted;
        }
    }

    
    if (pElection->voters->votersCount > 0) {
        int turnoutPercentage = votersWhoVoted / pElection->voters->votersCount * 100.0;
        printf("Total Voters: %d\n", pElection->voters->votersCount);
        printf("Voters Who Voted: %d\n", votersWhoVoted);
        printf("Voter Turnout: %d%%\n", turnoutPercentage);
    } else {
        printf("No registered voters.\n");
    }

    return 1; 
}


int totalVotes(Election* pElection)
{
    int votersWhoVoted = 0;
    for (int i = 0; i < pElection->voters->votersCount; ++i) {
        if (pElection->voters->theVoters[i].hasVoted) {
            ++votersWhoVoted;
        }
    }
    return votersWhoVoted;
}
Candidate* findCandidateByID(Election* pElection, char* ID)
{
    if (!pElection || pElection->numOfCandidates <= 0 || !ID) {
           return NULL;
       }

       for (int i = 0; i < pElection->numOfCandidates ; i++) {
           if ((strcmp(pElection->allCandidates[i].idNumber , ID) == 0)) {
               return &pElection->allCandidates[i]; // Candidate found.
           }
       }

       return NULL;
}
void printElection(const Election election)
{
    printf("Election:\nElection date: ");
    printDate(&election.electionDate);
    printf("\n");
    if (election.numOfCandidates == 0) {
        printf("There are no candidates!\n");
    }
    for(int i =0 ;i<election.numOfCandidates;i++)
    {
        printf("Candidate:\n%d) ",i+1);
        printCandidate(election.allCandidates[i]);
        printf("Number of votes: %zu \n",election.allCandidates[i].votesNumber);
        printf("\nParty members:\n");
        if (election.allCandidates[i].numOfMembers == 0)
        {
            printf("There are no Members!\n");
            printf("\n\n");
            return;
        }
        printPartyArr(&election.allCandidates[i].partyMembers);
        printf("\n\n");
    }
    
}
void freeCandidateArr(Candidate* arr, int size) {
    generalArrayFunction(arr, size, sizeof(Candidate), (void*)freeCandidate);
    free(arr);
}
void freeVoterManagerArr(VoterManager* pManager) {
    generalArrayFunction(pManager->theVoters, pManager->votersCount, sizeof(Voter), (void*)freeVoter);
    free(pManager->theVoters);
}
void freeElection(Election* pElection)
{
    if(pElection->numOfCandidates>0)
        freeCandidateArr(pElection->allCandidates, pElection->numOfCandidates);
    freeVoterManagerArr(pElection->voters);
    free(pElection->voters);
}

