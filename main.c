#include <stdio.h>
#include <stdlib.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"
#include "co2.h"
#include "getInputs.h"
#include "CuTest.h"
#include "runTests.h"

void addNewApplicant(int numApplicants, int largestId);
void waitListByCO2(Applicant *applicantList, int numApplicants);
void getCoords(int postal, char *streetName, double *lat, double *lon);
int compareByCO2(const void *a, const void *b);
int compareBySeniority(const void *a, const void *b);
void sortBySolution(Applicant *applicantList, int numApplicants, int turn, int index);
void outputList(Applicant *applicantList, int numApplicants, int status);
int isEven(int number);


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

    printf("Tast 1 for at tilføje en ansøger\n");
    printf("Tast 2 for at printe ventelisten, baseret på CO2 besparelse\n");
    printf("Tast 3 for at printe ventelisten, baseret på ventetid\n");
    printf("Tast 4 for at printe ventelisten, baseret på VORES LØSNING IDK\n");
    printf("Tast q for at slutte programmet\n");

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
            printf("Want next applicant? (y/n) ");
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

    int homePostal;
    char homeStreet[NAME_LENGTH];
    int occPostal;
    char occStreet[NAME_LENGTH]; 

    // Get inputs
    getInputHome(&homePostal, homeStreet);
    getInputOccupation(&occPostal, occStreet); 

    // Applicant home coordinates
    getCoords(homePostal, homeStreet, &applicantLat, &applicantLon);
    
    // Applicant work-site coordinates
    getCoords(occPostal, occStreet, &workLat, &workLon);
    
    newApplicant(largestId, numApplicants, homePostal, applicantLat, applicantLon, workLat, workLon, 0);
}

void waitListByCO2(Applicant *applicantList, int numApplicants){
    double avaHousingLat, avaHousingLon; 

    int avaPostal;
    char avaStreet[NAME_LENGTH];
    // Get input for available housing
    getInputHousing(&avaPostal, avaStreet);
    getCoords(avaPostal, avaStreet, &avaHousingLat, &avaHousingLon);


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

void getCoords(int postal, char *streetName, double *lat, double *lon){
    if (getCoordinates(postal, streetName, lat, lon) != 1) {
        printf("Error retrieving coordinates\n");
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
        printf("Next applicant in line is: (Based on days on waitlist)\n");
        printf("\n%d | ID: %d Postal: %d Days On List: %d\n", turn, applicantList[index].id, applicantList[index].postal, applicantList[index].daysOnList);
        
    } else {
        qsort(applicantList, numApplicants, sizeof(Applicant), compareByCO2);
        printf("Next applicant in line is: (Based on CO2 savings)\n");
        printf("\n%d | ID: %d Postal: %d Days On List: %d DistanceCURRENT: %.2lf DistanceNEW: %.2lf CO2 SAVED: %lf\n", turn, applicantList[index].id, applicantList[index].postal, applicantList[index].daysOnList, applicantList[index].distanceCurrent, applicantList[index].distanceNew, applicantList[index].CO2Savings);           
    }
}

int isEven(int number){
    return number % 2 == 0;
}


// Status indicates information given in outputs (1 for information about distance and CO2)
void outputList(Applicant *applicantList, int numApplicants, int status){
    if (status == 1){
        for (int i = 0; i < numApplicants; i++){
            printf("\n%d | ID: %d Postal: %d Days On List: %d DistanceCURRENT: %.2lf DistanceNEW: %.2lf CO2 SAVED: %lf\n", i, applicantList[i].id, applicantList[i].postal, applicantList[i].daysOnList, applicantList[i].distanceCurrent, applicantList[i].distanceNew, applicantList[i].CO2Savings);           
        }   
    }
    else {
        for (int i = 0; i < numApplicants; i++){
            printf("\n%d | ID: %d Postal: %d Days On List: %d\n", i, applicantList[i].id, applicantList[i].postal, applicantList[i].daysOnList);           
        }   
    }
}
