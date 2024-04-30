//
//  Address.h
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//

#ifndef Address_h
#define Address_h

#include <stdio.h>
typedef struct{
    char* city;
    char* street;
    int   house;
}Address;

//--Functions--//
int     initAddress(Address* address);
int     changeAddress(Address* address);
void    freeAddress(Address* address);
void    printAddress(const Address address);
#endif /* Address_h */
