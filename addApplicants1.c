#include <stdio.h>
#include <stdlib.h>

#define MAX_APPLICANTS 100

// Struct
typedef struct {
    int id;
    int postal;
    double distance;
    int daysOnList;
    double newCO2;
    double preCO2;
} Applicant;

// Function for add applicant
void addApplicant(Applicant *applicantArray, int *numApplicants, const char *filePath, 
                  int postal, double distance, int daysOnList, double newCO2, double preCO2);

int main() {
    // Array to hold applicants and a counter for the number of applicants
    Applicant applicants[MAX_APPLICANTS];
    int num_applicants = 0;

    const char *file_path = "applicants.txt";

    // Example data for a new applicant
    int postal = ?;
    double distance = ?;
    int daysOnList = ?;
    double newCO2 = ?;
    double preCO2 = ?;

    // Add a new applicant
    addApplicant(applicants, &num_applicants, file_path, postal, distance, daysOnList, newCO2, preCO2);

    // Print the details of all applicants
    for (int i = 0; i < num_applicants; i++) {
        printf("ID: %d, Postal: %d, Distance: %.2f, Days: %d, New CO2: %.2f, Pre CO2: %.2f\n",
               applicants[i].id, applicants[i].postal, applicants[i].distance,
               applicants[i].daysOnList, applicants[i].newCO2, applicants[i].preCO2);
    }

    return 0;
}

// Function to add a new applicant
void addApplicant(Applicant *applicantArray, int *numApplicants, const char *filePath, 
                  int postal, double distance, int daysOnList, double newCO2, double preCO2) {
    int largestId = 0;

    // Open the file
    FILE *file = fopen(filePath, "r");

    if (file) {
        int id, postalTemp, daysOnListTemp;
        double distanceTemp, newCO2Temp, preCO2Temp;

        // Read the file to find the largest ID
        while (fscanf(file, "%d %d %lf %d %lf %lf", &id, &postalTemp, &distanceTemp, 
                      &daysOnListTemp, &newCO2Temp, &preCO2Temp) == 6) {
            if (id > largestId) {
                largestId = id;
            }
        }
        fclose(file);
        } else {
            printf("File not found. Starting IDs from 1.\n");
        }

    // Generate a new ID
    int newId = largestId + 1;

    // Create a new applicant
    Applicant newApplicant = {newId, postal, distance, daysOnList, newCO2, preCO2};

    // Add the new applicant to the array
    applicantArray[*numApplicants] = newApplicant;

    // Increment the count of applicants
    (*numApplicants)+= 1;
}
