#ifndef CO2_H
#define CO2_H

/* Based on 
    https://www.navit.com/resources/bus-train-car-or-e-scooter-carbon-emissions-of-transport-modes-ranked
*/

double calculateCo2(double distance, double co2PerKilometer, double co2emission);
double calculateEmissions(double distance, char transportType[]);

#endif
