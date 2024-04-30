//
//  VoterToFile.c
//  finalProject
//
//  Created by NirTurjeman on 05/04/2024.
//

#include "VoterToFile.h"
#include "ResidentToFile.h"
#define CHECK_FILE_READ(expression, expected, cleanup) \
    if ((expression) != (expected)) { \
        cleanup; \
        return 0; \
    }

int readVotersFromTxt(VoterManager* voters, FILE* file)
{
    int readValue = -1;
    eSortType sortingType;
    if (fscanf(file, "%d\n", &readValue) != 1)
        return 0;
    else
    {
        sortingType = (eSortType)readValue;
        voters->eType = sortingType;
    }
    fscanf(file, "%d\n", &voters->votersCount);
    voters->theVoters = (Voter*)malloc(sizeof(Voter) * voters->votersCount);
    for (int i = 0; i < voters->votersCount; i++) {
        voters->theVoters[i].pPerson = malloc(sizeof(Person));
        readPersonFromTxt(voters->theVoters[i].pPerson, file);
        fscanf(file, "%d\n", &voters->theVoters[i].hasVoted);
        fscanf(file,"%d\n", &voters->theVoters[i].theVote);
        fscanf(file,"%d\n", &voters->theVoters[i].timeCount);
        voters->theVoters[i].votingTimes = (Time*)malloc(sizeof(Time) * voters->theVoters[i].timeCount);
        for(int t = 0; t < voters->theVoters[i].timeCount; t++)
            fscanf(file, "%d:%d\n", &voters->theVoters[i].votingTimes[t].hour, &voters->theVoters[i].votingTimes[t].minute);
        fscanf(file, "%d\n", &voters->theVoters[i].voteType);
    }

    return 1;
}
int readVotersFromBinary(VoterManager* voters, FILE* file) {
    CHECK_FILE_READ(fread(&voters->eType, sizeof(eSortType), 1, file), 1, {});

    CHECK_FILE_READ(fread(&voters->votersCount, sizeof(int), 1, file), 1, {});

    voters->theVoters = (Voter*)malloc(sizeof(Voter) * voters->votersCount);
    if (!voters->theVoters) {
        return 0;
    }
    for (int i = 0; i < voters->votersCount; i++) {
        voters->theVoters[i].pPerson = (Person*)malloc(sizeof(Person));
        if (!voters->theVoters[i].pPerson || !readPersonFromBinary(voters->theVoters[i].pPerson, file)) {
            while (i-- > 0) {
                freePerson(voters->theVoters[i].pPerson);
                free(voters->theVoters[i].votingTimes);
            }
            free(voters->theVoters);
            return 0;
        }

        CHECK_FILE_READ(fread(&voters->theVoters[i].hasVoted, sizeof(int), 1, file), 1, {});
        CHECK_FILE_READ(fread(&voters->theVoters[i].theVote, sizeof(int), 1, file), 1, {});
        CHECK_FILE_READ(fread(&voters->theVoters[i].timeCount, sizeof(int), 1, file), 1, {});

        voters->theVoters[i].votingTimes = (Time*)malloc(sizeof(Time) * voters->theVoters[i].timeCount);
        if (!voters->theVoters[i].votingTimes) {
            while (i >= 0) {
                freePerson(voters->theVoters[i].pPerson);
                free(voters->theVoters[i].votingTimes);
                i--;
            }
            free(voters->theVoters);
            return 0;
        }

        for (int t = 0; t < voters->theVoters[i].timeCount; t++) {
            CHECK_FILE_READ(fread(&voters->theVoters[i].votingTimes[t].hour, sizeof(int), 1, file), 1, {});
            CHECK_FILE_READ(fread(&voters->theVoters[i].votingTimes[t].minute, sizeof(int), 1, file), 1, {});
        }

        CHECK_FILE_READ(fread(&voters->theVoters[i].voteType, sizeof(int), 1, file), 1, {});
    }
    return 1;
}
int writeVotersToTxt(const VoterManager* voters,FILE* file)
{
    fprintf(file, "%d\n", voters->eType);
    fprintf(file, "%d\n", voters->votersCount);
    for (int i=0; i<voters->votersCount; i++) {
        writePersonToTxt(voters->theVoters[i].pPerson,file);
        fprintf(file, "%d\n",voters->theVoters[i].hasVoted);
        fprintf(file,"%d\n",voters->theVoters[i].theVote);
        fprintf(file,"%d\n",voters->theVoters[i].timeCount);
        for(int t=0;t<voters->theVoters[i].timeCount;t++)
            fprintf(file,"%d:%d\n",voters->theVoters[i].votingTimes[t].hour,voters->theVoters[i].votingTimes[t].minute);
        fprintf(file,"%d\n",voters->theVoters[i].voteType);
    }
    return 1;
}
int writeVotersToBinary(const VoterManager* voters, FILE* file) {
    if (fwrite(&voters->eType, sizeof(eSortType), 1, file) != 1) {
        return 0;
    }

    if (fwrite(&voters->votersCount, sizeof(int), 1, file) != 1) {
        return 0;
    }

    for (int i = 0; i < voters->votersCount; i++) {
        if (!writePersonToBinary(voters->theVoters[i].pPerson, file)) {
            return 0; // Failed to write person
        }

        if (fwrite(&voters->theVoters[i].hasVoted, sizeof(int), 1, file) != 1) {
            return 0;
        }

        if (fwrite(&voters->theVoters[i].theVote, sizeof(int), 1, file) != 1) {
            return 0;
        }

        if (fwrite(&voters->theVoters[i].timeCount, sizeof(int), 1, file) != 1) {
            return 0;
        }

        for (int t = 0; t < voters->theVoters[i].timeCount; t++) {
            if (fwrite(&voters->theVoters[i].votingTimes[t].hour, sizeof(int), 1, file) != 1 ||
                fwrite(&voters->theVoters[i].votingTimes[t].minute, sizeof(int), 1, file) != 1) {
                return 0; // Failed to write voting times
            }
        }

        if (fwrite(&voters->theVoters[i].voteType, sizeof(int), 1, file) != 1) {
            return 0;
        }
    }

    return 1;
}
