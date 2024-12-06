#ifndef GEOCODING_H
#define GEOCODING_H

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>


// Function prototypes
int getCoordinates(int postal, char *streetName, double *lat, double *lon);
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

#endif // GEOCODING_H
