#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>  // Include cJSON for JSON parsing
#define _GNU_SOURCE


// Structure to hold the response data
struct MemoryStruct{
    char *memory;
    size_t size;
};



static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);


int getCoordinates(int postal, char *streetName, double *lat, double *lon){
    CURL *handle;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  // Initial allocation
    chunk.size = 0;

    char url[100];

    sprintf(url, "https://api.dataforsyningen.dk/adresser?postnr=%d&vejnavn=%s&format=geojson", postal, streetName);
    
    handle = curl_easy_init();

    if (handle){
        // Set the URL for the API request
        curl_easy_setopt(handle, CURLOPT_URL, url);
        

        // Set up the callback function to handle data
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&chunk);

        // Perform the request
        if (curl_easy_perform(handle) == CURLE_OK) {
            // Parse the JSON response
            cJSON *json = cJSON_Parse(chunk.memory);
            cJSON *features = cJSON_GetObjectItemCaseSensitive(json, "features");
            if (cJSON_IsArray(features) && cJSON_GetArraySize(features) > 0) {
                cJSON *firstFeature = cJSON_GetArrayItem(features, 0);
                cJSON *geometry = cJSON_GetObjectItemCaseSensitive(firstFeature, "geometry");
                cJSON *coordinates = cJSON_GetObjectItemCaseSensitive(geometry, "coordinates");

                // Retrieve longitude and latitude
                cJSON *longitude = cJSON_GetArrayItem(coordinates, 0);
                cJSON *latitude = cJSON_GetArrayItem(coordinates, 1);

                // Set global lat and lon
                *lat = latitude->valuedouble;
                *lon = longitude->valuedouble;
            } else {
                printf("Address not found. Try again\n\n");
                return 0;
            }
            // Cleanup
            cJSON_Delete(json);
        }

        curl_easy_cleanup(handle);
        free(chunk.memory);  // Free the memory allocated for the response

        return 1;
    }
    return 0;
}


// Callback function for handling the response data
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + totalSize + 1);
    memcpy(&(mem->memory[mem->size]), contents, totalSize);
    mem->size += totalSize;
    mem->memory[mem->size] = 0;

    return totalSize;
}

