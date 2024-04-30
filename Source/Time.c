//
//  Time.c
//  FinalProject
//
//  Created by Guy on 01/04/2024.
//
#include <stdlib.h>
#include "Time.h"
#include <time.h>
#include "Voter.h"
Time getCurrentTime(void) {
    Time currentTime;
    
    time_t rawTime;//time_t and struct tm are data types used in the C standard library
    struct tm *localTime;

    time(&rawTime);
    localTime = localtime(&rawTime);

    currentTime.hour = localTime->tm_hour;
    currentTime.minute = localTime->tm_min;
    return currentTime;
}
int isSameTime(const Time t1,const Time t2)
{
    if(t1.hour == t2.hour && t1.minute == t2.minute)
        return 1;
    return 0;
}
