#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ResidentComm.h"
int initCommunity(ResidentComm* community)
{
    community->residents = NULL;
    community->numOfResidents=0;
    return 1;
}

int addResident(ResidentComm* community)
{
    Person* pPerson = (Person*)malloc(sizeof(Person));
    if (!pPerson)
        return 0;
    if (!initPerson(pPerson))
    {
        freePerson(pPerson);
        free(pPerson);
        return 0;
    }
    community->residents = (Person**)realloc(community->residents,(community->numOfResidents + 1) * sizeof(Person*));
    if (!community->residents)
    {
        freePerson(pPerson);
        free(pPerson);
        return 0;
    }
    
    community->residents[community->numOfResidents] = pPerson;
    community->numOfResidents++;
    return 1;
    
}

Person** residentsAbove18(ResidentComm* community)
{
    int countAbove18 = 0;
    for (int i = 0; i < community->numOfResidents; i++) {
        if (isAbove18(*community->residents[i])) {
            countAbove18++;
        }
    }
    Person** above18 = (Person**)malloc(countAbove18 * sizeof(Person*));
    if (!above18)
        return 0;
        
    int index = 0;
    for (int i = 0; i < community->numOfResidents; i++) {
        if (isAbove18(*community->residents[i])) {
            above18[index++] = community->residents[i];
        }
    }
    return above18;
}

int findResident(ResidentComm* community,  char* id)
{
    for (int i = 0; i < community->numOfResidents; i++) {
        if (strcmp(community->residents[i]->identity.idNumber, id)==0) {
            return 1;
        }
    }
    return 0;
}

int countResidentsAbove18(ResidentComm* community) {
    int countAbove18 = 0;
    for (int i = 0; i < community->numOfResidents; i++) {
        if (isAbove18(*community->residents[i])) {
            countAbove18++;
        }
    }
    return countAbove18;
}

int canVote(ResidentComm* community, Person* residentToCheck) {
    Person** above18 = residentsAbove18(community);
    if (!above18)
        return 0;
        
    int numOfPeople = countResidentsAbove18(community);
    for (int i = 0; i < numOfPeople; i++) {
        if (strcmp(above18[i]->identity.idNumber, residentToCheck->identity.idNumber)) {
            free(above18);
            return 1;
        }
    }
    free(above18);
    return 0; 
}
void printResident(const Person resident)
{
    printf("Name: %s\n",resident.name);
    printAddress(resident.identity.address);
    printf("ID number: %s\n",resident.identity.idNumber);
    printf("Phone number: %d\n",resident.identity.phoneNumber);
    printDate(&resident.identity.date);
    printf("Email address: %s\n\n",resident.identity.email);
}
void printResidentsArr(const ResidentComm community)
{
    for(int i=0;i<community.numOfResidents;i++)
    {
        printResident(*community.residents[i]);
    }
}
void freePersonArr(ResidentComm* community)
{
    for (int i=0; i < community->numOfResidents; i++)
    {
        freePerson(community->residents[i]);
        free(community->residents[i]);
    }
    free(community->residents);
}



void freeResidentComm(ResidentComm* community)
{
    freePersonArr(community);
}
