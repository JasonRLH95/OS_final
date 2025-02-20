#include <stdio.h>
#include <unistd.h>

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

void printPixelArt() {
    char *art[] = {
        "  L       JJJJJ    RRRR    H   H ",
        "  L          J     R   R   H   H ",
        "  L          J     RRRR    HHHHH ",
        "  L      J   J     R  R    H   H ",
        "  LLLLL   JJJ      R   R   H   H ",
    };

    int rows = sizeof(art) / sizeof(art[0]);
    for (int i = 0; i < rows; i++) {
        printf("\033[1;31m%s\n", art[i]);
    }
}

void welcome() {
    int totalSteps = 100;

    for (int i = 1; i <= totalSteps; i++) {
        loadingBar(i, totalSteps, "Loading");
        usleep(20000);
    }
    printf("\n\n");
    printPixelArt();

    printf("\n\033[1;35mShell Started!\033\n");
    printf("\033[1;34mYou can type any shell command\033\n");
    printf("\033[0;33m  or\033\n");
    printf("\033[1;36mType 'exit' to quit.\033\n\n\n");
}



int main(int argc, char const *argv[]) {
    
    welcome();


    return 0;
}