//
//  partyMember.h
//  FinalProject
//
//  Created by Guy on 01/04/2024.
//

#ifndef partyMember_h
#define partyMember_h
#include <stdio.h>
#include "Person.h"
#include "Date.h"
#include "List.h"
typedef enum {
    eCouncilmember, eCFO, eCEO, eNofMemberTypes
} eMemberType;

static const char* MemberTypeStr[eNofMemberTypes]
        = { "Council member", "CFO", "CEO" };


typedef struct{
    char* name;
    char* idNumber;
    eMemberType type;
    Date        joinDate;
    int         salary;
} PartyMember;

//--Functions--//
int         initMember(PartyMember* member);
void        updateSalary(PartyMember* member);
eMemberType getMemberType(PartyMember* member);
int         getTheSalary(PartyMember* member);
int         isNumeric(char *str);
void        printPartyArr(const LIST* partyMembers);
void        printPartyMember(const void* member);
void        freePartyMember(void* member);
#endif /* partyMember_h */
