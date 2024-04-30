//
//  Person.h
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//

#ifndef Person_h
#define Person_h
#define OLD_MAN 80 //we are define the age of old man to 80
#include <stdio.h>
#include "Identity.h"
typedef struct{
    char* name;
    Identity identity;
}Person;

//--Functions--//
int     initPerson(Person* pPerson);
char*   getName(Person p);
char*   getIdentityNumber(Person p);
void    freePerson(Person* pPerson);
int     isAbove18(const Person Person);
#endif /* Person_h */
