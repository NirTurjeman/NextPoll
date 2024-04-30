//
//  ElectionToFile.c
//  finalProject
//
//  Created by NirTurjeman on 05/04/2024.
//

#include "ElectionToFile.h"
#include "CandidateToFile.h"
#include "MemberToFile.h"
#include "VoterToFile.h"
#define CHECK_FILE_READ(expression, fileToClose, expected, returnValue) \
    if ((expression) != (expected)) { \
        fclose(fileToClose); \
        return returnValue; \
    }


int writeElectionToTxt(const Election* election, const char* electionFile, const char* CandidatesFile) {
    FILE *eFile = fopen(electionFile, "w");
    FILE *cFile = fopen(CandidatesFile, "w");
    if (!eFile || !cFile) {
        if (eFile) fclose(eFile);
        if (cFile) fclose(cFile);
        printf("Error opening file\n");
        return 0;
    }

    if (fprintf(cFile, "%d\n", election->numOfCandidates) < 0) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    for (int i = 0; i < election->numOfCandidates; i++) {
        if (!writeCandidateToTxt(&election->allCandidates[i], cFile)) {
            fclose(eFile);
            fclose(cFile);
            return 0;
        }
    }

    if (fprintf(eFile, "%d %d %d\n", election->electionDate.year, election->electionDate.month, election->electionDate.day) < 0 ||
        fprintf(eFile, "%d\n", election->isElectionOpen) < 0) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    if (election->voters->votersCount > 0 && !writeVotersToTxt(election->voters, eFile)) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    fclose(eFile);
    fclose(cFile);
    return 1;
}
int writeElectionToBinary(const Election* election, const char* electionFile, const char* CandidatesFile) {
    FILE *eFile = fopen(electionFile, "wb");
    FILE *cFile = fopen(CandidatesFile, "wb");
    if (!eFile || !cFile) {
        if (eFile) fclose(eFile);
        if (cFile) fclose(cFile);
        printf("Error opening file\n");
        return 0;
    }

    if (fwrite(&election->numOfCandidates, sizeof(int), 1, cFile) != 1 ||
        fwrite(&election->electionDate, sizeof(Date), 1, eFile) != 1 ||
        fwrite(&election->isElectionOpen, sizeof(int), 1, eFile) != 1) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    for (int i = 0; i < election->numOfCandidates; i++) {
        if (!writeCandidateToBinary(&election->allCandidates[i], cFile)) {
            fclose(eFile);
            fclose(cFile);
            return 0;
        }
    }

    if (!writeVotersToBinary(election->voters, eFile)) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    fclose(eFile);
    fclose(cFile);
    return 1;
}

int readElectionFromTxt(Election* election, const char* electionFile,const char* CandidatesFile) {
    FILE *eFile = fopen(electionFile, "r");
    FILE *cFile = fopen(CandidatesFile, "r");
    if (!eFile || !cFile) {
        if (eFile) fclose(eFile);
        if (cFile) fclose(cFile);
        printf("Error opening file\n");
        return 0;
    }

    Date date;
    CHECK_FILE_READ(fscanf(eFile, "%d %d %d\n", &date.year, &date.month, &date.day), eFile, 3, 0);
    election->electionDate = date;

    CHECK_FILE_READ(fscanf(eFile, "%d\n", &election->isElectionOpen), eFile, 1, 0);

    if (!readVotersFromTxt(election->voters, eFile)) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    CHECK_FILE_READ(fscanf(cFile, "%d\n", &election->numOfCandidates), cFile, 1, 0);

    election->allCandidates = (Candidate*)malloc(sizeof(Candidate)*election->numOfCandidates);
    if (!election->allCandidates) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    for (int i = 0; i < election->numOfCandidates; i++) {
            Candidate* pCandidate = &election->allCandidates[i];
            if (!readCandidateFromTxt(pCandidate, cFile)) {
                // Free all candidates loaded before the error
                for (int j = 0; j < i; j++) {
                    freeCandidate(&election->allCandidates[j]);
                }
                free(election->allCandidates);
                fclose(eFile);
                fclose(cFile);
                return 0;
            }
        }


    fclose(eFile);
    fclose(cFile);
    return 1;
}
int readElectionFromBinary(Election* election, const char* electionFile,const char* CandidatesFile) {
    FILE* eFile = fopen(electionFile, "rb");
    FILE* cFile = fopen(CandidatesFile, "rb");
    if (!eFile || !cFile) {
        if (eFile) fclose(eFile);
        if (cFile) fclose(cFile);
        printf("Error opening file\n");
        return 0;
    }

    CHECK_FILE_READ(fread(&election->electionDate, sizeof(Date), 1, eFile), eFile, 1, 0);
    CHECK_FILE_READ(fread(&election->isElectionOpen, sizeof(int), 1, eFile), eFile, 1, 0);

    if (!readVotersFromBinary(election->voters, eFile)) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    CHECK_FILE_READ(fread(&election->numOfCandidates, sizeof(int), 1, cFile), cFile, 1, 0);

    election->allCandidates = (Candidate*)malloc(sizeof(Candidate) * election->numOfCandidates);
    if (!election->allCandidates) {
        fclose(eFile);
        fclose(cFile);
        return 0;
    }

    for (int i = 0; i < election->numOfCandidates; i++) {
            Candidate* pCandidate = &election->allCandidates[i];
            if (!readCandidateFromBinary(pCandidate, cFile)) {
                // Free all candidates loaded before the error
                for (int j = 0; j < i; j++) {
                    freeCandidate(&election->allCandidates[j]);
                }
                free(election->allCandidates);
                fclose(eFile);
                fclose(cFile);
                return 0;
            }
        }

    fclose(eFile);
    fclose(cFile);
    return 1;
}
