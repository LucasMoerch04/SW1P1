#include <stdio.h>
#include <stdlib.h>
#include "applicantStruct.h"

#define MAX_APPLICANTS 100

void readApplicantsList(Applicant *applicants, int *numApplicants, int *largestId);
void newApplicant(int largestId, int numApplicants, int postal, double xCoordHome, double yCoordHome, double xCoordOcc, double yCoordOcc, int daysOnList);


Applicant *makeApplicantsArray(int *numApplicants, int *largestId){
    Applicant *applicants = malloc(MAX_APPLICANTS * sizeof(Applicant));
    if (applicants == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    readApplicantsList(applicants, numApplicants, largestId);

    return applicants;
}

void readApplicantsList(Applicant *applicants, int *numApplicants, int *largestId){

    // Open txt file
    const char *filePath = "../applicants.txt";
    FILE *file = fopen(filePath, "r");

    if (file){
        int id, postalTemp, daysOnListTemp, distanceCurrentTemp, distanceNewTemp;
        int result;
        double xCoordHomeTemp, yCoordHomeTemp, xCoordOccTemp, yCoordOccTemp, CO2CurrentTemp, CO2NewTemp;

        while (1){
            result = fscanf(file, "%d %d %lf %lf %lf %lf %d", &id, &postalTemp, &xCoordHomeTemp, &yCoordHomeTemp, &xCoordOccTemp, &yCoordOccTemp,
                                                                &daysOnListTemp);
            if (result != 7){ // If file is finished or error in fscanf
                break;
            }
            if (id > *largestId){
                *largestId = id;
            }
            // add applicant to array
            Applicant app;
            app.id = id;
            app.postal = postalTemp;
            app.xCoordHome = xCoordHomeTemp;
            app.yCoordHome = yCoordHomeTemp;
            app.xCoordOcc = xCoordOccTemp;
            app.yCoordOcc = yCoordOccTemp;
            app.daysOnList = daysOnListTemp;
            app.distanceNew = 0;
            app.distanceCurrent = 0;
            app.CO2Current = 0;
            app.CO2New = 0;
            app.CO2Savings = 0;

            applicants[*numApplicants] = app;
        
            (*numApplicants)++;
            if (*numApplicants >= MAX_APPLICANTS){
                printf("Maximum number of applicants reached!\n");
                break;
            }
        }
        fclose(file);
    } else{
        printf("File not found. Starting IDs from 1.\n");
    }
}

void newApplicant(int largestId, int numApplicants, int postal, double xCoordHome, double yCoordHome, double xCoordOcc, double yCoordOcc, int daysOnList){
    FILE *file = fopen("../applicants.txt", "a");
    int id = largestId + 1;

    if (file){
        fprintf(file, "\n%d %d %lf %lf %lf %lf %d", id, postal, xCoordHome, yCoordHome, xCoordOcc, yCoordOcc, daysOnList);
        printf("Applicant added with ID: %d\n", id);
    }
    fclose(file);
}