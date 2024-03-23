#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>

#define BUFF_SIZE 256

char* getInputFromUser();
char** splitArgument(char*);
void getLocation();

void setTextColor(int color) {
    printf("\033[0;%dm", color);
}

char* getInputFromUser() {
    // Реализация функции
    return NULL;
}

char** splitArgument(char *str) {
    // Реализация функции
    return NULL;
}

void getLocation() {
    char location[BUFF_SIZE];
    char hostname[HOST_NAME_MAX];
    struct passwd *pw = getpwuid(getuid());

    if (!pw || gethostname(hostname, HOST_NAME_MAX) == -1) {
        perror("Error getting user info or hostname");
        return;
    }

    char* cwd = realpath(".", NULL);

    if (!cwd) {
        perror("Error getting current directory");
        return;
    }

    setTextColor(34);
    printf("=> %s@%s:%s <=\n", pw->pw_name, hostname, cwd);
    setTextColor(0);

    free(cwd);
}

int main() {
    getLocation();
    return 0;
}
