//
//  Time.h
//  FinalProject
//
//  Created by Guy on 01/04/2024.
//

#ifndef Time_h
#define Time_h
#include <stdio.h>

typedef struct {
    int hour;
    int minute;
} Time;

//--Functions--//
Time getCurrentTime(void);
int isSameTime(const Time t1,const Time t2);

#endif /* Time_h */
