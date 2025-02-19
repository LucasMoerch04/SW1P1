#ifndef GET_INPUTS_H
#define GET_INPUTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>


// Constants
#define NAME_LENGTH 1000
#define POST_LENGTH 10

#define COLOR_BOLD  "\e[1m"
#define COLOR_RESET "\e[0m"

// colors with underline
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

// colors without underline
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define BLU "\e[0;34m"
#define CYN "\e[0;36m"
#define YEL "\e[0;33m"



// Function prototypes
void getInput(int *postal, char *streetName, int location);


#endif
