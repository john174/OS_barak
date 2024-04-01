#ifndef MYSHELL_H
#define MYSHELL_H


#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFF_SIZE 1024


char*   getInputFromUser();
void    welcome();
char**  splitArgument(char*);
void    getLocation();
void    setTextColor(int color);
void    cp(char **args);
void    logout(char *str);
void    cd(char **args);
void    rm(char *str);
void    mypipe(char **argv1, char **argv2);
void    move(char **args);
void    echoppend(char **args);
void    echorite(char **args);






#endif