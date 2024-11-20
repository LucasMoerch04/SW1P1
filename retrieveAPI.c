#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>  // Include cJSON for JSON parsing
#define _GNU_SOURCE


// Structure to hold the response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

double lat = 0.0;
double lon = 0.0;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

void get_coordinates(int postal, char *street_name) {
    CURL *handle;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  // Initial allocation
    chunk.size = 0;

    char *url = NULL;

    asprintf(&url, "https://api.dataforsyningen.dk/adresser?postnr=%d&vejnavn=%s&format=geojson", postal, street_name);
    
    handle = curl_easy_init();

    if (handle) {
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
            cJSON *first_feature = cJSON_GetArrayItem(features, 0);
            cJSON *geometry = cJSON_GetObjectItemCaseSensitive(first_feature, "geometry");
            cJSON *coordinates = cJSON_GetObjectItemCaseSensitive(geometry, "coordinates");

            // Retrieve longitude and latitude
            cJSON *longitude = cJSON_GetArrayItem(coordinates, 0);
            cJSON *latitude = cJSON_GetArrayItem(coordinates, 1);

            // Set global lat and lon
            lat = latitude->valuedouble;
            lon = longitude->valuedouble;

            // Cleanup
            cJSON_Delete(json);
        }

        curl_easy_cleanup(handle);
        free(chunk.memory);  // Free the memory allocated for the response
    }
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

