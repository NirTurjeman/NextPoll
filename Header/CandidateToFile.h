//
//  CandidateToFile.h
//  finalProject
//
//  Created by NirTurjeman on 05/04/2024.
//

#ifndef CandidateToFile_h
#define CandidateToFile_h

#include <stdio.h>
#include "Candidate.h"
//--Functions--//
int     writeCandidateToTxt(Candidate* candidate,FILE* file);
int     writeCandidateToBinary(Candidate* candidate,FILE* file);
int     readCandidateFromTxt(Candidate* candidate,FILE* file);
int     readCandidateFromBinary(Candidate* candidate,FILE* file);
#endif /* CandidateToFile_h */
