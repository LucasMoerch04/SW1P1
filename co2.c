#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "co2.h"

// Grams of CO2 emission per km
#define carCo2 166
#define busCo2 93
#define metroCo2 63
#define trainCo2 58


double calculateCo2(double distance, double co2PerKilometer, double co2emission);


double calculateEmissions(double distance, char transportType[]){
    double co2PerKilometer;
    double co2emission;
    if (strcmp(transportType, "Car") == 0){
        co2PerKilometer = carCo2;
        co2emission = calculateCo2(distance, co2PerKilometer, co2emission);

    } else if (strcmp(transportType, "Bus") == 0){
        co2PerKilometer = busCo2;
        co2emission = calculateCo2(distance, co2PerKilometer, co2emission);

    } else if (strcmp(transportType, "Metro") == 0){
        co2PerKilometer = metroCo2;
        co2emission = calculateCo2(distance, co2PerKilometer, co2emission);

    } else if (strcmp(transportType, "Train") == 0){
        co2PerKilometer = trainCo2;
        co2emission = calculateCo2(distance, co2PerKilometer, co2emission);

    } else{
        printf("Invalid transport type");
        return -1;
    }

    return co2emission;
}

double calculateCo2(double distance, double co2PerKilometer, double co2emission){
    double co2PerKmInKg = co2PerKilometer / 1000;
    double co2Discharge = co2PerKmInKg * distance;

    return co2Discharge;
}
