#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "PartyMember.h"
#include "Date.h"
#include "General.h"

int initMember(PartyMember* member) 
{
    int res = 0;
    printf("Member info:\n");
    member->name = getStrExactName("Member Name:");
    while(!res)
    {
        member->idNumber = getStrExactName("Member id:");
        res =checkValidIdNumber(member->idNumber);
        if(!res)
            printf("Wrong id!,Try again");
    }
    printf("Join date:\n");
    getCorrectDate(&member->joinDate);
    member->type = getMemberType(member);
    updateSalary(member);
    return 1;
}
eMemberType getMemberType(PartyMember* member)
{
    int option;
    printf("\n\n");
    do {
        printf("Please enter one of the following types\n");
        for (int i = 0; i < eNofMemberTypes; i++)
            printf("%d for %s\n", i, MemberTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNofMemberTypes);
    getchar();
    return (eMemberType) option;
}
int getTheSalary(PartyMember* member) {
    char salaryStr[20];
    int salary;
    getchar();
    while (1) {
        printf("please enter the salary for %s:", member->name);
        getchar();
        fgets(salaryStr, sizeof(salaryStr), stdin);
        if (strlen(salaryStr) > sizeof(int)) {
            printf("Input is too long, enter the real salary.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        if (!isNumeric(salaryStr)) {
            printf("Invalid input. Please enter a valid value.\n");
            continue;
        }
        salary = atoi(salaryStr);
        break;
    }
    return salary;
}
int isNumeric(char *str)
{
    char* dst = str;
    for (char* src = str; *src != '\0'; src++) {
        *dst = *src;
        if (*src != ',') 
            dst++;
        if (!isdigit(*str))
            return 0;
    }
    *dst = '\0';
        return 1;
}

void updateSalary(PartyMember* member)
{
    int x = getTheSalary(member);
    member->salary = x;
}
void printPartyArr(const LIST* partyMembers)
{
    L_print(partyMembers,printPartyMember);
}
void printPartyMember(const void* member)
{
    PartyMember* partyMember = ((PartyMember*)member);
    printf("Name:%s\nType: %s\nJoin date:",partyMember->name,MemberTypeStr[partyMember->type]);
    printDate(&partyMember->joinDate);
    printf("Salary:%d\n\n",partyMember->salary);
}
void freePartyMember(void* member)
{
    PartyMember* pMember = (PartyMember*)member;
    if (pMember != NULL) {
        if (pMember->name != NULL) {
            free(pMember->name);
            pMember->name = NULL;
        }
        
        if (pMember->idNumber != NULL) {
            free(pMember->idNumber);
            pMember->idNumber = NULL;
        }
        
        free(pMember);
    }
}
