//
//  AdminManager.c
//  FinalProject
//
//  Created by Guy on 03/04/2024.
//
#include <stdlib.h>
#include <string.h>
#include "AdminManager.h"
#include "VoterManager.h"
void initAdminManager(AdminManager* pAdmins)
{
    pAdmins->adminsArr=NULL;
    pAdmins->adminsCount=0;
}

int addAdmin(AdminManager* admins) {
    Admin* pAdmin = (Admin*)malloc(sizeof(Admin));
    if (pAdmin == NULL) {
        return 0;
    }

    if (!initAdmin(pAdmin)) {
        free(pAdmin);
        return 0;
    }

    Admin* newAdminsArr = (Admin*)realloc(admins->adminsArr, (admins->adminsCount + 1) * sizeof(Admin));
    if (newAdminsArr == NULL) {
        free(pAdmin);
        return 0;
    }

    admins->adminsArr = newAdminsArr;
    admins->adminsArr[admins->adminsCount] = *pAdmin;  // Copy the data from pAdmin to the new element
    admins->adminsCount++;

    free(pAdmin); 

    return 1;
}
void printAdmins(const AdminManager admins)
{
    printf("Admins:\n");
    for (int i=0; i<admins.adminsCount; i++)
        printf("Name: %s\nID number: %s\n\n",admins.adminsArr[i].name,admins.adminsArr[i].idNumber);
    
}
Admin*  findAdmin(AdminManager* admins,char* idNumber)
    {
        for(int i=0;i<admins->adminsCount;i++)
            if(!strcmp(admins->adminsArr[i].idNumber,idNumber))
                return &admins->adminsArr[i];
        return NULL;
    }
void freeAdminManager(AdminManager* pAdminManager) {
    if (pAdminManager != NULL) {
        for (int i = 0; i < pAdminManager->adminsCount; i++) {
            freeAdmin(&(pAdminManager->adminsArr[i]));
        }
        free(pAdminManager->adminsArr);
    }
}
