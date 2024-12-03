#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LENGTH 1000
#define POST_LENGTH 10

//colors with underline
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"
#define COLOR_RESET "\e[0m"

void getInputHome(int *postal, char *streetName);
void getInputOccupation(int *postal, char *streetName);
void getInputHousing(int *postal, char *streetName);
int isValidPostal(const char *postal);
int isValidStreetName(const char *name);


void getInputHome(int *postal, char *streetName){
    char streetNameH[NAME_LENGTH];
    char postalH[POST_LENGTH];

    int valid = 0;
    int bool = 1;

//postal
    
    printf("We need info about the applier's %scurrent address%s.\n", UGRN, COLOR_RESET);

    while (!valid){ 
        printf("Enter the %spostal code%s for the applier's address: ", UGRN, COLOR_RESET);

        if (fgets(postalH, sizeof(postalH), stdin)){
            postalH[strcspn(postalH, "\n")] = '\0'; //erstatte \n med \0

            if (isValidPostal(postalH)){
                valid = 1;
            }else{
                printf("%sInvalid input. Make sure to enter exactly four digits.%s\n", URED, COLOR_RESET);
            }
        }else{
            printf("%sFailed to read.\n%s",URED, COLOR_RESET);
        }
    }

    *postal = atoi(postalH); //atoi -> string to int

//streetname

    while (bool){
        printf("Enter %sroad name%s for the applier's address: ", UGRN, COLOR_RESET);
        if (fgets(streetNameH, sizeof(streetNameH), stdin)){
                streetNameH[strcspn(streetNameH, "\n")] = '\0';

            if (isValidStreetName(streetNameH)){
                bool = 0;
            }else{
                printf("%sInvalid input. Enter again.%s\n", URED, COLOR_RESET);
            }
        }else{
            printf("%sFailed to read.%s\n", URED, COLOR_RESET);
        }
    }
    strcpy(streetName, streetNameH);
}

void getInputOccupation(int *postal, char *streetName){
    char streetNameO[NAME_LENGTH];
    char postalO[POST_LENGTH];

    int valid = 0;
    int bool = 1;

//postal
    
    printf("\nWe need info about the applier's %soccupation's address%s.\n", UBLU, COLOR_RESET);

    while (!valid){ 
        printf("Enter %spostal code%s for the applier's occupation's address: ", UBLU, COLOR_RESET);

        if (fgets(postalO, sizeof(postalO), stdin)){
            postalO[strcspn(postalO, "\n")] = '\0'; //erstatte \n med \0

            if (isValidPostal(postalO)){
                valid = 1;
            }else{
                printf("%sInvalid input. Make sure to enter exactly four digits.%s\n", URED, COLOR_RESET);
            }
        }else{
            printf("%sFailed to read.%s\n", URED, COLOR_RESET);
        }
    }

    *postal = atoi(postalO); //atoi -> string to int

//streetname

    while (bool){
        printf("Enter %sroad name%s for the applier's occupation's address: ", UBLU, COLOR_RESET);
        if (fgets(streetNameO, sizeof(streetNameO), stdin)){
                streetNameO[strcspn(streetNameO, "\n")] = '\0';

            if (isValidStreetName(streetNameO)){
                bool = 0;
            }else{
                printf("%sInvalid input. Enter again.%s\n", URED, COLOR_RESET);
            }
        }else{
            printf("%sFailed to read.%s\n", URED, COLOR_RESET);
        }
    }
    strcpy(streetName, streetNameO);
}

void getInputHousing(int *postal, char *streetName){
    char streetNameH[NAME_LENGTH];
    char postalH[POST_LENGTH];

    int valid = 0;
    int bool = 1;

//postal
    
    printf("\nWe need info about the address for the %savailable housing%s.\n", UMAG, COLOR_RESET);

    while (!valid){ 
        printf("Enter %spostal code%s for the desired housing: ", UMAG, COLOR_RESET);

        if (fgets(postalH, sizeof(postalH), stdin)){
            postalH[strcspn(postalH, "\n")] = '\0'; //erstatte \n med \0

            if (isValidPostal(postalH)){
                valid = 1;
            }else{
                printf("%sInvalid input. Make sure to enter exactly four digits.%s\n", URED, COLOR_RESET);
            }
        }else{
            printf("%sFailed to read.%s\n", URED, COLOR_RESET);
        }
    }

    *postal = atoi(postalH); //atoi -> string to int

//streetname

    while (bool){
        printf("Enter %sroad name%s for the desired housing: ", UMAG, COLOR_RESET);
        if (fgets(streetNameH, sizeof(streetNameH), stdin)){
                streetNameH[strcspn(streetNameH, "\n")] = '\0';

            if (isValidStreetName(streetNameH)){
                bool = 0;
            }else{
                printf("%sInvalid input. Enter again.%s\n", URED, COLOR_RESET);
            }
        }else{
            printf("%sFailed to read.%s\n", URED, COLOR_RESET);
        }
    }
    strcpy(streetName, streetNameH);
}

int isValidPostal(const char *postal){
    if (postal == NULL || strlen(postal) != 4){ //tjekker om der er indhold i strengen og om længden af strengen svarer til 4
        return 0;
    }

    for (int i = 0; i < 4; i++){
        if (!isdigit(postal[i])){ //tjekker om hvert enekelte karakter er et tal
            return 0; 
        }
    }
    return 1;
}

int isValidStreetName(const char *name){
    int containsLetter = 0;

    if (name == NULL || strlen(name) == 0) {
        return 0; // Tomt input
    }

    for (int i = 0; name[i] != '\0'; i++) {
        if (isalpha(name[i])) {
            containsLetter = 1; // Fundet et bogstav
        } else if (name[i] != '.' && name[i] != ' ') {
            return 0; // Indeholder ugyldige tegn
        }
    }
    return containsLetter; // Gyldigt hvis mindst ét bogstav er fundet

}