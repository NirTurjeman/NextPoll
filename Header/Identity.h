//
//  Identity.h
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//

#ifndef Identity_h
#define Identity_h

#include <stdio.h>
#include "Address.h"
#include "Date.h"
typedef struct {
    Address address;
    char* idNumber;
    int phoneNumber;
    Date date;
    char* email;
}Identity;

//--Functions--//
int initIdentity(Identity* identity);
int checkValidIdNumber(const char* idNumber);
int validPhoneNumber(const int phoneNumber);
int changePhoneNumber(int* oldPhoneNumber ,int* newPhoneNumber);
int validEmail(char* email);
int changeEmail(char* oldEmail,char* newEmail);
int getAge(Date birthDay);
void freeIdentity(Identity* identity);
#endif /* Identity_h */
