#include <stdio.h>
#include <stdlib.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"
#include "co2.h"
#include "getInputs.h"

void addNewApplicant(int numApplicants);
void waitListByCO2(Applicant *applicants, int numApplicants);

void getCoords(int postal, char *streetName, double *lat, double *lon);
int compareByCO2(const void *a, const void *b);
int compareBySeniority(const void *a, const void *b);
void outputList(Applicant *applicantList, int numApplicants, int status);


int occupationPostal = 0;


int main(void){

    double avaHousingLat, avaHousingLon; 
    double applicantLat, applicantLon;
    double workLat, workLon;
    int numApplicants = 0;
    char answer;
    Applicant *applicantList = makeApplicantsArray(&numApplicants);

    printf("Tast 1 for at tilføje en ansøger\n");
    printf("Tast 2 for at printe ventelisten, baseret på CO2 besparelse\n");
    printf("Tast 3 for at printe ventelisten, baseret på ventetid\n");
    printf("Tast q for at slutte programmet\n");

    scanf(" %c", &answer);
    
    if (answer == '1'){
        addNewApplicant(numApplicants);

    } else if(answer == '2'){
        waitListByCO2(applicantList, numApplicants);
        qsort(applicantList, numApplicants, sizeof(Applicant), compareByCO2);
        outputList(applicantList, numApplicants, 1);

    } else if(answer == '3'){
        qsort(applicantList, numApplicants, sizeof(Applicant), compareBySeniority);
        outputList(applicantList, numApplicants, 0);
        
    }

    return 0;
}

void addNewApplicant(int numApplicants){
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
    
    
    newApplicant(numApplicants, homePostal, applicantLat, applicantLon, workLat, workLon, 0);
}

void waitListByCO2(Applicant *applicantList, int numApplicants){
    double avaHousingLat, avaHousingLon; 

    int avaPostal;
    char avaStreet[NAME_LENGTH];
    // Get input for available housing
    getInputHousing(&avaPostal, avaStreet);
    getCoords(avaPostal, avaStreet, &avaHousingLat, &avaHousingLon);
    occupationPostal = 9400;

    for (int i = 0; i < numApplicants; i++){
        double distanceCurrent = calcDistKm(applicantList[i].xCoordHome, applicantList[i].yCoordHome, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc);
        // Distance between available housing and work
        double distanceNew = calcDistKm(avaHousingLat, avaHousingLon, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc);

        // Calculate CO2 emissions
        double CO2Current = CalculateEmissions(distanceCurrent, "Car");

        // Calculate new CO2 emissions
        double CO2New = CalculateEmissions(distanceNew, "Car");

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

    // Calculate the difference in CO2Savings between the two applicants
    double CO2Diff = applicantA->CO2Savings - applicantB->CO2Savings;
    
    // If difference in CO2Savings is small (less than 0.5), prioritize by daysOnList
    if (CO2Diff > -0.5 && CO2Diff < 0.5){
        return applicantB->daysOnList - applicantA->daysOnList;  // Most days on list comes first
    }

    // The applicant with most CO2 Saving is prioritized
    if (applicantA->CO2Savings > applicantB->CO2Savings){
        return 1;
    }

    if (applicantA->CO2Savings < applicantB->CO2Savings){
        return -1;  
    }

    return 0;
}

int compareBySeniority(const void *a, const void *b){
    const Applicant *applicantA = (const Applicant *)a;
    const Applicant *applicantB = (const Applicant *)b;

    return applicantB->daysOnList - applicantA->daysOnList;
}

void outputList(Applicant *applicantList, int numApplicants, int status){
    if (status == 1){
        for (int i = 0; i < numApplicants; i++){
            printf("\nID: %d Postal: %d Days On List: %d DistanceCURRENT: %.2lf DistanceNEW: %.2lf CO2 SAVED: %lf\n", applicantList[i].id, applicantList[i].postal, applicantList[i].daysOnList, applicantList[i].distanceCurrent, applicantList[i].distanceNew, applicantList[i].CO2Savings);           
        }   
    }
    else {
        for (int i = 0; i < numApplicants; i++){
            printf("\nID: %d Postal: %d Days On List: %d\n", applicantList[i].id, applicantList[i].postal, applicantList[i].daysOnList);           
        }   
    }
    

    
}


