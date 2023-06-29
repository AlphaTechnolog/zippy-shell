#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell/eval.h"

char** split_command(char* command) {
    char** args = malloc(sizeof(char*) * 16);
    if (args == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char* arg = strtok(command, " ");
    int i = 0;
    while (arg != NULL) {
        args[i++] = arg;
        if (i == 16) {
            args = realloc(args, sizeof(char*) * 32);
            if (args == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        arg = strtok(NULL, " ");
    }
    args[i] = NULL;

    return args;
}

void eval(char *cmd) {
    char** args = split_command(cmd);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("zippy");
        exit(EXIT_FAILURE);
    } else {
        int status;
        wait(&status);
    }

    free(args);
}
