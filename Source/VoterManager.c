#include <stdlib.h>
#include <string.h>
#include "VoterManager.h"
#include "General.h"
#include "ResidentComm.h"

int initVoterManager(VoterManager* pManager, ResidentComm residentsArr) {
    int count = countResidentsAbove18(&residentsArr);
        Person** temp = residentsAbove18(&residentsArr);
        pManager->theVoters = (Voter*)malloc(sizeof(Voter) * count);
        if (!pManager->theVoters)
            return 0;

        int votersPerHour[24] = {0}; // based on hashtable

        for (int i = 0; i < count; i++) {
            initVoter(&(pManager->theVoters[i]));
            pManager->theVoters[i].pPerson = temp[i];
            pManager->theVoters[i].votingTimes = (Time*)malloc(sizeof(Time) * 4);
            if (!pManager->theVoters[i].votingTimes) {
                for (int j = 0; j < i; j++) {
                    free(pManager->theVoters[j].votingTimes);
                }
                free(pManager->theVoters);
                return 0;
            }

            generateVotingTimes(votersPerHour, MAX_VOTERS_PER_HOUR, &(pManager->theVoters[i]));
        }

        pManager->votersCount = count;
        pManager->eType = eNoSort; // Assuming eNoSort is the default

        return 1;
}

void generateVotingTimes(int* votersPerHour, int maxVotersPerHour, Voter* voter) {
    voter->timeCount = 4;
    for (int j = 0; j < voter->timeCount; j++) {
        
        int hour;
        do {
            hour = rand() % 15 + 7; // Random number between 7 and 21
        } while (votersPerHour[hour] >= maxVotersPerHour);

        int minute = 0;

        voter->votingTimes[j].hour = hour;
        voter->votingTimes[j].minute = minute;

        votersPerHour[hour]++;
    }
}

int checkValidTimeToVote(Voter* voter)
{
    int counter=0;
    Time realTime = getCurrentTime();
    for (int i=0; i<voter->timeCount; i++) {
        if(voter->votingTimes[i].hour == realTime.hour)
            counter++;
        else if (voter->votingTimes[i].hour-1 == realTime.hour)
            counter++;
    }
    return counter;
}

int compareByID(const void* voter1,const void* voter2)
{
    const Voter voterA = *(const Voter*)voter1;
    const Voter voterB = *(const Voter*)voter2;
    return strcmp(voterA.pPerson->identity.idNumber,voterB.pPerson->identity.idNumber);
}
int compareByName(const void* voter1,const void* voter2)
{
    const Voter voterA = *(const Voter*)voter1;
    const Voter voterB = *(const Voter*)voter2;
    return strcmp(voterA.pPerson->name,voterB.pPerson->name);
}
int compareByAge(const void* voter1,const void* voter2)
{

    const Voter voterA = *(const Voter*)voter1;
    const Voter voterB = *(const Voter*)voter2;
    
    Date dateA = voterA.pPerson->identity.date;
    Date dateB = voterB.pPerson->identity.date;
    
    if (getAge(dateA)>getAge(dateB))
        return 0;

    return 1;
}
int compareByDate(const Date date1,const Date date2)
{
    const Date dateA = date1;
    const Date dateB = date2;
    int dateASum = (dateA.day)+(dateA.year)+(dateA.month);
    int dateBSum = (dateB.day)+(dateB.year)+(dateB.month);
    return dateASum-dateBSum;
}
int sortVoter(VoterManager* pManager)
{
    
        int res;
        printf("Base on what field do you want to sort?\n");
        do
        {
            printf("Enter 1 for %s\nEnter 2 for %s\nEnter 3 for %s\n",SortType[eSortByID],SortType[eSortByName],SortType[eSortByAge]);
            scanf("%d",&res);
        }while(res < 1 || res > 3);
        switch (res) {
            case 1:
                pManager->eType = eSortByID;
                qsort(pManager->theVoters,pManager->votersCount, sizeof(Voter), compareByID);
                break;
            case 2:
                pManager->eType = eSortByName;
                qsort(pManager->theVoters,pManager->votersCount, sizeof(Voter), compareByName);
                break;
            case 3:
                pManager->eType = eSortByAge;
                qsort(pManager->theVoters,pManager->votersCount, sizeof(Voter), compareByAge);
                break;
            case 4:
                pManager->eType = eNoSort;
                return 0;
        }
        return 1;
    }
Voter* findVoterByID(const VoterManager* pManager, char* ID, int(*compare)(const void*, const void*)) {
    Voter* temp = (Voter*)calloc(1, sizeof(Voter));
    temp->pPerson = (Person*)malloc(sizeof(Person));
    temp->pPerson->identity.idNumber = (char*)malloc(strlen(ID) + 1);
    strcpy(temp->pPerson->identity.idNumber, ID);

    for (int i = 0; i < pManager->votersCount; i++) {
        if (compare(&pManager->theVoters[i], temp) == 0) {
            free(temp->pPerson->identity.idNumber);
            free(temp->pPerson);
            free(temp);
            return &pManager->theVoters[i];
        }
    }

    free(temp->pPerson->identity.idNumber);
    free(temp->pPerson);
    free(temp);
    return NULL;
}


int findVoter(const VoterManager* pManager)
{
    Voter* temp = (Voter*)calloc(1, sizeof(Voter));
    temp->pPerson = (Person*)malloc(sizeof(Person));
    Voter* found = NULL;
    int age;
    switch (pManager->eType)
    {
        case eSortByID:
            printf("ID:      ");
            temp->pPerson->identity.idNumber = getStrExactName("Enter id number");
            found = (Voter*)bsearch(temp, pManager->theVoters, pManager->votersCount,sizeof(Voter),compareByID);
            break;
        case eSortByName:
            printf("Name:      ");
            temp->pPerson->name = getStrExactName("Enter name");
            found = (Voter*)bsearch(temp, pManager->theVoters, pManager->votersCount,sizeof(Voter),compareByName);
            break;
        case eSortByAge:
            printf("Age:      ");
            scanf("%d",&age);
            found = (Voter*)bsearch(temp, pManager->theVoters, pManager->votersCount,sizeof(Voter),compareByAge);
            break;
        case eNoSort:
            printf("The search cannot be performed, array not sorted\n");
            return 0;
    }
    if(found)
    {
        printf("Voter found, \n");
        printResident(*found->pPerson);
    }else
        printf("Voter was not found\n");
    return 1;
}
void generalArrayFunction(void* arr,int arrSize,size_t typeSize,void (*function)(const void*))
{
    for(int i=0;i<arrSize;i++)
    {
        function((char*)arr + i*typeSize);
    }
}
void printVoterArr(const VoterManager* manager) {
    printf("Voters:\n");
    generalArrayFunction(manager->theVoters, manager->votersCount, sizeof(Voter),(void*) PrintVoter);
}

