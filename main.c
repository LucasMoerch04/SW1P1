#include <stdio.h>
#include <stdlib.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"
#include "co2.h"

void getCoords(int postal, char *streetName, double *lat, double *lon);
int compare(const void *a, const void *b);


int main(void){

    double avaHousingLat, avaHousingLon; 
    double applicantLat, applicantLon;
    double workLat, workLon;

    // Available housing coordinates
    getCoords(2450, "Sluseholmen", &avaHousingLat, &avaHousingLon);

    // Applicant coordinates
    getCoords(2650, "Bymuren", &applicantLat, &applicantLon);
    
    // Applicant work-site coordinates
    getCoords(2450, "Frederikskaj", &workLat, &workLon);
    
    // Distance between available housing and applicant
    double distance = calcDistKm(avaHousingLat, avaHousingLon, applicantLat, applicantLon);
    printf("Distance: %lf\n", distance);

    // Distance between available housing and work
    double newDistance = calcDistKm(avaHousingLat, avaHousingLon, workLat, workLon);
    printf("New distance: %lf\n", newDistance);

    // Calculate CO2 emissions
    double preCO2 = CalculateEmissions(25600000000, "Car");
    printf("CO2: %lf\n", preCO2);

    // Calculate new CO2 emissions
    double newCO2 = CalculateEmissions(newDistance, "Car");
    printf("New CO2: %lf\n", newCO2);


    Applicant *applicantList = createDefaultList();

    qsort(applicantList, 10, sizeof(Applicant), compare);

    for (int i = 0; i < 10; i++){

        printf("ID: %d Postal: %d Distance: %lf Days on list: %d New CO2: %lf Pre CO2: %lf\n", applicantList[i].id, applicantList[i].postal, 
                                    applicantList[i].distance, applicantList[i].daysOnList, 
                                    applicantList[i].newCO2, applicantList[i].preCO2);
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
    // Postal is same, sort by days on list
    if ( applicantA->postal == applicantB->postal){
        return applicantB->daysOnList - applicantA->daysOnList;
    }
    
    // Sort by distance
    if (applicantA->distance < applicantB->distance) return -1;
    if (applicantA->distance > applicantB->distance) return 1;
    return 0;
}