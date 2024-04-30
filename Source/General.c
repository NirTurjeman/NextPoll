//
//  General.c
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "General.h"
char* getStrExactName(const char* msg)
{
    char* str;
    char temp[MAX_STR_LEN];
    printf("%s\t", msg);
    myGets(temp, MAX_STR_LEN);

    str = getDynStr(temp);
    return str;
}
char* getDynStr(char* str)
{
    char* theStr;
    theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if (!theStr)
        return NULL;

    strcpy(theStr, str);
    return theStr;
}

char* myGets(char* buffer, int size)
{
    char* ok;
    if (buffer != NULL && size > 0)
    {
        do {
            ok = fgets(buffer, size, stdin);
        } while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
        if (ok)
        {
            char* back = buffer + strlen(buffer);
            //trim end spaces
            while ((buffer < back) && (isspace(*--back)));
            *(back + 1) = '\0';
            return buffer;
        }
        buffer[0] = '\0';
    }
    return NULL;
}
