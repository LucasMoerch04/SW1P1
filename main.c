#include <stdio.h>
#include <stdlib.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"
#include "co2.h"
#include "getInputs.h"

void getCoords(int postal, char *streetName, double *lat, double *lon);
int compare(const void *a, const void *b);

int occupationPostal = 0;


int main(void){

    double avaHousingLat, avaHousingLon; 
    double applicantLat, applicantLon;
    double workLat, workLon;
    int numApplicants = 0;
    char answer;
    printf("test");
    Applicant *applicantList = makeApplicantsArray(&numApplicants);

    printf("Tilføj ansøger? (y/n)\n");
    scanf(" %c", &answer);

    

    // Call func to calculate data and insert to newApplicant()



    if (answer == 'y'){
            
        int homePostal;
        char homeStreet[NAME_LENGTH]; // Allocate space for the street name
        int occPostal;
        char occStreet[NAME_LENGTH];  // Allocate space for the street name

        // Get inputs
        getInputHome(&homePostal, homeStreet); // Pass address of homePostal
        getInputOccupation(&occPostal, occStreet); // Pass address of occPostal

        // Applicant coordinates
        getCoords(homePostal, homeStreet, &applicantLat, &applicantLon);
        
        // Applicant work-site coordinates
        getCoords(occPostal, occStreet, &workLat, &workLon);
        
        
        newApplicant(numApplicants, homePostal, applicantLat, applicantLon, workLat, workLon, 0);

    } else if(answer == 'n'){
        int avaPostal;
        char avaStreet[NAME_LENGTH];
        // Get input for available housing
        getInputHousing(&avaPostal, avaStreet);
        getCoords(avaPostal, avaStreet, &avaHousingLat, &avaHousingLon);
        occupationPostal = 9400;

        for (int i = 0; i < numApplicants; i++){
            printf("HER%lf", applicantList[i].xCoordOcc);
            double distanceCurrent = calcDistKm(applicantList[i].yCoordHome, applicantList[i].xCoordHome, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc);
            // Distance between available housing and work
            double distanceNew = calcDistKm(avaHousingLat, avaHousingLon, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc);

            // Calculate CO2 emissions
            double CO2Current = CalculateEmissions(distanceCurrent, "Car");

            // Calculate new CO2 emissions
            double CO2New = CalculateEmissions(distanceNew, "Car");

            // update applicant to array
            applicantList[i] = (Applicant){applicantList[i].id, applicantList[i].postal, applicantList[i].xCoordHome, applicantList[i].yCoordHome, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc,
                      applicantList[i].daysOnList, distanceCurrent, distanceNew, CO2Current, CO2New};
        }
    
        // Create sorted list
        qsort(applicantList, numApplicants, sizeof(Applicant), compare);
        for (int i = 0; i < numApplicants; i++){
        printf("\nID: %d Postal: %d HomeCOORDS: %lf %lf OccCOORDS: %lf %lf DaysOnList: %d DistanceCURRENT: %lf DistanceNEW: %lf %lf %lf\n", applicantList[i].id, applicantList[i].postal, applicantList[i].xCoordHome, applicantList[i].yCoordHome, applicantList[i].xCoordOcc, applicantList[i].yCoordOcc,
                      applicantList[i].daysOnList, applicantList[i].distanceCurrent, applicantList[i].distanceNew, applicantList[i].CO2Current, applicantList[i].CO2New);
    }
    }

    return 0;
}

void getCoords(int postal, char *streetName, double *lat, double *lon) {
    if (getCoordinates(postal, streetName, lat, lon) != 1) {
        printf("Error retrieving coordinates\n");
    }
}


int compare(const void *a, const void *b) {
    const Applicant *applicantA = (const Applicant *)a;
    const Applicant *applicantB = (const Applicant *)b;

    if (applicantA->postal == occupationPostal){
        return -1;
    }
    
    if (applicantB->postal == occupationPostal) {
        return 1; // Lower priority
    }

    // Postal is same, sort by days on list
    if ( applicantA->postal == applicantB->postal){
        return applicantB->daysOnList - applicantA->daysOnList;
    }
    
    // Sort by distance
    if (applicantA->distanceCurrent < applicantB->distanceCurrent) return 1;
    if (applicantA->distanceCurrent > applicantB->distanceCurrent) return -1;

    return 0;
}