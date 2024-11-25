#include <stdio.h>
#include "retrieveAPI.h"
#include "applicantStruct.h"
#include "distance.h"

int main(void){


    get_coordinates(2650, "Bymuren");
    default_list();

    printf("hello, world\n");

    printf("%lf\n", lat);
    printf("%lf\n", lon);

    
    return 0;
}