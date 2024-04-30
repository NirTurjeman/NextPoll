//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include "General.h"
#include "Date.h"
#include "Identity.h"
#include "ResidentComm.h"
#include "VoterManager.h"
#include "AdminManager.h"
#include "Election.h"
#include "ResidentToFile.h"
#include "AdminsToFile.h"
#include "ElectionToFile.h"
#include "CandidateToFile.h"
#define UPLOAD_ERROR "First you need to upload the project from file!\n"
#define GENERAL_ERROR printf("General Erorr!\n");
#define SAVE_TO_FILES saveToFiles(residents,adminsArr,election);

//##--Txt Files Name--##//
#define residentTxt "\\DataBase\\Residents.txt"
#define adminTxt "\\DataBase\\Admins.txt"
#define candidateTxt "\\DataBase\\Candidates.txt"
#define electionTxt "\\DataBase\\Election.txt"

//##--Binary Files Name--##//
#define residentBin "\\DataBase\\Residents.bin"
#define adminBin "\\DataBase\\Admins.bin"
#define candidateBin "\\DataBase\\Candidates.bin"
#define electionBin "\\DataBase\\Election.bin"


void saveToFiles(ResidentComm residents,AdminManager adminsArr,Election election);

int main(int argc, const char * argv[]) {
    
    //##---STRUCTS---##//
    typedef enum{ eAdmin , eVoter , eCandidate , eObserver}MenuType;//This enum about the menu that user open
    ResidentComm residents;
    initCommunity(&residents);
    Voter* pVoter = NULL;
    Admin* pAdmin = NULL;
    AdminManager adminsArr;
    initAdminManager(&adminsArr);
    Election election;
    election.isElectionOpen = 0;
    election.voters = malloc(sizeof(VoterManager));
    Candidate* pCandidate = NULL;
    int startProgram = 0;
    
    while(!startProgram)
    {
        //##--EFRAT-MAIN--##//
        printf("##--Welcome to our Final Project--##\n\n");
        printf("1) To upload the project from txt file\n");
        printf("2) To upload the project from binary file\n");
        printf("3) To print the project\n");
        printf("4) To print subcomponents system\n");
        printf("5) To add components\n");
        printf("6) To sort Voters array\n");
        printf("7) To search in voter array\n");
        printf("8) To demonstrate the act of creativity\n");
        printf("-1) To show our menu\n");
        int res=0;
        scanf("%d",&res);
        switch (res) {
            case 1:
                if(!readResidentFromTxt(&residents,residentTxt))
                    printf("Error read resident file!\n");
                if(!readAdminsFromTxt(&adminsArr,adminTxt))
                    printf("Error read Admins file!\n");
                if(!readElectionFromTxt(&election,electionTxt,candidateTxt))
                    printf("Error read election file!\n");
                break;
            case 2:
                if(!readResidentFromBinary(&residents,residentBin))
                    printf("Error read resident file!\n");
                if(!readAdminsFromBinary(&adminsArr,adminBin))
                    printf("Error read Admins file!\n");
                if(!readElectionFromBinary(&election,electionBin,candidateBin))
                    printf("Error read election file!\n");
                break;
            case 3:
                if(election.isElectionOpen)
                    printElection(election);
                else
                    printf(UPLOAD_ERROR);
                break;
            case 4:
                if(!election.isElectionOpen)
                {
                    if(adminsArr.adminsCount == 0||election.voters->votersCount == 0)
                    {
                        printf(UPLOAD_ERROR);
                        break;
                    }
                }else
                    printAdmins(adminsArr);
                    printVoterArr(election.voters);
                break;
            case 5:
                
                printf("\nOptions to add to the system:\n");
                printf("1) Add resident\n");
                printf("2) Create Election\n");
                printf("3) Add candidate\n");
                printf("4) Add party member\n");
                printf("5) Vote for some voter\n");
                printf("6) Add Admin\n");
                res=0;
                scanf("%d",&res);
                if (res > 6 || res < 1)
                {
                   GENERAL_ERROR
                   break;
                }
                if(res==1)
                {
                    if(!addResident(&residents))
                    {
                        GENERAL_ERROR
                        break;
                    }
                    if(!initVoterManager(election.voters, residents))
                        GENERAL_ERROR
                        
                    SAVE_TO_FILES
                }

                else if (res == 2)
                {
                    if (election.isElectionOpen == 1) {
                        printf("There is already an open election!\n");
                        break;
                    }
                    initElection(&election);
                    election.voters = malloc(sizeof(VoterManager));
                    if (!initVoterManager(election.voters, residents))
                    {
                        GENERAL_ERROR
                            break;
                    }
                    SAVE_TO_FILES
                        break;
                }
                else if (res==3)
                {
                    if (!election.isElectionOpen)
                    {
                        printf(UPLOAD_ERROR);
                        break;
                    }

                    if(!addCandidate(&election))
                    {
                        GENERAL_ERROR
                        break;
                    }
                    SAVE_TO_FILES
                }
                else if (res==4)
                {
                    if (!election.isElectionOpen)
                    {
                        printf(UPLOAD_ERROR);
                        break;
                    }

                    if (election.numOfCandidates==0) {
                        printf("There is no Candidates in election\n");
                        break;
                    }
                    printf("Select a candidate you would like the member will be added : \n");
                    printCandidateArr(election.allCandidates, election.numOfCandidates);
                    int option;
                    scanf("%d",&option);
                    if(option>0&&option<election.numOfCandidates+1)
                    {
                        if(!addPartyMember(&election.allCandidates[option-1]))
                        {
                            GENERAL_ERROR
                            break;
                        }
                        SAVE_TO_FILES
                    }
                    else
                        printf("Wrong input!\n");
                }else if(res == 5)
                {
                    if (!election.isElectionOpen)
                    {
                        printf(UPLOAD_ERROR);
                        break;
                    }

                    if (election.voters->votersCount>0) {
                        printf("Choose a voter to vote for him:\n");
                        printVoterArr(election.voters);
                        char* id = getStrExactName("Enter the ID of the voter you selected");
                        Voter* theVoter = findVoterByID(election.voters,id,compareByID);
                        if (theVoter) {
                            if (theVoter->hasVoted)
                            {
                                printf("This Voter alredy vote!\n");
                                break;
                            }
                            printf("Choose candidate:\n");
                            printCandidateArr(election.allCandidates, election.numOfCandidates);
                            int input;
                            scanf("%d",&input);
                            if (input<0||input>election.numOfCandidates+1) {
                                printf("Wrong input!\n");
                                break;
                            }
                            theVoter->hasVoted = 1;
                            election.allCandidates[input-1].votesNumber++;
                            theVoter->theVote = input-1;
                            SAVE_TO_FILES
                        }
                    }
                }
                else if (res == 6)
                {
                    if (!addAdmin(&adminsArr))
                    {
                        GENERAL_ERROR
                            break;
                    }
                    SAVE_TO_FILES

                }
                break;
                
            case 6:
                if(!election.isElectionOpen)
                {
                    printf(UPLOAD_ERROR);
                    break;
                }
                if (election.voters->votersCount == 0) {
                    printf("There are no Voters in program!\n");
                    break;
                }
                if(!sortVoter(election.voters))
                {
                    GENERAL_ERROR
                }
                printVoterArr(election.voters);
                break;
            case 7:
                if (!election.isElectionOpen) {
                    printf("There is no election yet!\n");
                    break;
                }
                if (election.voters->votersCount == 0) {
                    printf("There are no Voters in program!\n");
                    break;
                }
                if(!findVoter(election.voters))
                    GENERAL_ERROR
                break;
            case 8:
                printf("\nCreative actions:\n");
                printf("1) The function validates an Israeli ID by checking its format and applying a checksum algorithm\n");
                printf("2) The function calculates a person's age in real-time based on their birth date\n");
                int option = 0;
                scanf("%d",&option);
                if (option == 1) {
                    char* id = getStrExactName("Enter id Number:");
                    if(!checkValidIdNumber(id))
                        printf("Wrong id!\n");
                    else
                        printf("Good job!\n");
                }else if(option == 2)
                {
                    Date date;
                    printf("Date of birth:\n");
                    getCorrectDate(&date);
                    int age = getAge(date);
                    printf("Your age is: %d\n",age);
                }
                break;
            case -1:
                startProgram = 1;
                break;
        }
    }
    //##---OUR MAIN MENU---##//
    if (!election.isElectionOpen) 
    {
        if(!readResidentFromTxt(&residents,residentTxt))
            printf("Error read resident file!\n");
        if(!readAdminsFromTxt(&adminsArr,adminTxt))
            printf("Error read Admins file!\n");
        if(!readElectionFromTxt(&election,electionTxt,candidateTxt))
            printf("Error read election file!\n");
    }
    MenuType menuType = eObserver;
    int counter = 1;//The failed login number
    printf("#--Welcome to Voting App--#\n");
    while(counter<=3 && menuType == eObserver)
    {
        if(counter>1)
            printf("Number of attempts left for login %d.\n\n",4-counter);
        
        char* id = getStrExactName("To login Enter your ID number:\n");
        if(!checkValidIdNumber(id))
        {
            printf("Error your id number is not in the right syntax!\n");
            counter++;
            continue;
        }
        else
        {
            pAdmin = findAdmin(&adminsArr, id);
            if(pAdmin)
            {
                menuType = eAdmin;
                break;
            }
            pCandidate = findCandidateByID(&election,id);
            if(pCandidate)
            {
                menuType = eCandidate;
                break;
            }
            if(!findResident(&residents, id))
            {
                printf("Wrong ID number!\n");
                counter++;
                continue;
            }
            else
            {
                pVoter = findVoterByID(election.voters,id,compareByID);
                if(!pVoter || pVoter->hasVoted)
                {
                    printf("You cannot Vote!\n");
                    counter++;
                    continue;
                }
                menuType = eVoter;
            }
        }
    }
    while(counter<=3 && menuType == eVoter )
    {
        Date voterDate = pVoter->pPerson->identity.date;
        Date dateInput;
        printf("Day of Birth information:\n");
        getCorrectDate(&dateInput);
        if(!compareByDate(voterDate, dateInput))
        {
            printf("Wrong Date!\n");
            counter++;
            continue;
        }
        break;
    }
    if (counter == 3) {
        printf("You are Blocked!\n");
    }
    int res = 0;
    switch (menuType)
    {
            //##------Admin Menu------##//
        case eAdmin:
        {
            res = 0;
            while(res != -1)
            {
                printf("Hello %s Wellcome to *Admin* Menu\n",pAdmin->name);
                printf("1) Add resident\n");
                printf("2) Add candidate\n");
                printf("3) Create election\n");
                printf("4) Sort and Print Voters\n");
                printf("5) Find Voter by your selection sort\n");
                printf("6) Print Election\n");
                printf("-1) Exit\n");
                scanf("%d",&res);
                switch (res) {
                    case 1:
                        if (!addResident(&residents))
                        {
                            GENERAL_ERROR
                                break;
                        }
                        if (election.isElectionOpen == 1)
                            if(!initVoterManager(election.voters,residents))
                                GENERAL_ERROR
                        
                        SAVE_TO_FILES
                        
                        break;
                    case 2:
                        if (election.isElectionOpen != 1)
                        {
                            printf("There is no election yet!\n");
                            break;
                        }
                        if (!addCandidate(&election))
                        {
                            GENERAL_ERROR
                                break;
                        }
                        printCandidateArr(election.allCandidates, election.numOfCandidates);
                        SAVE_TO_FILES
                        break;
                    case 3:
                        if (election.isElectionOpen == 1) {
                            printf("There is already an open election!\n");
                            break;
                        }
                        initElection(&election);
                        election.voters = malloc(sizeof(VoterManager));
                        if(!initVoterManager(election.voters,residents))
                        {
                            GENERAL_ERROR
                            break;
                        }
                        SAVE_TO_FILES
                        break;
                    case 4:
                        if (!election.isElectionOpen) {
                            printf("There is no election yet!\n");
                            break;
                        }
                            if(!sortVoter(election.voters))
                                GENERAL_ERROR
                            printVoterArr(election.voters);
                        break;
                    case 5:
                        if (!election.isElectionOpen) {
                            printf("There is no election yet!\n");
                            break;
                        }
                        if(!findVoter(election.voters))
                            GENERAL_ERROR
                        break;
                    case 6:
                        if (!election.isElectionOpen) {
                            printf("There is no election yet!\n");
                            break;
                        }
                        printElection(election);
                        break;
                    case -1:
                        printf("Good bye!\n");
                        freeElection(&election);
                        freeResidentComm(&residents);
                        freeAdminManager(&adminsArr);
                        break;
                    default:
                        printf("Input should be between 1 to 3\n");
                        break;
                }
            }
            break;
        }
            //##------Voter Menu------##//
        case eVoter:
            res = 0;
            printf("Hello %s Wellcome to Voting App\n",pVoter->pPerson->name);
            if (pVoter->hasVoted)
            {
                printf("You cannot vote twice!\n");
                break;
            }
            if(checkValidTimeToVote(pVoter) == 0)
                {
                    printf("Now is not your time to vote!\n");
                    printf("Your voting times:\n");
                    for (int i=0; i<pVoter->timeCount; i++) {
                        printf("%d) %d - %d\n",i+1,pVoter->votingTimes[i].hour,pVoter->votingTimes[i].hour+1);
              }
                    printf("Please make sure you enter in VALID times, have a nice one :)\n");
                    break;
            }
            printf("Which candidate would you like to choose:\n");
            printCandidateArr(election.allCandidates, election.numOfCandidates);
            pVoter->theVote = res - 1;
            while(!res)
                scanf("%d",&res);
            printf("Your chosen candidate is %s\n",election.allCandidates[res-1].name);
            election.allCandidates[res-1].votesNumber++;
            pVoter->theVote = res-1;
            pVoter->hasVoted = 1;
            break;
            //##------Candidate Menu------##//
        case eCandidate:
            while(res!=-1)
            {
            res = 0;
            printf("Hello %s Wellcome to *Candidate* menu\n",pCandidate->name);
            printf("1) party member options\n");
            printf("2) Show the percentage of voting in the elections\n");
            printf("3) What is the percentage of voters who voted for me?\n");
            printf("-1) Exit");
                scanf("%d",&res);
                if(res>3 || res <-1 || res == 0)
                    continue;
               
                switch (res) {
                    case 1:
                    {
                        int option;
                        while(1)
                        {
                            printf("1) Add party Member\n");
                            printf("2) Update salary to party member\n");
                            printf("3) Print all");
                            scanf("%d",&option);
                            if (option>0 && option<4)
                                break;
                        }
                        if(option == 1)
                        {
                            if(!addPartyMember(pCandidate))
                                printf("General Error! try again\n");
                            SAVE_TO_FILES
                        }
                        else if (option == 2)
                        {
                            int memberNum;
                            printf("Which member do you want to update salary?\n");
                            NODE *pNode = pCandidate->partyMembers.head.next;
                            for (int i=0; i<pCandidate->numOfMembers; i++)
                            {
                                printf("%d) %s\n",i+1,((PartyMember*)pNode->key)->name);
                                pNode=pNode->next;
                            }
                            scanf("%d",&memberNum);
                            if (memberNum<1 || memberNum>pCandidate->numOfMembers+1)
                            {
                                printf("Error input!");
                                return 0;
                            }
                            pNode = pCandidate->partyMembers.head.next;
                            for (int i=1; i<memberNum; i++) {
                                pNode = pNode->next;
                            }
                            updateSalary(pNode->key);
                            SAVE_TO_FILES
                        }
                        else if (option == 3)
                            printPartyArr(&pCandidate->partyMembers);
                        break;
                    }
                    case 2:
                        if(!generateVoterTurnoutReport(&election))
                            GENERAL_ERROR
                        break;
                    case 3:
                        calculateCandidatePercentage(pCandidate->votesNumber,totalVotes(&election));
                        break;
                    case -1:
                        printf("Good Bye!");
                        freeElection(&election);
                        freeResidentComm(&residents);
                        freeAdminManager(&adminsArr); // need to fix
                }
            }
            break;
        }
            
    }
void saveToFiles(ResidentComm residents,AdminManager adminsArr,Election election)
{
    //TXT//
    if(!writeResidentToTxt(&residents,residentTxt))
        printf("Error write resident file!\n");
    if(!writeAdminsToTxt(&adminsArr,adminTxt))
        printf("Error write Admins file!\n");
    if(!writeElectionToTxt(&election,electionTxt,candidateTxt))
        printf("Error write election file!\n");
    
    //BIN//
    if(!writeResidentToBinary(&residents,residentBin))
        printf("Error write resident file!\n");
    if(!writeAdminsToBinary(&adminsArr,adminBin))
        printf("Error write Admins file!\n");
   if(!writeElectionToBinary(&election,electionBin,candidateBin))
        printf("Error write election file!\n");
}
