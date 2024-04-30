//
//  MemberToFile.h
//  finalProject
//
//  Created by NirTurjeman on 05/04/2024.
//

#ifndef MemberToFile_h
#define MemberToFile_h
#include "PartyMember.h"
#include "Date.h"
#include <stdio.h>
int     readMemberFromTxt(PartyMember* member,FILE* file);
int     readMemberFromBinary(PartyMember* member, FILE* file);
int     writeMemberToTxt(const PartyMember* member,FILE* file);
int     writeMemberToBinary(const PartyMember* member,FILE* file);
#endif /* MemberToFile_h */
