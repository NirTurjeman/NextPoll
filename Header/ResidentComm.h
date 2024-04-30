//
//  residentComm.h
//  FinalProject
//
//  Created by Guy on 01/04/2024.
//

#ifndef residentComm_h
#define residentComm_h
#include <stdio.h>
#include "Person.h"
typedef struct
{
    Person** residents;
    int numOfResidents;
} ResidentComm;

//--Functions--//
int         initCommunity(ResidentComm* community);
int         addResident(ResidentComm* community);
int         countResidentsAbove18(ResidentComm* community);
Person**    residentsAbove18(ResidentComm* community);
int         findResident(ResidentComm* community,  char* id);
int         canVote(ResidentComm* community, Person* residentToCheck);
void        printResident(const Person resident);
void        printResidentsArr(const ResidentComm community);
void        freePersonArr(ResidentComm* community);
void        freeResidentComm(ResidentComm* community);
#endif /* residentComm_h */
