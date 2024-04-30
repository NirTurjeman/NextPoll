//
//  AdminToFile.c
//  finalProject
//
//  Created by NirTurjeman on 05/04/2024.
//

#include "AdminsToFile.h"
#define MAX_LEN 255
#define CHECK_FILE_READ(expression, fileToClose, returnValue) \
    if ((expression) != 1) { \
        fclose(fileToClose); \
        return returnValue; \
    }


int writeAdminsToTxt(const AdminManager* pAdmin,const char* fileName)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }
    int count = pAdmin->adminsCount;
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", pAdmin->adminsArr[i].name);
        fprintf(file, "%s\n", pAdmin->adminsArr[i].idNumber);
    }
    fclose(file);
    return 1;
}
int writeAdminsToBinary(const AdminManager* pAdmin, const char* fileName) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    int count = pAdmin->adminsCount;
    if (fwrite(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        unsigned int nameLength = (int)strlen(pAdmin->adminsArr[i].name);
        unsigned int idNumberLength = (int)strlen(pAdmin->adminsArr[i].idNumber);
        BYTE lengthData = (nameLength << 4) | idNumberLength;
        
        if (fwrite(&lengthData, sizeof(BYTE), 1, file) != 1) {
            return 0;
        }
        if (fwrite(pAdmin->adminsArr[i].name, sizeof(char), nameLength, file) != nameLength) {
            fclose(file);
            return 0;
        }
        if (fwrite(pAdmin->adminsArr[i].idNumber, sizeof(char), idNumberLength, file) != idNumberLength) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}
int readAdminsFromTxt(AdminManager* pManager, const char* fileName)
{
    int count;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    CHECK_FILE_READ(fscanf(file, "%d\n", &count), file, 0);
    pManager->adminsCount = count;
    
    pManager->adminsArr = (Admin*)malloc(pManager->adminsCount * sizeof(Admin));
    if (!pManager->adminsArr)
        return 0;
    
    for (int i = 0; i < count; i++) {
        Admin* pAdmin = (Admin*)malloc(sizeof(Admin));
        if (pAdmin == NULL)
            return 0;
        if (!pAdmin) {
            for (int j = 0; j < i; j++)
                freeAdmin(&pManager->adminsArr[j]);
            fclose(file);
            return 0;
        }
            char t1[MAX_LEN] = {0};
            char t2[MAX_LEN] = {0};
            if (fgets(t1, sizeof(t1), file) == NULL)
                return 0;
            if(fgets(t2, sizeof(t2), file) == NULL)
                return 0;
            t1[strcspn(t1, "\r\n")] = '\0';
            t2[strcspn(t2, "\r\n")] = '\0';
            pAdmin->name = strdup(t1);
            pAdmin->idNumber = strdup(t2);
        pManager->adminsArr[i] = *pAdmin;
        }
    return 1;
    }

int readAdminsFromBinary(AdminManager* pManager, const char* fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    int count;
    CHECK_FILE_READ(fread(&count, sizeof(int), 1, file), file, 0);
    
    pManager->adminsCount = count;
    pManager->adminsArr = (Admin*)malloc(count * sizeof(Admin));
    if (pManager->adminsArr == NULL) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        BYTE lengthData;
        if (fread(&lengthData, sizeof(BYTE), 1, file) != 1) {
            return 0;
        }
        unsigned int nameLength = (lengthData >> 4);
        unsigned int idNumberLength = lengthData & 0x0F; 
        pManager->adminsArr[i].name = (char*)malloc(nameLength + 1);
        pManager->adminsArr[i].idNumber = (char*)malloc(idNumberLength + 1);
        if (pManager->adminsArr[i].name == NULL || pManager->adminsArr[i].idNumber == NULL) {
                    // Free all previously allocated memory
                    while (i-- > 0) {
                        free(pManager->adminsArr[i].name);
                        free(pManager->adminsArr[i].idNumber);
                    }
                    free(pManager->adminsArr);
                    fclose(file);
                    return 0;
                }
        if (fread(pManager->adminsArr[i].name, sizeof(char), nameLength, file) != nameLength ||
            fread(pManager->adminsArr[i].idNumber, sizeof(char), idNumberLength, file) != idNumberLength) {
            free(pManager->adminsArr[i].name);
            free(pManager->adminsArr[i].idNumber);
            fclose(file);
            return 0;
        }

    }
    fclose(file);
    return 1;
}

