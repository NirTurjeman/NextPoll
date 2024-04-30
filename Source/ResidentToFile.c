
#include "ResidentToFile.h"
#define MAX_LEN 255
int writeResidentToTxt(const ResidentComm* pResident, const char* fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }
    int count = pResident->numOfResidents;
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        writePersonToTxt(pResident->residents[i], file);
    }
    fclose(file);
    return 1;
}
int writeResidentToBinary(const ResidentComm* pResident, const char* fileName)
{
    FILE* file = fopen(fileName, "wb");
    if (!file) {
        printf("Error file not found\n");
        return 0;
    }
        if(fwrite(&pResident->numOfResidents, sizeof(int), 1, file) != 1)
            return 0;
    for (int i = 0; i < pResident->numOfResidents; i++)
        writePersonToBinary(pResident->residents[i], file);
    fclose(file);
    return 1;
}
int writePersonToTxt(const Person* pPerson, FILE* file)
{
    fprintf(file, "%s\n", pPerson->name);
    Date date = pPerson->identity.date;
    fprintf(file, "%d %d %d\n", date.year, date.month, date.day);
    Address address = pPerson->identity.address;
    fprintf(file, "%s/%s/%d\n", address.city, address.street, address.house);
    fprintf(file, "%d\n", pPerson->identity.phoneNumber);
    fprintf(file, "%s\n", pPerson->identity.email);
    fprintf(file, "%s\n", pPerson->identity.idNumber);
    return 1;
}
int writePersonToBinary(const Person* pPerson,FILE* file)
{
    
        int nameLength = (int)strlen(pPerson->name);
        if (fwrite(&nameLength, sizeof(int), 1, file) != 1) //Write name length
        {
            fclose(file);
            return 0;
        }
        if(fwrite(pPerson->name, sizeof(char), nameLength, file) != nameLength) //Write airline name
        {
            fclose(file);
            return 0;
        }
        writeDateToFile(&pPerson->identity.date,file);
        int cityLengh = (int)strlen(pPerson->identity.address.city);
        if(fwrite(&cityLengh, sizeof(int), 1, file) != 1)//Write city length
        {
            fclose(file);
            return 0;
        }
        if(fwrite(pPerson->identity.address.city, sizeof(char), cityLengh, file) != cityLengh)//Write city str
        {
            fclose(file);
            return 0;
        }
        int streetLength = (int)strlen(pPerson->identity.address.street);
        if(fwrite(&streetLength, sizeof(int), 1, file) != 1)//Write street length
        {
            fclose(file);
            return 0;
        }
        if(fwrite(pPerson->identity.address.street, sizeof(char), streetLength, file) != streetLength)//Write street str
        {
            fclose(file);
            return 0;
        }
        if(fwrite(&pPerson->identity.address.house, sizeof(int), 1, file) != 1)//Write house number
        {
            fclose(file);
            return 0;
        }
        if(fwrite(&pPerson->identity.phoneNumber, sizeof(int), 1, file) != 1)//Write phone number
        {
            fclose(file);
            return 0;
        }
        int emailLength = (int)strlen(pPerson->identity.email);
        if(fwrite(&emailLength, sizeof(int), 1, file) != 1)//Write email length
        {
            fclose(file);
            return 0;
        }
        if(fwrite(pPerson->identity.email, sizeof(char), emailLength, file) != emailLength)//Write email length
        {
            fclose(file);
            return 0;
        }
        int idLength = (int)strlen(pPerson->identity.idNumber);
        if(fwrite(&idLength, sizeof(int), 1, file) != 1)//Write id length
        {
            fclose(file);
            return 0;
        }
        if(fwrite(pPerson->identity.idNumber, sizeof(char), idLength, file) != idLength)//Write id str
        {
            fclose(file);
            return 0;
        }
    return 1;
}
int readLine(FILE* file, char* buffer, size_t size) {
    if (fgets(buffer, (int)size, file) == NULL) return 0;
    buffer[strcspn(buffer, "\r\n")] = '\0';
    return 1;
}
int readPersonFromTxt(Person* pPerson, FILE* file)///////////////////////////////////
{
    char buffer[MAX_LEN] = {0};
    if (!readLine(file, buffer, sizeof(buffer))) {
        freePerson(pPerson);
        fclose(file);
        return 0;
    }
    pPerson->name = strdup(buffer);
    if (fscanf(file, "%d %d %d\n", &pPerson->identity.date.year, &pPerson->identity.date.month, &pPerson->identity.date.day) != 3) {
        freePerson(pPerson);
        fclose(file);
        return 0;
    }
    if (!readLine(file, buffer, sizeof(buffer))) {
        freePerson(pPerson);
        fclose(file);
        return 0;
    }

    char* token = strtok(buffer, "/");
    pPerson->identity.address.city = strdup(token ? token : "");

    token = strtok(NULL, "/");
    pPerson->identity.address.street = strdup(token ? token : "");

    token = strtok(NULL, "/");
    pPerson->identity.address.house = token ? atoi(token) : 0;

    if (fscanf(file, "%d\n", &pPerson->identity.phoneNumber) != 1) {
        freePerson(pPerson);
        fclose(file);
        return 0;
    }

    if (!readLine(file, buffer, sizeof(buffer))) {
        freePerson(pPerson);
        fclose(file);
        return 0;
    }
    pPerson->identity.email = strdup(buffer);

    if (!readLine(file, buffer, sizeof(buffer))) {
        freePerson(pPerson);
        fclose(file);
        return 0;
    }
    pPerson->identity.idNumber = strdup(buffer);
    return 1;
}
int readPersonFromBinary(Person* pPerson, FILE* file) {
    int nameLength;
    if (fread(&nameLength, sizeof(int), 1, file) != 1) // Read name length
        return 0;

    pPerson->name = (char*)malloc((nameLength + 1)*sizeof(char));
    if (fread(pPerson->name, sizeof(char), nameLength, file) != nameLength) // Read name
        return 0;
    pPerson->name[nameLength] = '\0'; // Null-terminate the string

    readDateFromFile(&pPerson->identity.date, file);

    int cityLength;
    if (fread(&cityLength, sizeof(int), 1, file) != 1) // Read city length
        return 0;

    pPerson->identity.address.city = (char*)malloc((cityLength + 1)*sizeof(char));
    if (fread(pPerson->identity.address.city, sizeof(char), cityLength, file) != cityLength) // Read city
        return 0;
    pPerson->identity.address.city[cityLength] = '\0'; // Null-terminate the string

    int streetLength;
    if (fread(&streetLength, sizeof(int), 1, file) != 1) // Read street length
        return 0;

    pPerson->identity.address.street = (char*)malloc((streetLength + 1)*sizeof(char));
    if (fread(pPerson->identity.address.street, sizeof(char), streetLength, file) != streetLength) // Read street
        return 0;
    pPerson->identity.address.street[streetLength] = '\0'; // Null-terminate the string

    if (fread(&pPerson->identity.address.house, sizeof(int), 1, file) != 1) // Read house number
        return 0;

    if (fread(&pPerson->identity.phoneNumber, sizeof(int), 1, file) != 1) // Read phone number
        return 0;

    int emailLength;
    if (fread(&emailLength, sizeof(int), 1, file) != 1) // Read email length
        return 0;

    pPerson->identity.email = (char*)malloc((emailLength + 1)*sizeof(char));
    if (fread(pPerson->identity.email, sizeof(char), emailLength, file) != emailLength) // Read email
        return 0;
    pPerson->identity.email[emailLength] = '\0'; // Null-terminate the string

    int idLength;
    if (fread(&idLength, sizeof(int), 1, file) != 1) // Read ID length
        return 0;

    pPerson->identity.idNumber = (char*)malloc((idLength + 1)*sizeof(char));
    if (fread(pPerson->identity.idNumber, sizeof(char), idLength, file) != idLength) // Read ID
        return 0;
    pPerson->identity.idNumber[idLength] = '\0'; // Null-terminate the string

    return 1; // Success
}
int readResidentFromTxt(ResidentComm* pResident, const char* fileName) {
    int count;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    if (fscanf(file, "%d\n", &count) != 1) {
        fclose(file);
        return 0;
    }

    pResident->numOfResidents = count;
    pResident->residents = realloc(pResident->residents, count * sizeof(Person*));
    if (!pResident->residents) {
        fclose(file);
        return 0;
    }
    for (int i = 0; i < count; i++) {
        Person* pPerson = malloc(sizeof(Person));
        if (!pPerson) {
            for (int j = 0; j < i; j++) {
                freePerson(pResident->residents[j]);
            }
            free(pResident->residents);
            fclose(file);
            return 0;
        }
        readPersonFromTxt(pPerson,file);
        pResident->residents[i] = pPerson;
    }
    fclose(file);
    return 1;
}
int readResidentFromBinary(ResidentComm* pResident, const char* fileName) {
    FILE* file = fopen(fileName, "rb");
    if (!file) {
        printf("Error file not found\n");
        return 0;
    }

    if(fread(&pResident->numOfResidents, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    pResident->residents = (Person**)malloc(pResident->numOfResidents * sizeof(Person*));
    if (pResident->residents == NULL) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < pResident->numOfResidents; i++) { // make sure all free
            pResident->residents[i] = (Person*)malloc(sizeof(Person));
            if (!pResident->residents[i]) {
                for (int j = 0; j < i; j++) {
                    freePerson(pResident->residents[j]); 
                    free(pResident->residents[j]);
                }
                free(pResident->residents);
                fclose(file);
                return 0;
            }

            if (!readPersonFromBinary(pResident->residents[i], file)) {
                for (int j = 0; j <= i; j++) {
                    freePerson(pResident->residents[j]);
                    free(pResident->residents[j]);
                }
                free(pResident->residents);
                fclose(file);
                return 0;
            }
        }

    fclose(file);
    return 1;
}
