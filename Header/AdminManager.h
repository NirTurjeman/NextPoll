//
//  AdminManager.h
//  FinalProject
//
//  Created by Guy on 03/04/2024.
//

#ifndef AdminManager_h
#define AdminManager_h

#include <stdio.h>
#include "Admin.h"
typedef struct {
    Admin* adminsArr;
    int adminsCount;
}AdminManager;

//--Functions--//
void    initAdminManager(AdminManager* pAdmins);
int         addAdmin(AdminManager* admins);
Admin*      findAdmin(AdminManager* admins,char* idNumber);
void        printAdmins(const AdminManager admins);
void        freeAdminManager(AdminManager* pAdminManager);
#endif /* AdminManager_h */
