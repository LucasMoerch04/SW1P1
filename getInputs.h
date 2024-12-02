#ifndef GET_INPUTS_H
#define GET_INPUTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constants
#define NAME_LENGTH 1000
#define POST_LENGTH 10

// Colors with underline
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"
#define COLOR_RESET "\e[0m"

// Function prototypes
void getInputHome(int *postal, char *streetName);
void getInputOccupation(int *postal, char *streetName);
void getInputHousing(int *postal, char *streetName);
int isValidPostal(const char *postal);
int isValidStreetName(const char *name);

#endif
