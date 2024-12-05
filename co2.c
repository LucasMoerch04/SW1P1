#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "co2.h"

#define carCo2 166
#define busCo2 93
#define metroCo2 63
#define trainCo2 58
#define walkCo2 0
#define bikeCo2 0

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

    } else if (strcmp(transportType, "Walk") == 0 || strcmp(transportType, "Bike") == 0){
        co2PerKilometer = walkCo2;
        co2emission = calculateCo2(distance, co2PerKilometer, co2emission);

    } else{
        printf("Invalid transport type");
    }

    return co2emission;
}

double calculateCo2(double distance, double co2PerKilometer, double co2emission){
    // 0.166 grams of CO2 per kilometer in car
    double co2PerKmInKg = co2PerKilometer / 1000;
    double co2Discharge = co2PerKmInKg * distance;

    return co2Discharge;
}
