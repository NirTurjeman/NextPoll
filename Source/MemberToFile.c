//
//  MemberToFile.c
//  finalProject
//
//  Created by NirTurjeman on 05/04/2024.
//

#include "MemberToFile.h"
#include "ResidentToFile.h"
#define MAX_LEN 255
int readMemberFromTxt(PartyMember* member,FILE* file)
{
    int readValue = -1;
    eMemberType memberType;
    if (fscanf(file, "%d\n", &readValue) != 1)
        return 0;
    else
    {
        memberType = (eMemberType)readValue;
        member->type = memberType;
    }
     Date date;
     if (fscanf(file, "%d %d %d\n", &date.year, &date.month, &date.day) != 3)
         return 0;
     member->joinDate = date;
     if (fscanf(file, "%d\n", &member->salary) != 1)
         return 0;
    
    char buffer[MAX_LEN] = {0};
    if (fgets(buffer, (int)sizeof(buffer), file) == NULL)
        return 0;
    buffer[strcspn(buffer, "\r\n")] = '\0';
    member->name = strdup(buffer);
    
    char buffer1[MAX_LEN] = {0};
    if (fgets(buffer1, (int)sizeof(buffer1), file) == NULL)
        return 0;
    buffer[strcspn(buffer, "\r\n")] = '\0';
    member->idNumber = strdup(buffer1);
    return 1;
}
int readMemberFromBinary(PartyMember* member, FILE* file) {
    if (fread(&member->type, sizeof(eMemberType), 1, file) != 1) {
        return 0;
    }

    if (!readDateFromFile(&member->joinDate, file)) {
        return 0;
    }

    if (fread(&member->salary, sizeof(int), 1, file) != 1) {
        return 0;
    }

    int nameLength;
    if (fread(&nameLength, sizeof(int), 1, file) != 1) {
        return 0;
    }
    char* nameBuffer = (char*)malloc(nameLength + 1);
    if (nameBuffer == NULL) {
        return 0;
    }
    if (fread(nameBuffer, sizeof(char), nameLength, file) != nameLength) {
        free(nameBuffer);
        return 0;
    }
    nameBuffer[nameLength] = '\0';
    member->name = nameBuffer;

    int idLength;
    if (fread(&idLength, sizeof(int), 1, file) != 1) {
        free(nameBuffer);
        return 0;
    }
    char* idBuffer = (char*)malloc(idLength + 1);
    if (idBuffer == NULL) {
        free(nameBuffer);
        return 0;
    }
    if (fread(idBuffer, sizeof(char), idLength, file) != idLength) {
        free(nameBuffer);
        free(idBuffer);
        return 0;
    }
    idBuffer[idLength] = '\0';
    member->idNumber = idBuffer;

    return 1;
}
int writeMemberToTxt(const PartyMember* member,FILE* file)
    {
        fprintf(file, "%d\n",member->type);
        Date date = member->joinDate;
        fprintf(file, "%d %d %d\n", date.year, date.month, date.day);
        fprintf(file, "%d\n",member->salary);
        fprintf(file, "%s\n",member->name);
        fprintf(file, "%s\n",member->idNumber);
        return 1;
    }
int writeMemberToBinary(const PartyMember* member, FILE* file) {
    if (fwrite(&member->type, sizeof(eMemberType), 1, file) != 1) {
        return 0;
    }

    if (!writeDateToFile(&member->joinDate, file)) {
        return 0;
    }

    if (fwrite(&member->salary, sizeof(int), 1, file) != 1) {
        return 0;
    }

    int nameLength = (int)strlen(member->name);
    if (fwrite(&nameLength, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(member->name, sizeof(char), nameLength, file) != nameLength) {
        return 0;
    }

    int idLength = (int)strlen(member->idNumber);
    if (fwrite(&idLength, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(member->idNumber, sizeof(char), idLength, file) != idLength) {
        return 0;
    }

    return 1;
}
