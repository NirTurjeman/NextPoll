//
//  Identity.c
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Identity.h"
#include "General.h"
#define CHECK_AND_WARN_IF_FALSE(cond, msg) do { \
    if (!(cond)) { \
        printf("%s\n", (msg)); \
        return 0; \
    } \
} while (0)


int initIdentity(Identity* identity)
{
    if(!initAddress(&identity->address))
        return 0;

    identity->idNumber = getStrExactName("Enter id number: \n");
    CHECK_AND_WARN_IF_FALSE(checkValidIdNumber(identity->idNumber), "Wrong id syntax!");

    printf("Enter phone Number: \n");
    scanf("%d", &identity->phoneNumber);
    CHECK_AND_WARN_IF_FALSE(validPhoneNumber(identity->phoneNumber), "Wrong Phone number syntax!");

    printf("Day of Bith:\n");
    getCorrectDate(&identity->date);

    identity->email = getStrExactName("Enter email address: \n");
    CHECK_AND_WARN_IF_FALSE(validEmail(identity->email), "Wrong email syntax!");

    return 1;
}


int checkValidIdNumber(const char* idNumber)
{
    int sum = 0, digit, i;
     char paddedID[10] = {0};

     if(strlen(idNumber) > 9 || strspn(idNumber, "0123456789") != strlen(idNumber))
         return 0;

     sprintf(paddedID, "%09d", atoi(idNumber));

     for(i = 0; i < 9; ++i) {
         digit = paddedID[i] - '0';
         if(i % 2 == 1) {
             digit *= 2;
             if(digit > 9) digit -= 9;
         }
         sum += digit;
     }

     return sum % 10 == 0;
    return 1;
}
int validPhoneNumber(const int phoneNumber)
{
    if(phoneNumber < 100000000 || phoneNumber >= 1000000000)
        return 0;
    if((phoneNumber / 100000000) != 5)
        return 0;
    return 1;
}
int changePhoneNumber(int* oldPhoneNumber ,int* newPhoneNumber)
{
    if(!validPhoneNumber(*newPhoneNumber))
        return 0;
    else
        oldPhoneNumber = newPhoneNumber;
    return 1;
}
int validEmail(char* email)
{
    int atSymbolCount = 0;
    int dotCount = 0;
    char *atSymbolPtr = NULL;
    char *dotPtr = NULL;

    if (email == NULL || email[0] == '.' || email[strlen(email) - 1] == '.') {
        return 0;
    }

    for (int i = 0; email[i]; i++) {
        if (email[i] == '@') {
            atSymbolCount++;
            atSymbolPtr = &email[i];
        } else if (email[i] == '.') {
            dotCount++;
            dotPtr = &email[i];
        }
    }

    if (atSymbolCount == 1 && dotCount >= 1 && dotPtr > atSymbolPtr) {
        for (int i = 1; email[i]; i++) {
            if (email[i] == '.' && email[i-1] == '.') {
                return 0;
            }
            if (email[i] == '@' && email[i-1] == '.') {
                return 0;
            }
            if (email[i] == '.' && email[i-1] == '@') {
                return 0;
            }
        }
    }
    return 1;
}
int changeEmail(char* oldEmail,char* newEmail)
{
    if(!validEmail(newEmail))
        return 0;
    
    oldEmail = newEmail;
    return 1;
}
int getAge(Date birthDay)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int thisYear = local->tm_year + 1900;
    int thisMonth = local->tm_mon + 1;
    int thisDay = local->tm_mday;
    int age = thisYear - birthDay.year;
    if (birthDay.month > thisMonth) {
        age--;
    } else if (birthDay.month == thisMonth) {
        if (birthDay.day > thisDay) {
            age--;
        }
    }
    return age;
}
void freeIdentity(Identity* identity)
{
    free(identity->idNumber);
    free(identity->email);
    freeAddress(&identity->address);
}
