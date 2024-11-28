#include <stdio.h>
#include <stdlib.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"
#include "co2.h"

void get_coords(int postal, char *street_name, double *lat, double *lon);
int compare(const void *a, const void *b);


int main(void){

    double ava_housing_lat, ava_housing_lon; 
    double applicant_lat, applicant_lon;
    double work_lat, work_lon;

    // Available housing coordinates
    get_coords(2450, "Sluseholmen", &ava_housing_lat, &ava_housing_lon);

    // Applicant coordinates
    get_coords(2650, "Bymuren", &applicant_lat, &applicant_lon);
    
    // Applicant work-site coordinates
    get_coords(2450, "Frederikskaj", &work_lat, &work_lon);
    
    // Distance between available housing and applicant
    double distance = haversine(ava_housing_lat, ava_housing_lon, applicant_lat, applicant_lon);
    printf("Distance: %lf\n", distance);

    // Distance between available housing and work
    double new_distance = haversine(ava_housing_lat, ava_housing_lon, work_lat, work_lon);
    printf("New distance: %lf\n", new_distance);

    // Calculate CO2 emissions
    double pre_CO2 = CalculateEmissions(distance, "Car");
    printf("CO2: %lf\n", pre_CO2);

    // Calculate new CO2 emissions
    double new_CO2 = CalculateEmissions(new_distance, "Car");
    printf("New CO2: %lf\n", new_CO2);


    Applicant *applicant_list = create_default_list();

    qsort(applicant_list, 3, sizeof(Applicant), compare);

    for (int i = 0; i < 3; i++){

        printf("ID: %d Postal: %d Distance: %lf Days on list: %d New CO2: %lf Pre CO2: %lf\n", applicant_list[i].id, applicant_list[i].postal, 
                                    applicant_list[i].distance, applicant_list[i].days_on_list, 
                                    applicant_list[i].new_CO2, applicant_list[i].pre_CO2);
    }

    return 0;
}

void get_coords(int postal, char *street_name, double *lat, double *lon) {
    if (get_coordinates(postal, street_name, lat, lon) != 1) {
        printf("Error retrieving coordinates\n");
    }
}


int compare(const void *a, const void *b) {
    const Applicant *applicantA = (const Applicant *)a;
    const Applicant *applicantB = (const Applicant *)b;
    // Postal is same, sort by days on list
    if ( applicantA->postal == applicantB->postal){
        return applicantB->days_on_list - applicantA->days_on_list;
    }
    
    // Sort by distance
    if (applicantA->distance < applicantB->distance) return -1;
    if (applicantA->distance > applicantB->distance) return 1;
    return 0;
}