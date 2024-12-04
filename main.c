#include <stdio.h>
#include <stdlib.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"
#include "co2.h"
#include "getInputs.h"
#include "CuTest.h"
#include "runTests.h"
#include <locale.h>


void addNewApplicant(int numApplicants, int largestId);
void waitListByCO2(Applicant *applicantList, int numApplicants);
int compareByCO2(const void *a, const void *b);
int compareBySeniority(const void *a, const void *b);
void sortBySolution(Applicant *applicantList, int numApplicants, int turn, int index);
int isEven(int number);
void outputList(Applicant *applicantList, int numApplicants, int status);
void outputNext(Applicant *applicantList, int turn, int index);



int main(int argc, char *argv[]){
    

    // Run program with '-test'
    if (argc == 2){
        if (strcmp(argv[1], "-test") == 0){
            RunAllTests();
        }
    }

    double avaHousingLat, avaHousingLon; 
    double applicantLat, applicantLon;
    double workLat, workLon;
    int numApplicants = 0;
    int largestId = 0;
    char answer;
    Applicant *applicantList = makeApplicantsArray(&numApplicants, &largestId);

    if (setlocale(LC_ALL, "da_DK.UTF-8") == NULL) {
        printf("Locale setting failed!\n");
    }

    printf("Press %s1%s to add an applicant.\n", UBLU, COLOR_RESET);
    printf("Press %s2%s to print the waiting list, based on CO2 reduction.\n", UBLU, COLOR_RESET);
    printf("Press %s3%s to print the waiting list, based on waiting time.\n", UBLU, COLOR_RESET);
    printf("Press %s4%s to print the waiting lsit, based on our solution.\n", UBLU, COLOR_RESET);
    printf("Press %sq%s to %sexit%s the program.\n", UBLU, COLOR_RESET, URED, COLOR_RESET);

    scanf(" %c", &answer);
    
    if (answer == '1'){
        addNewApplicant(numApplicants, largestId);
        
    } else if(answer == '2'){
        waitListByCO2(applicantList, numApplicants);
        qsort(applicantList, numApplicants, sizeof(Applicant), compareByCO2);
        outputList(applicantList, numApplicants, 1);

    } else if(answer == '3'){
        
        qsort(applicantList, numApplicants, sizeof(Applicant), compareBySeniority);
        outputList(applicantList, numApplicants, 0);

    } else if(answer == '4'){
        char next = 'y';
        int turn = 1;
        int index = 0;
        waitListByCO2(applicantList, numApplicants); //Initiate array

        do {
            sortBySolution(applicantList, numApplicants, turn, index);
            printf("Want next applicant? (y/n):   ");
            scanf(" %c", &next);
            turn++;
            if (!isEven(turn)){ // Only increment index every other turn
                index++;
            }
        } while (next == 'y');
    }

    return 0;
}

void addNewApplicant(int numApplicants, int largestId){
    double applicantLat, applicantLon;
    double workLat, workLon;
    int result = 0;
    int homePostal;
    char homeStreet[NAME_LENGTH];
    int occPostal;
    char occStreet[NAME_LENGTH]; 

    // Applicant home coordinates
    while(result != 1){
        getInputHome(&homePostal, homeStreet);
        result = getCoordinates(homePostal, homeStreet, &applicantLat, &applicantLon);
    }
    result = 0;

    // Applicant work-site coordinates
    while(result != 1){
        getInputOccupation(&occPostal, occStreet); 
        result = getCoordinates(occPostal, occStreet, &workLat, &workLon); 
    }
    
    newApplicant(largestId, numApplicants, homePostal, applicantLat, applicantLon, workLat, workLon, 0);
}


void waitListByCO2(Applicant *applicantList, int numApplicants){
    double avaHousingLat, avaHousingLon; 
    int result = 0;
    int avaPostal;
    char avaStreet[NAME_LENGTH];
    // Get input for available housing
    while (result != 1){
        getInputHousing(&avaPostal, avaStreet);
        result = getCoordinates(avaPostal, avaStreet, &avaHousingLat, &avaHousingLon);
    }


    for (int i = 0; i < numApplicants; i++){
        double distanceCurrent = calcDistKm(applicantList[i].xCoordHome, applicantList[i].yCoordHome, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc);
        // Distance between available housing and work
        double distanceNew = calcDistKm(avaHousingLat, avaHousingLon, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc);

        // Calculate CO2 emissions
        double CO2Current = calculateEmissions(distanceCurrent, "Car");

        // Calculate new CO2 emissions
        double CO2New = calculateEmissions(distanceNew, "Car");

        double CO2Savings = CO2Current - CO2New;

        // update applicant to array
        applicantList[i] = (Applicant){applicantList[i].id, applicantList[i].postal, applicantList[i].xCoordHome, applicantList[i].yCoordHome, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc,
                                                            applicantList[i].daysOnList, distanceCurrent, distanceNew, CO2Current, CO2New, CO2Savings};
    }
}


