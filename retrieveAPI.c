#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>  // Include cJSON for JSON parsing

// Structure to hold the response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

double lat = 0.0;
double lon = 0.0;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

void get_coordinates(void) {
    CURL *handle;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  // Initial allocation
    chunk.size = 0;

    handle = curl_easy_init();
    if (handle) {
        // Set the URL for the API request
        curl_easy_setopt(handle, CURLOPT_URL, "https://geocoding-api.open-meteo.com/v1/search?name=2650&count=1&language=en&format=json");

        // Set up the callback function to handle data
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&chunk);

        // Perform the request
        curl_easy_perform(handle);

        // Parse the JSON response
        cJSON *json = cJSON_Parse(chunk.memory);

        // Extract latitude and longitude from the JSON
        cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
        cJSON *first_result = cJSON_GetArrayItem(results, 0);
        cJSON *latitude = cJSON_GetObjectItemCaseSensitive(first_result, "latitude");
        cJSON *longitude = cJSON_GetObjectItemCaseSensitive(first_result, "longitude");


    
        lat = latitude->valuedouble;
        lon = longitude->valuedouble;


        // Cleanup
        cJSON_Delete(json);
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

