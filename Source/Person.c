//
//  Person.c
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//

#include "Person.h"
#include "General.h"
#include <stdlib.h>
int initPerson(Person* pPerson)
{
    pPerson->name = getStrExactName("Enter Person name:");
    if(!initIdentity(&pPerson->identity))
        return 0;
    return 1;
}
char* getName(Person p)
{
    return p.name;
}
char* getIdentityNumber(Person p)
{
    return p.identity.idNumber;
}
int isAbove18(const Person person)
{
    if(getAge(person.identity.date) < 18)
        return 0;
    return 1;
}
void freePerson(Person* pPerson)
{
    free(pPerson->name);
    freeIdentity(&pPerson->identity);
}
