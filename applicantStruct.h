#ifndef APPLICANTSTRUCT_H
#define APPLICANTSTRUCH_H

#include <stdio.h>
#include <stdlib.h>


// Structure to hold the response data
typedef struct Applicant{
    int id;
    int postal;
    double xCoordHome;
    double yCoordHome;
    double xCoordOcc;
    double yCoordOcc;
    int daysOnList;
    double distanceCurrent;
    double distanceNew;
    double CO2Current;
    double CO2New;
    double CO2Savings;
} Applicant;


// Function prototypes
Applicant *makeApplicantsArray(int *numApplicants, int *largestId);
void newApplicant(int largestId, int numApplicants, int postal, double xCoordHome, double yCoordHome, double xCoordOcc, double yCoordOcc, int daysOnList);


#endif 
