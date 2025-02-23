#include <stdbool.h>

char *inputFromUser();
void loadingBar(int a, int b, char* head);
void printPixelArt();
void welcome();
void logout();
void getLocation();
void cd(char **args);
void copyFile(char *src,char *dest);
void copyDirectory(char *src,char *dest);
void cp(char **args);
void recursiveDelete(char *path);
void delete(char **args);
char **splitInput(char *input);
bool executeCommand(char *input);

