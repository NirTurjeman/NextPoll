//
//  Candidate.h
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//

#ifndef Candidate_h
#define Candidate_h

#include <stdio.h>
#include <string.h>
#include "Person.h"
#include "List.h"
#include "PartyMember.h"

typedef struct{
    char* name;
    char* idNumber;
    LIST partyMembers;
    int  numOfMembers;
    size_t votesNumber;
    int candidateNumber;
}Candidate;

//--Functions--//
int           initCandidate(Candidate* pCandidate,int candidateNumber);
int           addPartyMember(Candidate* pCandidate);
void          calculateCandidatePercentage(const size_t candidateVotes, const size_t totalVotesCast);
size_t        calculateTotalSalary(LIST partyMembers);
int           comparePartyMemberById(const void* key1, const void* key2);
void          changePartyMemberTypeById(Candidate* candidate, const char* memberId, eMemberType newType);
void          changePartyMemberSalaryById(Candidate* candidate, const char* memberId,int newSalary);
void          printCandidate(const Candidate candidate);
void          printCandidateArr(const Candidate* arr,int size);
void          freeCandidate(Candidate* candidate);
#endif /* Candidate_h */
