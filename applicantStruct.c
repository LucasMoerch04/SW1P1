#include <stdio.h>
#include <stdlib.h>


// Change length based on number of applicants here:

typedef struct Applicant {
    int id;
    int postal;
    double distance;
    int days_on_list;
    double new_CO2;
    double pre_CO2;
    
} Applicant;



Applicant *create_default_list(void){
    // Initiate applicants array
    Applicant *applicants = malloc(3 * sizeof(Applicant));
    if (applicants == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // TODO: INSERT DEFAULT APPLICANTS HERE
    Applicant test;
    test.id = 1;
    test.postal = 2650;
    test.distance = 2.8;
    test.days_on_list = 432;
    test.new_CO2 = 3.02;
    test.pre_CO2 = 23.2;

    // Saves test-person to array
    applicants[0] = test;


    Applicant test2;
    test2.id = 2;
    test2.postal = 2550;
    test2.distance = 2.6;
    test2.days_on_list = 22;
    test2.new_CO2 = 2.02;
    test2.pre_CO2 = 13.2;

    // Saves test-person to array
    applicants[1] = test2;

    Applicant test3;
    test3.id = 3;
    test3.postal = 2650;
    test3.distance = 2.7;
    test3.days_on_list = 322;
    test3.new_CO2 = 2.02;
    test3.pre_CO2 = 13.2;

    // Saves test-person to array
    applicants[2] = test3;

    
    // Prints every applicant's data
    for (int i = 0; i < 3; i++){

    printf("ID: %d Postal: %d Distance: %lf Days on list: %d New CO2: %lf Pre CO2: %lf\n", applicants[i].id, applicants[i].postal, 
                                   applicants[i].distance, applicants[i].days_on_list, 
                                   applicants[i].new_CO2, applicants[i].pre_CO2);
    }



    return applicants;
}

