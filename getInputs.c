#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#define NAME_LENGTH 1000
#define POST_LENGTH 10

// colors with underline
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"
#define COLOR_RESET "\e[0m"

void getInput(int *postal, char *streetName, int location);
int isValidPostal(const char *postal);
int isValidStreetName(const char *name);


void getInput(int *postal, char *streetName, int location){
    char streetNameH[NAME_LENGTH];
    char postalH[POST_LENGTH];
    const char *color;

    int valid = 0;
    int bool = 1;

    // postal
    switch (location){
    case 1:
        /* home */
        color = UGRN;
        printf("We need info about the applier's %scurrent address%s.\n", color, COLOR_RESET);
        break;
    case 2:
        /* occupation */
        color = UBLU;
        printf("\nWe need info about the applier's %soccupation's address%s.\n", color, COLOR_RESET);
        break;
    case 3:
        /* housing */
        color = UMAG;
        printf("\nWe need info about the address for the %sdesired housing%s.\n", color, COLOR_RESET);
        break;
    default:
        break;
    }

    while (!valid){
        printf("Enter %spostal code%s: ", color, COLOR_RESET);

        if (fgets(postalH, sizeof(postalH), stdin)){
            postalH[strcspn(postalH, "\n")] = '\0'; // erstatte \n med \0

            if (isValidPostal(postalH)){
                valid = 1;
            }
            else{
                printf("%sInvalid input. Make sure to enter exactly four digits.%s\n", URED, COLOR_RESET);
            }
        }
        else{
            printf("%sFailed to read.\n%s", URED, COLOR_RESET);
        }
    }

    *postal = atoi(postalH); // atoi -> string to int

    // streetname

    while (bool){
        printf("Enter %sroad name%s (remember to capitalize letters): ", color, COLOR_RESET);
        if (fgets(streetNameH, sizeof(streetNameH), stdin)){
            streetNameH[strcspn(streetNameH, "\n")] = '\0';

            if (isValidStreetName(streetNameH)){
                bool = 0;
            }
            else{
                printf("%sInvalid input. Enter again.%s\n", URED, COLOR_RESET);
            }
        }
        else{
            printf("%sFailed to read.%s\n", URED, COLOR_RESET);
        }
    }
    strcpy(streetName, streetNameH);
}

int isValidPostal(const char *postal){
    if (postal == NULL || strlen(postal) != 4){ // tjekker om der er indhold i strengen og om længden af strengen svarer til 4
        return 0;
    }

    for (int i = 0; i < 4; i++){
        if (!isdigit(postal[i]))
        { // tjekker om hvert enekelte karakter er et tal
            return 0;
        }
    }
    return 1;
}

int isValidStreetName(const char *name){
    int containsLetter = 0;

    if (name == NULL || strlen(name) == 0){
        return 0; // Empty input
    }

    // Convert to wide-character string
    wchar_t wname[NAME_LENGTH];
    mbstowcs(wname, name, NAME_LENGTH);

    for (int i = 0; wname[i] != L'\0'; i++) {
        if (iswalpha(wname[i])) {
            containsLetter = 1; // Found a letter
        } else if (wname[i] != L'.' && wname[i] != L' ') {
            return 0; // Contains invalid characters
        }
    }
    return containsLetter; // Valid if at least one letter is found
}