#include <stdio.h>
#include "retrieveAPI.h"

int main(void){
    get_coordinates();

    printf("hello, world\n");

    printf("%lf\n", lat);
    printf("%lf\n", lon);
    return 0;
}