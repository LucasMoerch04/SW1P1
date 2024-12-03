#include <stdio.h>
#include <stdlib.h>

#define MAX_APPLICANTS 100

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
        double xCoordHomeTemp, yCoordHomeTemp, xCoordOccTemp, yCoordOccTemp, CO2CurrentTemp, CO2NewTemp;

        while (fscanf(file, "%d %d %lf %lf %lf %lf %d", &id, &postalTemp, &xCoordHomeTemp, &yCoordHomeTemp, &xCoordOccTemp, &yCoordOccTemp,
                      &daysOnListTemp) == 7){
            if (id > *largestId){
                *largestId = id;
            }
            // add applicant to array
            applicants[*numApplicants] = (Applicant){id, postalTemp,xCoordHomeTemp, yCoordHomeTemp, xCoordOccTemp, yCoordOccTemp, 
                                                     daysOnListTemp, 0, 0, 0.0, 0.0, 0.0 };
        
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