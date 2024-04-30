//
//  Admin.h
//  FinalProject
//
//  Created by Guy on 03/04/2024.
//

#ifndef Admin_h
#define Admin_h

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char* name;
    char* idNumber;
}Admin;

//--Functions--//
int    initAdmin(Admin* pAdmin);
void   freeAdmin(Admin* pAdmin);
#endif /* Admin_h */
