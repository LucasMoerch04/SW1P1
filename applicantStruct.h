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
Applicant *createDefaultList(void);
int getListSize(Applicant *applicants);
void addApplicants(Applicant *applicantArray, int *numApplicants, const char *filePath, 
                  int postal, double distance, int daysOnList, double newCO2, double preCO2);



#endif 
