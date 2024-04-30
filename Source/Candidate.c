#include <stdlib.h>
#include "Candidate.h"
#include "General.h"
#define CHECK_NULL(ptr) do { \
        if ((ptr) == NULL) { \
                return 0; \
            } \
        } while (0)


int initCandidate(Candidate* pCandidate,int candidateNumber)
{
    printf("Candidate info:\n");
    pCandidate->name = getStrExactName("Candidate Name:");
    pCandidate->idNumber =getStrExactName("Candidate id:");
    if(!checkValidIdNumber(pCandidate->idNumber))
    {
        pCandidate->idNumber=0;
        printf("Wrong id, need to start over\n");
        return 0;
    }
    if(L_init(&pCandidate->partyMembers) == False)
        return 0;
    pCandidate->numOfMembers =0;
    pCandidate->votesNumber=0;
    pCandidate->candidateNumber=candidateNumber;
    return 1;
}
int addPartyMember(Candidate* pCandidate)
{
    PartyMember *pPartyMember  = malloc(sizeof(PartyMember));
    CHECK_NULL(pPartyMember);
    
    
    if (!initMember(pPartyMember))
    {
        freePartyMember(pPartyMember);
        free(pPartyMember);
        return 0;
    }
    NODE* current = pCandidate->partyMembers.head.next;
    NODE* preCurrent = &pCandidate->partyMembers.head;
    while( current<0)
    {
        preCurrent = current;
        current = current->next;
    }
    if(!L_insert(preCurrent,pPartyMember))
    {
        L_delete(preCurrent->next, freePartyMember);
        return 0;
    }
    pCandidate->numOfMembers++;
    return 1;
}
void calculateCandidatePercentage(const size_t candidateVotes,const size_t totalVotesCast)
{
    printf("My voting precentges are: %.2zu%%\n", (candidateVotes/totalVotesCast)*100);
    return ;
}
size_t calculateTotalSalary(const LIST partyMembers)
{
    size_t salary = 0;
    NODE* pNode = partyMembers.head.next;
    while(pNode->next != NULL)
    {
        salary +=((PartyMember*)pNode->key)->salary;
        pNode = pNode->next;
    }
    return salary;
}
int comparePartyMemberById(const void* key1, const void* key2) {
    const PartyMember* member1 = (const PartyMember*)key1;
    const PartyMember* member2 = (const PartyMember*)key2;
    
    return strcmp(member1->idNumber, member2->idNumber);
}


void changePartyMemberSalaryById(Candidate* candidate, const char* memberId,int newSalary)
{
    const NODE* node = L_find(&(candidate->partyMembers.head), (DATA)memberId, comparePartyMemberById);
    
    if (node != NULL) {
        PartyMember* member = (PartyMember*)node->key;
        
        member->salary = newSalary;
    } else {
        
        printf("Party member with ID '%s' not found in the candidate's list\n", memberId);
    }
}
void printCandidate(const Candidate candidate)
{
    printf("Name: %s\n",candidate.name);
}
void printCandidateArr(const Candidate* arr,int size)
{
    for(int i=0; i< size ;i++)
    {
        printf("%d) ",i+1);
        printCandidate(arr[i]);
    }
}
void freeCandidate(Candidate* candidate)
{
    if (candidate->numOfMembers > 0) {
            L_free(&candidate->partyMembers, freePartyMember);
        } 
}


