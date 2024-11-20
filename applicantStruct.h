#ifndef APPLICANTSTRUCT_H
#define APPLICANTSTRUCH_H

#include <stdio.h>


// Structure to hold the response data
typedef struct Applicant {
    int id;
    int postal;
    double distance;
    int days_on_list;
    double new_CO2;
    double pre_CO2;
    
} Applicant;



// Function prototypes
Applicant default_list(void);


#endif 
