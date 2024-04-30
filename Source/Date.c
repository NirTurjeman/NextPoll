//
//  Date.c
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//

#include "Date.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"
#include <time.h>
const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define SPECIAL_TAV '/'
void getCorrectDate(Date* pDate)
{
    char date[MAX_STR_LEN];
    int ok = 1;

    do {
        printf("Enter Date [Syntax: dd/mm/yyyy]:\n");
        myGets(date, MAX_STR_LEN);
        ok = checkDate(date, pDate);
        if (!ok)
            printf("Error try again\n");
    } while (!ok);
}
int     checkDate(char* date, Date* pDate)
{
    int day, month, year;
    if (strlen(date) != 10)
        return 0;
    if(date[2] != SPECIAL_TAV || date[5] != SPECIAL_TAV)
        return 0;
    sscanf(date, "%d/%d/%d", &day, &month, &year);
    if (day < 1 || month < 1 || month > 12 || day > DAY_MONTHS[month - 1])
        return 0;
    pDate->day = day;
    pDate->month = month;
    pDate->year = year;
    return 1;
}
int     checkDateForElection(char* date, Date* pDate)
{
   int day, month, year;
   if(!checkDate(date, pDate))
       return 0;
    sscanf(date, "%d/%d/%d", &day, &month, &year);
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int thisYear = local->tm_year + 1900;
    int thisMonth = local->tm_mon + 1;
    int thisDay = local->tm_mday;
    
    if(pDate->year < (local->tm_year + 1900))
        return 0;
    else if (year == thisYear && month < thisMonth)
        return 0;
    else if (year == thisYear && month == thisMonth && day < thisDay)
        return 0;
    
    pDate->day = day;
    pDate->month = month;
    pDate->year = year;
    return 1;
}
void printDate(const Date* pDate)
{
    printf("Date: %d/%d/%d\n", pDate->day, pDate->month, pDate->year);
}

int writeDateToFile(const Date* pDate,FILE* file)
{
    if(!file)
        return 0 ;
    
    BYTE data[3];
    data[0] = pDate->year >> 7;
    data[1] = (pDate->month >> 3) | (pDate->year << 1);
    data[2] = pDate->day | (pDate->month << 5);
    
    if(fwrite(data,sizeof(BYTE),3,file) !=3)
    {
        fclose(file);
        return 0;
    }
    return 1;
}

int readDateFromFile(Date* pDate,FILE* file)
{
    if(!file)
        return 0 ;
    
    BYTE data[3];
    if(fread(data,sizeof(char),3,file) != 3)
    {
        fclose(file);
        return 0;
    }
    pDate->year = (data[1] >> 1) | ((data[0] & 0xF) << 7 );
    pDate->month = (data[2] >> 5) | ((data[1] & 0x1) << 3 );
    pDate->day = data[2] & 0x1F;    
    return 1;
}
