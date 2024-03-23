#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>
#include "MyShell.h"
#include <ctype.h>
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#define DELIMITER ' '

#endif

char *getInputFromUser()
{
    char *buffer = malloc(BUFF_SIZE);
    if (fgets(buffer, BUFF_SIZE, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline
        return buffer;
    }
    free(buffer);
    return NULL;
}

void getLocation()
{
    char location[BUFF_SIZE];
    char hostname[HOST_NAME_MAX];
    struct passwd *pw = getpwuid(getuid());

    if (!pw || gethostname(hostname, HOST_NAME_MAX) == -1)
    {
        perror("Error getting user info or hostname");
        return;
    }

    char *cwd = realpath(".", NULL);
    if (!cwd)
    {
        perror("Error getting current directory");
        return;
    }

    setTextColor(34);
    printf("=> %s@%s:%s <=", pw->pw_name, hostname, cwd);
    setTextColor(0);

    free(cwd);
}

void cp(char **arguments)
{
    // Verify the presence of arguments
    if (arguments[1] == NULL || arguments[2] == NULL)
    {
        fprintf(stderr, "Usage: cp <source> <destination>\n");
        return;
    }

    // Open the source file and check for successful opening
    FILE *src = fopen(arguments[1], "r");
    if (src == NULL)
    {
        perror("Error opening source file");
        return;
    }

    // Open the destination file for writing and check for successful opening
    FILE *des = fopen(arguments[2], "w");
    if (des == NULL)
    {
        perror("Error opening destination file");
        fclose(src); // Close the file and release resources
        return;
    }

    // Copy data from source to destination
    int ch;
    while ((ch = fgetc(src)) != EOF)
    {
        if (fputc(ch, des) == EOF)
        {
            perror("Error writing to destination file");
            fclose(src); // Close files and release resources in case of error
            fclose(des);
            return;
        }
    }

    // Close files and release resources
    fclose(src);
    fclose(des);

    printf("File copied successfully.\n");
}

void setTextColor(int color)
{
    printf("\033[0;%dm", color);
}
void resetTextColor()
{
    printf("\033[0m");
}

void welcome()
{
    printf("                                                           ,            ||   Welcome to my shell     \n"
           "                                                        _.'|            ||     \n"
           "                                                     ,-'  /;            ||   Version 0.1 \n"
           "                                                   ,' |  /  |           ||     \n"
           "                                                  / . | /.' ;           ||     \n"
           "                        _._                       | ,  /   /            ||     \n"
           "                      ,'   `._        _           | | /_/,'             ||   https://github.com/john174  \n"
           "                     '        `._   ,' '`.        ' ,' ,'               ||     \n"
           "                    /            ,,'      `.      ;/ -'_.--.._          ||     \n"
           "                   |             |          |     /  ,' /_./.,|         ||     \n"
           "                   |       ,'-._  |         | ,'''- /_,-' |  |`:.       ||     \n"
           "         _,._    _  `.   ._;,.. `.|         |'     '|   |   _,'         ||     \n"
           "     _.-;....`.-' `--.| /:|_   `|,`._       |      /  `'''''            ||     \n"
           "  _,;-'``` | `|       '| .  `''|'|   `.    /      /                     ||   Have fun! \n"
           ",.:______,,...|      / | |   _.; |`.   `./,'    .'                      ||     \n"
           "            ,-'     |  './,-:_ |/   `.   ||    ,'                       ||     \n"
           "           /       ,|   .:...,'     ,|`. |   ,'           ._            ||     \n"
           "           `.    ,'  | /._        _,|   ||-''''-       /-`` |           ||     \n"
           "             `--'     / | `..,---' ,'    |      '.   _,''_,'|           ||     \n"
           "            / .`      |  |  `-._,,'     ,'       |  / |/-- /            ||  Like a rose with thorns, life has its prickly moments,    \n"
           "            | |'-.''-. |  `.        _.-'|      _,' | /-- ,'             ||  yet it's these that make us stronger and more beautiful   \n"
           "            ;  |..._  `'---.'--';'-      |---;'._  |/ _,'  __           ||                                                         - Vlad S Rayona   \n"
           "           /  ___   `|''-'-`    /         |    `-.:,|,;.-''  `'-.       ||     \n"
           "           '``   `'`-|         /          |    _,:|;.____ / /   |       ||     \n"
           "                      '       /           /  ,' _,'|.   |`'|--.- |      ||     \n"
           "                       `.   ,' `-._     _/  / --/ | |:.  | `. ` ` |     ||     \n"
           "                         `''       `'--'   | ,'| ' /  `---....----`     ||     \n"
           "                                           |/| ` ,'                     ||     \n"
           "                                           |,,-''                       ||     \n");
}









char** splitArgument(char* str) {
    int len = strlen(str);
    int num_tokens = 1;
    for (int i = 0; i < len; i++) {
        if (str[i] == DELIMITER) {
            num_tokens++;
        }
    }

    char** tokens = (char**)malloc(num_tokens * sizeof(char*));
    if (tokens == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int token_index = 0;
    char* token = strtok(str, " ");
    while (token != NULL) {
        tokens[token_index] = strdup(token);
        if (tokens[token_index] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        token_index++;
        token = strtok(NULL, " ");
    }

    return tokens;
}










void help()
{
    setTextColor(33); // Yellow color
    printf("Available commands:\n");
    resetTextColor();
    printf("------------------------------------------------------------------------------------------\n"
           "  cp <source> <destination>          - Copy a file from source to destination.\n"
           "------------------------------------------------------------------------------------------\n"
           "  help                               - Display this help message.\n"
           "\n");
    setTextColor(32);
    printf("Command Descriptions:\n");
    setTextColor(36);
    printf("Example: cd /path/to/directory/\n");
    resetTextColor();
    printf("------------------------------------------------------------------------------------------\n"
           "  cp <source> <./destination>         - Copy a file from the source path to the destination path.\n"
           "                                      ");
    setTextColor(36);
    printf("Example: cp file1.txt ./path/to/destination/file1.txt\n");
    resetTextColor();
}

int main()
{
    welcome();
    help();

    while (1)
    {
        getLocation();
        printf(": ");
        fflush(stdout);
        char *input = getInputFromUser();
        if (input == NULL){
            printf("Error reading input.\n");
            continue;
        }
        char **arguments = splitArgument(input);
        char *command = arguments[0];
        if (strcmp(command, "help") == 0){
            help();
        }
        else if (strcmp(command, "cp") == 0){
            cp(arguments);
        }
        else{
            printf("Command not recognized: %s\n", command);
            free(arguments);
            continue;
        }

        free(input);
        free(arguments);
    }

    return 0;
}