#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LENGTH 50

//to implement color
#define Green "\e[0;32m"
#define White "\e[0;37m"
#define Cyan "\e[0;36m"
#define BoldPurple "\e[1;35m"

int getInputs(void);
int isValidPostal(const char *postal);
int isValidStreetName(const char *name);
void clearBuffer(void);


int getInputs(void){
    char *streetName[NAME_LENGTH];
    char buffer[NAME_LENGTH];
    char postalH[10];
    char postalO[10];
    int post[2];

//current housing
    int valid = 0;
    int Bool = 1;

    while (!valid){ 
        printf("%sTo apply for hoursing we must know your current address. \nFirst, enter%s postal code%s, and then%s road name%s.\n", Green, BoldPurple, Green, BoldPurple, Green);
        printf("%sEnter postal code for current address: ", White);

        if (fgets(postalH, sizeof(postalH), stdin)){
            postalH[strcspn(postalH, "\n")] = '\0';
            clearBuffer();

            if (isValidPostal(postalH)){
                valid = 1;
            } else{
                printf("Invalid input. Make sure to enter exactly four digits.\n");
            }
        } else{
            printf("Failed to read.\n");
            clearBuffer();
        }
    }

    post[0] = atoi(postalH); // atoi -> string to int

    printf("Enter road name for current address: ");
    scanf(" %[^\n]", buffer);
    clearBuffer();

    while (Bool){
        for (int i = 0; i <= NAME_LENGTH; i++){
            if (buffer[i] == EOF){
                i = NAME_LENGTH;
            }
            if (isdigit(buffer[i])){
                i = 0;
                printf("Invalid input. Enter again.\n");
                printf("Enter road name for current address: "); 
                scanf(" %[^\n]", buffer);
            } else{
                Bool = 0;
            }
        }
    }

    streetName[0] = malloc(strlen(buffer) + 1); // +1 for \0
    if (streetName[0] == NULL){
        printf("Error: Unable to allocate memory!\n");
        return 1;
    }

    strcpy(streetName[0], buffer);
    printf("%d, %s\n\n", post[0], streetName[0]);


//occupation
    valid = 0;
    Bool = 1;

    while (!valid){ 
        printf("%sTo apply for hoursing we must know your occupation's address. \nFirst, enter%s postal code%s, and then%s road name%s.\n", Green, BoldPurple, Green, BoldPurple, Green);
        printf("%sEnter postal code for occupation's address: ", White);

        if (fgets(postalO, sizeof(postalO), stdin)){
            postalO[strcspn(postalO, "\n")] = '\0';

            if (isValidPostal(postalO)){
                valid = 1;
            }else{
                printf("Invalid input. Make sure to enter exactly four digits.\n");
            }
        }else{
            printf("Failed to read.\n");
        }
    }

    post[1] = atoi(postalO); // atoi -> string to int

    printf("Enter road name for occupation's address: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Fjern '\n'
        if (strlen(buffer) == 0) {
            printf("Road name cannot be empty. Please try again.\n");
        } else if (!isValidStreetName(buffer)) {
            printf("Invalid input. Road name must contain letters.\n");
        } else {
            valid = 1; // Input er gyldigt
        }
    } else {
        printf("Failed to read input. Please try again.\n");
        clearBuffer(); // Ryd buffer
    }

    streetName[1] = malloc(strlen(buffer) + 1); // +1 for \0
    if (streetName[1] == NULL){
        printf("Error: Unable to allocate memory!\n");
        return 1;
    }

    strcpy(streetName[1], buffer);

    printf("housing: %d, %s\noccupation: %d, %s", post[0], streetName[0], post[1], streetName[1]);
}

int isValidPostal(const char *postal){
    if (postal == NULL || strlen(postal) == 0 || strlen(postal) != 4){
        return 0;
    }

    for (int i = 0; i < 4; i++){
        if (!isdigit(postal[i])){
            return 0; 
        }
    }
    return 1;
}

int isValidStreetName(const char *name) {
    if (name == NULL || strlen(name) == 0) {
        return 0; // Tomt input
    }
    for (int i = 0; name[i] != '\0'; i++) {
        if (isalpha(name[i])) {
            return 1; // Indeholder bogstaver
        }
    }
    return 0; // Ingen bogstaver
}

void clearBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Tømmer bufferen
}
