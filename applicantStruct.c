#include <stdio.h>
#include <stdlib.h>

#define MAX_APPLICANTS 100

typedef struct Applicant {
    int id;
    int postal;
    double distance;
    int daysOnList;
    double newCO2;
    double preCO2;
} Applicant;
 

void addApplicants(Applicant *applicants, int *numApplicants) {
    int largestId = 0;

    // Open txt file
    const char *filePath = "applicants.txt";
    FILE *file = fopen(filePath, "r");

    if (file) {
        // Initialize temp values
        int id, postalTemp, daysOnListTemp;
        double distanceTemp, newCO2Temp, preCO2Temp;

        while (fscanf(file, "%d %d %lf %d %lf %lf", &id, &postalTemp, &distanceTemp, 
                      &daysOnListTemp, &newCO2Temp, &preCO2Temp) == 6) {
            // Look for biggest id number
            if (id > largestId) {
                largestId = id;
            }
            // add applicant to array
            applicants[*numApplicants] = (Applicant){id, postalTemp, distanceTemp, 
                                                     daysOnListTemp, newCO2Temp, preCO2Temp};
            // 
            (*numApplicants)++;
            if (*numApplicants >= MAX_APPLICANTS) {
                printf("Maximum number of applicants reached!\n");
                break;
            }
        }
        fclose(file);
    } else {
        printf("File not found. Starting IDs from 1.\n");
    }
}

Applicant *create_default_list(void) {
    Applicant *applicants = malloc(MAX_APPLICANTS * sizeof(Applicant));
    if (applicants == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int numApplicants = 0;

    addApplicants(applicants, &numApplicants);

    for (int i = 0; i < numApplicants; i++) {
        printf("ID: %d, Postal: %d, Distance: %.2f, Days: %d, New CO2: %.2f, Pre CO2: %.2f\n",
               applicants[i].id, applicants[i].postal, applicants[i].distance,
               applicants[i].daysOnList, applicants[i].newCO2, applicants[i].preCO2);
    }
    
    return applicants;
}