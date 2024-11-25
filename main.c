#include <stdio.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"
#include "co2.h"

int main(void){


    get_coordinates(2650, "Bymuren");
    default_list();
    printf("CO2: %lf\n", CalculateEmissions(200, "Car"));

    printf("hello, world\n");

    printf("%lf\n", lat);
    printf("%lf\n", lon);

    
    return 0;
}