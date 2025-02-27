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
void mypipe(char **argv1, char **argv2);
void move(char **args);
void echoppend(char **args);
void echowrite(char **args);
void _read(char **args);
void wordCount(char **args);
char **splitInput(char *input);
void splitByPipe(char **args);
void echoSplit(char **args);
bool executeCommand(char *input);

