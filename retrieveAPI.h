#ifndef GEOCODING_H
#define GEOCODING_H

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

// Structure to hold the response data
struct MemoryStruct{
    char *memory;
    size_t size;
};


// Function prototypes
int getCoordinates(int postal, char *streetName, double *lat, double *lon);
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

#endif // GEOCODING_H
