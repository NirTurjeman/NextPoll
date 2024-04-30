//
//  VoterToFile.h
//  finalProject
//
//  Created by NirTurjeman on 05/04/2024.
//

#ifndef VoterToFile_h
#define VoterToFile_h
#include "VoterManager.h"
#include <stdio.h>

int     readVotersFromTxt(VoterManager* voters, FILE* file);
int     readVotersFromBinary(VoterManager* voters, FILE* file);
int     writeVotersToTxt(const VoterManager* voters,FILE* file);
int     writeVotersToBinary(const VoterManager* voters,FILE* file);
#endif /* VoterToFile_h */
