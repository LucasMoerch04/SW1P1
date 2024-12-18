#include <stdio.h>
#include <curl/curl.h>  // Include curl fetching data from API
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>  // Include cJSON for JSON parsing
#define _GNU_SOURCE


// Structure to hold the response data
struct MemoryStruct{
    char *memory; // Pointer to the response data
    size_t size; // Size of the response data
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);


// Function to get geographic coordinates for a given postal number and street name
int getCoordinates(int postal, char *streetName, double *lat, double *lon) {
    CURL *handle;   // CURL handle for making API requests
    struct MemoryStruct chunk;  // Structure to hold the API response data

    // Initialize response data structure
    chunk.memory = malloc(1);   // Allocate initial memory for the response
    chunk.size = 0; // Initialize size to 0

    char url[100];  // Buffer to store the API URL

    // Initialize CURL handle
    handle = curl_easy_init();

    if (handle) {
        // Encode the street name to handle special characters (e.g. æ, ø, å)
        char *encodedStreetName = curl_easy_escape(handle, streetName, 0);

        if (encodedStreetName) {
            // Construct the API URL with postal number and encoded street name
            sprintf(url, "https://api.dataforsyningen.dk/adresser?postnr=%d&vejnavn=%s&format=geojson", postal, encodedStreetName);
            
            // Free the encoded string to avoid memory leaks
            curl_free(encodedStreetName);
        }

        // Set the URL for the API request
        curl_easy_setopt(handle, CURLOPT_URL, url);

        // Set the callback function to process the API response
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        // Pass the response data structure to the callback function
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&chunk);

        // Execute the API request
        if (curl_easy_perform(handle) == CURLE_OK) {
            // Parse the JSON response
            cJSON *json = cJSON_Parse(chunk.memory);
            cJSON *features = cJSON_GetObjectItemCaseSensitive(json, "features");

            // Check if the JSON contains an array of features
            if (cJSON_IsArray(features) && cJSON_GetArraySize(features) > 0) {
                // Extract the first feature from the array
                cJSON *firstFeature = cJSON_GetArrayItem(features, 0);
                cJSON *geometry = cJSON_GetObjectItemCaseSensitive(firstFeature, "geometry");
                cJSON *coordinates = cJSON_GetObjectItemCaseSensitive(geometry, "coordinates");

                // Retrieve longitude and latitude from the coordinates array
                cJSON *longitude = cJSON_GetArrayItem(coordinates, 0);
                cJSON *latitude = cJSON_GetArrayItem(coordinates, 1);

                // Store the coordinates in the provided pointers
                *lat = latitude->valuedouble;
                *lon = longitude->valuedouble;
            } else {
                // Handle cases where no address is found
                printf("Address not found. Try again\n\n");
                free(chunk.memory); // Free the memory allocated for the response
                return 0;   // Return failure
            }

            // Clean up the JSON object
            cJSON_Delete(json);
        }

        // Clean up the CURL handle
        curl_easy_cleanup(handle);

        // Free the memory allocated for the API response
        free(chunk.memory);

        return 1;  // Return success
    }

    // Free the memory allocated for the API response in case of failure
    free(chunk.memory);
    return 0;  // Return failure
}


// Callback function for handling the response data
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;    // Calculate the total size of the incoming data chunk

    // Cast the user-defined pointer to the MemoryStruct type
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    // Reallocate memory for the new data chunk + 1 for null-terminator
    mem->memory = realloc(mem->memory, mem->size + totalSize + 1);

    // Copy the new data chunk into the allocated memory buffer
    memcpy(&(mem->memory[mem->size]), contents, totalSize);

    mem->size += totalSize;    // Update size of the buffer
    mem->memory[mem->size] = 0;    // Null-terminate the memory buffer

    return totalSize;    // Return the size of the processed data to libcurl
}

