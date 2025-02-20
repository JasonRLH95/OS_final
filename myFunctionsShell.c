#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myFunctionsShell.h"





char* inputFromUser() {
    char ch;
    int len = 0;
    char *input = (char *)malloc(sizeof(char));
    input[0] = '\0';

    while ((ch = getchar()) != '\n') {
        input[len++] = ch;
        input = (char *)realloc(input, sizeof(char) * (len + 1));
    }
    input[len] = '\0';

    return input;
}
