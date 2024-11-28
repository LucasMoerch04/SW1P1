#include <stdio.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"
#include "co2.h"

int main(void){

    // Available housing coordinates
    double ava_housing_lat, ava_housing_lon;
    if (get_coordinates(2450, "Sluseholmen", &ava_housing_lat, &ava_housing_lon) != 1) {
        printf("Error retrieving coordinates for available housing.\n");
        return 1;
    }

    // Applicant coordinates
    double applicant_lat, applicant_lon;
    if (get_coordinates(2650, "Bymuren", &applicant_lat, &applicant_lon) != 1) {
        printf("Error retrieving coordinates for applicant.\n");
        return 1;
    }

    // Applicant work-site coordinates
    double work_lat, work_lon;
    if (get_coordinates(2450, "Frederikskaj", &work_lat, &work_lon) != 1) {
        printf("Error retrieving coordinates for work-site.\n");
        return 1;
    }


    // Distance between available housing and applicant
    double distance = haversine(ava_housing_lat, ava_housing_lon, applicant_lat, applicant_lon);
    printf("Distance: %lf\n", distance);

    // Distance between available housing and work
    double new_distance = haversine(ava_housing_lat, ava_housing_lon, work_lat, work_lon);
    printf("New distance: %lf\n", new_distance);

    double pre_CO2 = CalculateEmissions(distance, "Car");
    printf("CO2: %lf\n", pre_CO2);

    double new_CO2 = CalculateEmissions(new_distance, "Car");
    printf("New CO2: %lf\n", new_CO2);

    return 0;
}
