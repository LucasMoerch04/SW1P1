#include <stdio.h>
#include <stdlib.h>

#define MAX_APPLICANTS 100

typedef struct Applicant{
    int id;
    int postal;
    double distance;
    int daysOnList;
    double newCO2;
    double preCO2;
} Applicant;

void readApplicantsList(Applicant *applicants, int *numApplicants);
void newApplicant(int numApplicants, int postal, double distance, int daysOnList, double newCO2, double preCO2);


Applicant *makeApplicantsArray(int *numApplicants){
    Applicant *applicants = malloc(MAX_APPLICANTS * sizeof(Applicant));
    if (applicants == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    
    readApplicantsList(applicants, numApplicants);

    return applicants;
}

void readApplicantsList(Applicant *applicants, int *numApplicants){
    int largestId = 0;

    // Open txt file
    const char *filePath = "applicants.txt";
    FILE *file = fopen(filePath, "r");

    if (file){
        int id, postalTemp, daysOnListTemp;
        double distanceTemp, newCO2Temp, preCO2Temp;

        while (fscanf(file, "%d %d %lf %d %lf %lf", &id, &postalTemp, &distanceTemp, 
                      &daysOnListTemp, &newCO2Temp, &preCO2Temp) == 6){
            if (id > largestId){
                largestId = id;
            }
            // add applicant to array
            applicants[*numApplicants] = (Applicant){id, postalTemp, distanceTemp, 
                                                     daysOnListTemp, newCO2Temp, preCO2Temp};
            // 
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

void newApplicant(int numApplicants, int postal, double distance, int daysOnList, double newCO2, double preCO2){
    FILE *file = fopen("applicants.txt", "a");
    int id = numApplicants + 1;

    if (file){
        fprintf(file, "\n%d %d %lf %d %lf %lf", id, postal, distance, daysOnList, newCO2, preCO2);
        printf("applicatn added\n");
    }
    fclose(file);
}