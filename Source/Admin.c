//
//  Admin.c
//  FinalProject
//
//  Created by Guy on 03/04/2024.
//

#include "Admin.h"
#include "General.h"
#include "Identity.h"
#include <stdlib.h>
int initAdmin(Admin* pAdmin)
{
    pAdmin->name = getStrExactName("Enter Admin name:");
    pAdmin->idNumber = getStrExactName("Enter id Number:");
    if(!checkValidIdNumber(pAdmin->idNumber))
        return 0;
    return 1;
}
void   freeAdmin(Admin* pAdmin)
{
          if (pAdmin->name != NULL)
              free(pAdmin->name);
          if (pAdmin->idNumber != NULL)
              free(pAdmin->idNumber);
}
