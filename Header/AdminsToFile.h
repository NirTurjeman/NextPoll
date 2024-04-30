//
//  AdminToFile.h
//  finalProject
//
//  Created by NirTurjeman on 05/04/2024.
//

#ifndef AdminsToFile_h
#define AdminsToFile_h

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "AdminManager.h"
#include "Admin.h"

typedef unsigned char BYTE;
//--Functions--//
int     writeAdminsToTxt(const AdminManager* pManager,const char* fileName);
int     writeAdminsToBinary(const AdminManager* pManager,const char* fileName);
int     readAdminsFromTxt(AdminManager* pManager, const char* fileName);
int     readAdminsFromBinary(AdminManager* pManager, const char* fileName);
#endif /* AdminToFile_h */
