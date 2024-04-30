//
//  ResidentToFile.h
//  finalProject
//
//  Created by NirTurjeman on 04/04/2024.
//

#ifndef ResidentToFile_h
#define ResidentToFile_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ResidentToFile.h"
#include "ResidentComm.h"
#include "Date.h"

//--Functions--//
int     writeResidentToTxt(const ResidentComm* pResident,const char* fileName);
int     writeResidentToBinary(const ResidentComm* pResident, const char* fileName);
int     writePersonToTxt(const Person* pPerson, FILE* file);
int     writePersonToBinary(const Person* pPerson, FILE* file);
int     readPersonFromTxt(Person* pPerson, FILE* file);
int     readPersonFromBinary(Person* pPerson, FILE* file);
int     readLine(FILE* file, char* buffer, size_t size);
int     readResidentFromTxt(ResidentComm* pResident, const char* fileName);
int     readResidentFromBinary(ResidentComm* pResident, const char* fileName);
#endif /* ResidentToFile_h */
