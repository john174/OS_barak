#ifndef MYSHELL_H
#define MYSHELL_H




#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFF_SIZE 1024

char* getInputFromUser();
void welcome();
char** splitArgument(char*);
void getLocation();
void setTextColor(int color);
void cp(char **args);








#endif