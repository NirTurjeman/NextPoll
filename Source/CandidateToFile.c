#include "CandidateToFile.h"
#include "MemberToFile.h"
#include "ResidentToFile.h"
#define MAX_LEN 255
int writeCandidateToTxt(Candidate* candidate,FILE* file)
{
    NODE* pNode = &candidate->partyMembers.head;
        fprintf(file, "%d\n",candidate->candidateNumber);
        fprintf(file, "%d\n",candidate->numOfMembers);
        fprintf(file, "%s\n",candidate->name);
        fprintf(file, "%s\n",candidate->idNumber);
        fprintf(file, "%zu\n",candidate->votesNumber);
    while(pNode->next!= NULL)
    {
        if(!writeMemberToTxt(((PartyMember*)pNode->next->key), file))
            return 0;
        pNode = pNode->next;
    }
    return 1;
}
int writeCandidateToBinary(Candidate* candidate, FILE* file) {
    int nameLength = (int)strlen(candidate->name);
    int idNumberLength = (int)strlen(candidate->idNumber);
    if (fwrite(&candidate->candidateNumber, sizeof(int), 1, file) != 1) 
        return 0;
    if (fwrite(&candidate->numOfMembers, sizeof(int), 1, file) != 1) 
        return 0;
    if (fwrite(&nameLength, sizeof(int), 1, file) != 1) 
        return 0;
    if (fwrite(candidate->name, sizeof(char), nameLength, file) != nameLength) 
        return 0;
    if (fwrite(&idNumberLength, sizeof(int), 1, file) != 1) 
        return 0;
    if (fwrite(candidate->idNumber, sizeof(char), idNumberLength, file) != idNumberLength) 
        return 0;
    if (fwrite(&candidate->votesNumber, sizeof(size_t), 1, file) != 1)
        return 0;
    NODE* pNode = candidate->partyMembers.head.next;
    while(pNode != NULL) {
        if (!writeMemberToBinary((PartyMember*)pNode->key, file)) {
            return 0;
        }
        pNode = pNode->next;
    }

    return 1;
}

int readCandidateFromTxt(Candidate* candidate,FILE* file) {
    
    if (fscanf(file, "%d\n", &candidate->candidateNumber) != 1) {
        fclose(file);
        return 0;
    }
    if (fscanf(file, "%d\n", &candidate->numOfMembers) != 1) {
        fclose(file);
        return 0;
    }
    char buffer[MAX_LEN] = {0};
    if (fgets(buffer, (int)sizeof(buffer), file) == NULL) 
        return 0;
    buffer[strcspn(buffer, "\r\n")] = '\0';
    candidate->name = strdup(buffer);
    
    char buffer1[MAX_LEN] = {0};
    if (fgets(buffer1, (int)sizeof(buffer1), file) == NULL)
        return 0;
    buffer1[strcspn(buffer1, "\r\n")] = '\0';
    
    candidate->idNumber = strdup(buffer1);
    if (fscanf(file, "%zu\n", &candidate->votesNumber) != 1) {
        fclose(file);
        return 0;
    }
    if(candidate->numOfMembers > 0)
    {
        if(L_init(&candidate->partyMembers) == False)
            return 0;
        for (int i=0; i<candidate->numOfMembers; i++) {
            PartyMember *pPartyMember  = malloc(sizeof(PartyMember));
            if (!pPartyMember)
                return 0;
            readMemberFromTxt(pPartyMember, file);
            NODE* current = candidate->partyMembers.head.next;
            NODE* preCurrent = &candidate->partyMembers.head;
            while( current<0)
            {
                preCurrent = current;
                current = current->next;
            }
            if(!L_insert(preCurrent,pPartyMember))
            {
                L_delete(preCurrent->next, freePartyMember);
                return 0;
            }
        }
    }
    return 1;
}
int readCandidateFromBinary(Candidate* candidate, FILE* file) {
    int nameLength, idNumberLength;
    if (fread(&candidate->candidateNumber, sizeof(int), 1, file) != 1) 
        return 0;
    if (fread(&candidate->numOfMembers, sizeof(int), 1, file) != 1) 
        return 0;
    if (fread(&nameLength, sizeof(int), 1, file) != 1) 
        return 0;
    char* name = malloc(nameLength + 1);
    if (!name) 
        return 0;
    if (fread(name, sizeof(char), nameLength, file) != nameLength) {
        free(name);
        return 0;
    }
    name[nameLength] = '\0';
    candidate->name = name;
    if (fread(&idNumberLength, sizeof(int), 1, file) != 1) 
        return 0;
    char* idNumber = malloc(idNumberLength + 1);
    if (!idNumber) {
        free(name);
        return 0;
    }
    if (fread(idNumber, sizeof(char), idNumberLength, file) != idNumberLength) {
        free(name);
        free(idNumber);
        return 0;
    }
    idNumber[idNumberLength] = '\0';
    candidate->idNumber = idNumber;
    if (fread(&candidate->votesNumber, sizeof(size_t), 1, file) != 1) {
        free(name);
        free(idNumber);
        return 0;
    }
    if (!L_init(&candidate->partyMembers)) {
        free(name);
        free(idNumber);
        return 0;
    }
    for (int i = 0; i < candidate->numOfMembers; i++) {
        PartyMember* pPartyMember = malloc(sizeof(PartyMember));
        if (!pPartyMember) {
            free(name);
            free(idNumber);
            L_free(&candidate->partyMembers, freePartyMember);
            return 0;
        }
        if (!readMemberFromBinary(pPartyMember, file)) {
            free(name);
            free(idNumber);
            free(pPartyMember);
            L_free(&candidate->partyMembers, freePartyMember);
            return 0;
        }
        if (!L_insert(&candidate->partyMembers.head, pPartyMember)) {
            free(name);
            free(idNumber);
            freePartyMember(pPartyMember);
            L_free(&candidate->partyMembers, freePartyMember);
            return 0;
        }
    }

    return 1;
}
