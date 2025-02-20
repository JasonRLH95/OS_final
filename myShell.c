#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "myShell.h"
#include "myFunctionsShell.h"


// ---------------------------------------
// the loading bar effect on the start and at the end of the program
// ---------------------------------------
void loadingBar(int step, int totalSteps, char* header) {
    printf("\033[H\033[J");

    printf("\033[1;35m");
    printf("\n%s\n\n",header);
    printf("\033[0;32m[");

    int loaded = (step * 100) / totalSteps;
    int totalHashes = 40;

    int numHashes = (loaded * totalHashes) / 100;
    for (int i = 0; i < totalHashes; i++) {
        if (i < numHashes) {
            printf("#");
        } else {
            printf(".");
        }
    }

    printf("]\033[0m");
    printf(" %d%%\n", loaded);
}

// ---------------------------------------
// the picel art displayed on the start of the program
// ---------------------------------------
void printPixelArt() {
    // initial sketch
    char *art[] = {
        "  L       JJJJJ    RRRR    H   H ",
        "  L          J     R   R   H   H ",
        "  L          J     RRRR    HHHHH ",
        "  L      J   J     R  R    H   H ",
        "  LLLLL   JJJ      R   R   H   H ",
    };
    int rows = sizeof(art) / sizeof(art[0]);
    // the actual print of the sketch
    for (int i = 0; i < rows; i++) {
        printf("\033[1;31m%s\n", art[i]);
    }
}

// ---------------------------------------
// the initial function called when the program begin, calling the loadingBar function, the printPixelArt function and print few welcome lines
// ---------------------------------------
void welcome() {
    // the actual effect for the loading bar according to steps and sleep effect between each step
    int totalSteps = 100;
    for (int i = 1; i <= totalSteps; i++) {
        loadingBar(i, totalSteps, "Loading");
        usleep(20000);
    }
    printf("\n\n");
    // creates the pixel art
    printPixelArt();

    printf("\n\033[1;35mShell Started!\033\n");
    printf("\033[1;34mYou can type any shell command\033\n");
    printf("\033[0;33m  or\033\n");
    printf("\033[1;36mType 'exit' to quit.\033\n\n\n");
}


// ---------------------------------------
// function that stops the program
// ---------------------------------------
void logout(){
    // closing the terminal - loading bar effect
    for (int i = 1; i <= 100; i++) {
        loadingBar(i, 100, "Loging out");
        usleep(20000);
    }
    printf("\n\n\n");
}

// ---------------------------------------
// function to get the current location of the program
// ---------------------------------------
void getLocation() {
    char location[256];
    char hostname[256];
    char *username;

    username = getenv("USER");//get the value of the user environment
    if (username == NULL) {
        username = "Guest";
        // if couldn't get to that environment ||
        // the user has not been saved to the environments ||
        // something made the user to be NULL =>
        // user would be Guest 
    }

    // gethostname() => retrives the computer name
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("Error retrieving hostname");
        return;
    }
    
    // gethostname() => retrives the absolute path of the current working directory
    if (getcwd(location, sizeof(location)) == NULL) {
        perror("Error retrieving location");
        return;
    }

    // the line printed before the user inputs field
    printf("\033[1;32m");
    printf("%s@%s", username, hostname);
    printf("\033[0;30m");
    printf(":%s", location);
    printf("\033[0m$ ");


    // fflush(stdout); // force immediate display of that line
}


// ---------------------------------------
// function that get the input from the user and split it into arguments
// ---------------------------------------
char **splitInput(char *input) {
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *)); // define an initial size of the input
    char *start = input;
    bool inQuotes = false;// flag of checking if the arguments is one string to manage cases like a directory name with spaces

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (*input) {
        if (*input == '"') {
            inQuotes = !inQuotes;
            if (!inQuotes) {
                // if finished the quotes,then set that current char which holds the closing quotes, as \0 in order to declare that the string stoped
                *input = '\0';
                // move to the next token and set it as the current input index
                tokens[position++] = start;
                // move the pointer of start from input so it won't hold an unnecessary space on memory
                start = NULL;
            } else {
                // if started the quotes then catch the first char after the quotes
                start = input + 1;
            }
        } else if ((*input == ' ' || *input == '\t') && !inQuotes) {
            // if the start pointer not yet null and the current input char is a space or tab and also the quote flag is false which means we out of the quote
            // then do the same as we wrote above on lines 134-136-138
            if (start) {
                *input = '\0';
                tokens[position++] = start;
                start = NULL;
            }
        } else if (!start) {
            // if start pointer has been nulled then point him to be the input current char
            start = input;
        }

        input++;// move to the next char at input
        if (position >= bufsize) {// if position of that input is bigger then the bufsize decalre at beggining then resize the bufsize and the tokens as well
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "Reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (start) {
        //move to next token
        tokens[position++] = start;
    }

    // set the last token as NULL to declare of finish the arguments array
    tokens[position] = NULL;
    return tokens;// return the arguments array
}

// ---------------------------------------
// function that manage the commands according to the arguments
// ---------------------------------------
bool executeCommand(char *input) {
    char **args = splitInput(input);

    int count = 0;
    // => check if any of the arguments of the splited input is "exit" if so then ignoring the rest arguments and exiting program
    while(args[count] != NULL){
        if(strcmp(args[count], "exit") == 0){
            logout();
            free(args);
            return false;
        }
        count++;
    }
    // otherwise execute command
    if(args[0] == NULL){
        free(args);
        return true;
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Error executing command");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Error forking");
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }
    
    free(args);
    return true;
}


int main(int argc, char const *argv[]) {
    
    welcome();

    while(1){
        getLocation();

        char *input = inputFromUser();

        // => check if any of the arguments of the splited input is "exit" if so then ignoring the rest arguments and exiting program
        if(!executeCommand(input)){
            free(input);
            break;
        };
        free(input);
    }

    return 0;
}

