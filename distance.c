#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "distance.h"

#define PI 3.14159265359

#define EARTH_RADIUS 6371

double convDegToRad(double degree)
{
    return degree * PI / 180;
}

double haversine(double lat1, double lon1, double lat2, double lon2)
{
    if(lat1 >= 90 || lat1 <= -90 || lat2 >= 90 || lat2 <= -90 || lon1 >= 180 || lon1 <= -180 || lon2 >= 180 || lon2 <= -180)
    {
        printf("Invalid input\n");
        exit(1);
    }

    double deltaLat = convDegToRad(lat2 - lat1);
    double deltaLon = convDegToRad(lon2 - lon1);

    lat1 = convDegToRad(lat1);
    lat2 = convDegToRad(lat2);

    double a = pow(sin(deltaLat / 2), 2) + pow(sin(deltaLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));


    return EARTH_RADIUS * c; // Result in km
}