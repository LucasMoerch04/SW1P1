#ifndef APPLICANTSTRUCT_H
#define APPLICANTSTRUCH_H

#include <stdio.h>
#include <stdlib.h>


// Structure to hold the response data
typedef struct Applicant{
    int id;
    int postal;
    double distance;
    int daysOnList;
    double newCO2;
    double preCO2;
    
} Applicant;



// Function prototypes
Applicant *makeApplicantsArray(int *numApplicants);
void readApplicantsList(Applicant *applicantArray, int *numApplicants);
void newApplicant(int *numApplicants, int postal, double distance, int daysOnList, double newCO2, double preCO2);




#endif 
