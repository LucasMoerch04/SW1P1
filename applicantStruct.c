#include <stdio.h>


// Change length based on number of applicants here:
#define LENGTH 0

typedef struct Applicant {
    int id;
    int postal;
    double distance;
    int days_on_list;
    double new_CO2;
    double pre_CO2;
    
} Applicant;

Applicant default_list(void){
    // Initiate applicants array
    Applicant *applicants;
    
    // TODO: INSERT DEFAULT APPLICANTS HERE
    Applicant test;
    test.id = 1;
    test.postal = 2650;
    test.distance = 2.4;
    test.days_on_list = 232;
    test.new_CO2 = 3.02;
    test.pre_CO2 = 23.2;

    // Saves test-person to array
    applicants[0] = test;

    // Prints every applicant's data
    for (int i = 0; i < LENGTH; i++){

    printf("%d %d %lf %d %lf %lf\n", applicants[i].id, applicants[i].postal, 
                                   applicants[i].distance, applicants[i].days_on_list, 
                                   applicants[i].new_CO2, applicants[i].pre_CO2);
    }



    return *applicants;
}