int compareByCO2(const void *a, const void *b){
    // Cast the input pointers
    const Applicant *applicantA = (const Applicant *)a;
    const Applicant *applicantB = (const Applicant *)b;

    // Calculate the difference in CO2Savings between the two applicantList
    double CO2Diff = applicantA->CO2Savings - applicantB->CO2Savings;
    
    // If difference in CO2Savings is small (less than 0.5), prioritize by daysOnList
    if (CO2Diff > -0.5 && CO2Diff < 0.5){
        return applicantB->daysOnList - applicantA->daysOnList;  // Most days on list comes first
    }

    // The applicant with most CO2 Saving is prioritized
    if (applicantA->CO2Savings > applicantB->CO2Savings){
        return -1;
    }

    if (applicantA->CO2Savings < applicantB->CO2Savings){
        return 1;  
    }

    return 0;
}

int compareBySeniority(const void *a, const void *b){
    const Applicant *applicantA = (const Applicant *)a;
    const Applicant *applicantB = (const Applicant *)b;

    return applicantB->daysOnList - applicantA->daysOnList;
}

// Function to give out next applicant based on turn is even or odd
void sortBySolution(Applicant *applicantList, int numApplicants, int turn, int index){
    if (isEven(turn)){
        qsort(applicantList, numApplicants, sizeof(Applicant), compareBySeniority);
        outputNext(applicantList, turn, index);
    } else {
        qsort(applicantList, numApplicants, sizeof(Applicant), compareByCO2);
        outputNext(applicantList, turn, index);
     }
}

int isEven(int number){
    return number % 2 == 0;
}

// Status indicates information given in outputs (1 for information about distance and CO2)
void outputList(Applicant *applicantList, int numApplicants, int status){
    if (status == 1){
        printf("\nWaitlist based on CO2 reduction\n"); 
        printf("----------------------------------------------------------------\n");
        printf("| %-3s %-6s %-6s %-12s %-14s %-10s %-3s |\n", "Nr", "Postal", "Days", "Distance", "New Distance", "CO2", "ID");
        printf("| %-3s %-6s %-6s (km)%-8s (km)%-10s (kg)%-8s %-1s |\n", " ", " ", " ", " ", " ", " ", " ");
        
        printf("----------------------------------------------------------------\n");
        for (int i = 0; i < numApplicants; i++){
            printf("| %-3d %-6d %-6d %-12.2lf %-14.2lf %-10.2lf %-3d |\n", i + 1, applicantList[i].postal, applicantList[i].daysOnList, applicantList[i].distanceCurrent, applicantList[i].distanceNew, applicantList[i].CO2Savings, applicantList[i].id);           
        }
        printf("----------------------------------------------------------------\n");
    }
    else {
        printf("\nWaitlist based on days on list\n"); 
        printf("--------------------------\n");
        printf("| %-3s %-8s %-5s %-3s |\n", "Nr", "Postal", "Days", "ID");        
        printf("--------------------------\n");
        for (int i = 0; i < numApplicants; i++){
            printf("| %-3d %-8d %-5d %-3d |\n", i + 1, applicantList[i].postal, applicantList[i].daysOnList,  applicantList[i].id);           
        }
        printf("--------------------------\n");
    }
}

void outputNext(Applicant *applicantList, int turn, int index){
    if (isEven(turn)){
        printf("\nNext applicant in line is: (Based on days on waitlist)\n");
        printf("--------------------------\n");
        printf("| %-3s %-8s %-5s %-3s |\n", "Nr", "Postal", "Days", "ID");        
        printf("| %-3d %-8d %-5d %-3d |\n", turn, applicantList[index].postal, applicantList[index].daysOnList,  applicantList[index].id);           
        printf("--------------------------\n");
    } else {
        printf("\nNext applicant in line is: (Based on CO2 savings)\n");
        printf("----------------------------------------------------------------\n");
        printf("| %-3s %-6s %-6s %-12s %-14s %-10s %-3s |\n", "Nr", "Postal", "Days", "Distance", "New Distance", "CO2", "ID");
        printf("| %-3s %-6s %-6s (km)%-8s (km)%-10s (kg)%-8s %-1s |\n", " ", " ", " ", " ", " ", " ", " "); 
        printf("| %-3d %-6d %-6d %-12.2lf %-14.2lf %-10.2lf %-3d |\n", turn, applicantList[index].postal, applicantList[index].daysOnList, applicantList[index].distanceCurrent, applicantList[index].distanceNew, applicantList[index].CO2Savings, applicantList[index].id);           
        printf("----------------------------------------------------------------\n");
    }
}
