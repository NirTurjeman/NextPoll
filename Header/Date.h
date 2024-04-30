//
//  Date.h
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//

#ifndef Date_h
#define Date_h

#include <stdio.h>
typedef struct{
    int day;
    int month;
    int year;
    }Date;
typedef unsigned char BYTE;

//--Functions--//
void    getCorrectDate(Date* pDate);
int     checkDate(char* date, Date* pDate);
int     checkDateForElection(char* date, Date* pDate);
void    printDate(const Date* pDate);
int     writeDateToFile(const Date* pDate,FILE* file);
int     readDateFromFile(Date* pDate,FILE* file);
#endif /* Date_h */
