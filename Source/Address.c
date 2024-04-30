//
//  Address.c
//  finalProject
//
//  Created by NirTurjeman on 02/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "Address.h"
#include "General.h"
int initAddress(Address* address)
{
    address->city = getStrExactName("Enter city name: \n");
    address->street = getStrExactName("Enter street name: \n");
    printf("Enter house number: \n");
    scanf("%d",&address->house);
    return 1;
}
int changeAddress(Address* address)
{
    if(!initAddress(address))
        return 0;
    return 1;
}
void printAddress(const Address address)
{
    printf("Address : city: %s , street: %s , house number: %d\n",address.city,address.street,address.house);
}
void freeAddress(Address* address)
{
    free(address->city);
    free(address->street);
}
