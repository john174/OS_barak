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
        if (buffer[0] == '\n')
        {
            free(buffer);
            return NULL;
        }
        buffer[strcspn(buffer, "\n")] = 0;
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
    // Check if source and destination file paths are provided
    if (arguments[1] == NULL || arguments[2] == NULL)
    {
        // Print usage message if arguments are missing
        fprintf(stderr, "Usage: cp <source> <destination>\n");
        return;
    }

    // Open source file for reading
    FILE *src = fopen(arguments[1], "r");
    if (src == NULL)
    {
        // Print error message if unable to open source file
        perror("Error opening source file");
        return;
    }

    // Open destination file for writing
    FILE *des = fopen(arguments[2], "w");
    if (des == NULL)
    {
        // Print error message if unable to open destination file
        perror("Error opening destination file");
        fclose(src);
        return;
    }

    int ch;
    // Copy contents from source file to destination file
    while ((ch = fgetc(src)) != EOF)
    {
        // Write character to destination file
        if (fputc(ch, des) == EOF)
        {
            // Print error message if unable to write to destination file
            perror("Error writing to destination file");
            fclose(src);
            fclose(des);
            return;
        }
    }

    // Close both files after copying
    fclose(src);
    fclose(des);

    // Print success message
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

char **splitArgument(char *str) {
    // Check if the input string is NULL or empty
    if (str == NULL || str[0] == '\0') {
        printf("Empty command.\n");
        return NULL;
    }

    int size = 1; // Initialize size to 1 to account for the NULL terminator at the end
    char **arguments = malloc(size * sizeof(char *)); // Allocate memory for the array of strings
    if (arguments == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    char *token = strtok(str, " "); // Tokenize the input string using space as the delimiter
    while (token != NULL) {
        arguments[size - 1] = token; // Assign the token to the current position in the arguments array
        size++;
        arguments = realloc(arguments, size * sizeof(char *)); // Resize the arguments array to accommodate the next token
        if (arguments == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        token = strtok(NULL, " "); // Move to the next token
    }
    arguments[size - 1] = NULL; // Set the last element of the arguments array to NULL to mark the end

    return arguments;
}



void logout(char *str)
{
    fflush(stdout);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 4 - i; j > 0; --j)
        {
            printf(" ");
        }
        for (int k = 0; k < i * 2 + 1; ++k)
        {
            printf("*");
            fflush(stdout);
            usleep(150000);
        }
        printf("\n");
    }
    for (int i = 0; i < 2; ++i)
    {
        printf("    *\n");
    }
    printf("\n");
    printf("Exit success!!!\n");
    exit(EXIT_SUCCESS);
}


void cd(char **args)
{
    char newPath[1024] = {0}; // Assume the path will not exceed 1024 characters

    // If only cd, without arguments, or argument starts with '~', go to home directory
    if (args[1] == NULL || strcmp(args[1], "~") == 0)
    {
        const char *home = getenv("HOME");
        if (home != NULL)
        {
            strcpy(newPath, home);
        }
        else
        {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    }
    else if (args[1][0] == '\"' || args[1][0] == '\'')
    { // Handling path in quotes
        // Concatenate all parts of the path into one string, remove quotes
        for (int i = 1; args[i] != NULL; ++i)
        {
            // Add spaces between parts, except the first one
            if (i > 1)
                strcat(newPath, " ");
            // Remove quotes from arguments and append to path
            strncat(newPath, args[i] + (args[i][0] == '\"' || args[i][0] == '\''), strlen(args[i]) - (args[i][0] == '\"' || args[i][0] == '\'' ? 2 : 0));
            // Check if the current argument ends with a quote
            if (args[i][strlen(args[i]) - 1] == '\"' || args[i][strlen(args[i]) - 1] == '\'')
            {
                break;
            }
        }
    }
    else
    { // Simple path without quotes
        strcpy(newPath, args[1]);
    }

    if (chdir(newPath) != 0)
    {
        perror("cd: Error changing directory");
    }
}





void help()
{
    setTextColor(33);
    printf("Available commands:\n");
    resetTextColor();

    printf("------------------------------------------------------------------------------------------\n"
           "  cp <source> <destination>          - Copy a file from source to destination.\n"
           "------------------------------------------------------------------------------------------\n"
           "  logout                             - Exit the shell.\n"
           "------------------------------------------------------------------------------------------\n"
           "  cd <directory>                     - Change the current directory.\n"
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

    printf("------------------------------------------------------------------------------------------\n"
           "  logout                             - Exit the shell.\n"
           "                                      ");
    setTextColor(36);
    printf("Example: logout\n");
    resetTextColor();

    printf("------------------------------------------------------------------------------------------\n"
           "  cd <directory>                     - Change the current directory.\n"
           "                                      ");
    setTextColor(36);
    printf("Example: cd /path/to/directory/\n");
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
        if (input == NULL)
        {
            printf("Error reading input.\n");
            continue;
        }
        char **arguments = splitArgument(input);
        char *command = arguments[0];
        if (strcmp(command, "logout") == 0)
        {
            logout(input);
            break;
        }
        else if (strcmp(command, "help") == 0)
        {
            help();
        }
        else if (strcmp(command, "cp") == 0)
        {
            cp(arguments);
        }
        else if (strcmp(command, "cd") == 0)
        {
            cd(arguments);
        }
        else
        {
            printf("Command not recognized: %s\n", command);
            free(arguments);
            continue;
        }

        free(input);
        free(arguments);
    }

    return 0;
}