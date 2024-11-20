
double co2PerKilometer;
double co2emission;

double calculateCo2(double distance)
{
    // 0.120 grams of CO2 per kilometer
    double co2PerKmInKg = co2PerKilometer / 1000;

    double co2Discharge = co2PerKmInKg * distance;

    return co2Discharge;
}

double CalculateEmissions(double distance, char transportType[])
{
    if (strcmp(transportType, "Car") == 0)
    {
        co2PerKilometer = 166;
        co2emission = calculateCo2(distance);
    }
    else if (strcmp(transportType, "Bus") == 0)
    {
        co2PerKilometer = 93;
        co2emission = calculateCo2(distance);
    }
    else if (strcmp(transportType, "Metro") == 0)
    {
        co2PerKilometer = 63;
        co2emission = calculateCo2(distance);
    }
    else if (strcmp(transportType, "Train") == 0)
    {
        co2PerKilometer = 58;
        co2emission = calculateCo2(distance);
    }
    else if (strcmp(transportType, "Walk") == 0 || strcmp(transportType, "Bike") == 0)
    {
        co2PerKilometer = 0;
        co2emission = calculateCo2(distance);
    }
    else
    {
        printf("Invalid transport type");
    }

    return co2emission;
}
