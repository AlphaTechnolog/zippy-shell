#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *expand_tilde(char *path) {
    char *home = getenv("HOME");
    if (home == NULL) {
        perror("getenv");
        exit(EXIT_FAILURE);
    }

    char *result = malloc(strlen(path) + strlen(home));
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *p = path;
    char *r = result;
    while (*p) {
        if (*p == '~') {
            strcpy(r, home);
            r += strlen(home);
        } else {
            *r++ = *p;
        }
        p++;
    }
    *r = '\0';

    return result;
}

char *extract_path_from_cd(char *expr) {
    char *token = strtok(expr, " ");
    token = strtok(NULL, " ");

    char *dir_path = expand_tilde(token);

    return dir_path;
}

void switch_dir(char *path) {
    if (chdir(path) == -1) {
        perror("cd");
    }
}

void cd(char *expr) {
    if (expr == NULL) {
        char *home = getenv("HOME");
        if (home == NULL) {
            perror("getenv");
            exit(EXIT_FAILURE);
        }

        switch_dir(home);
        return;
    }

    char *dir_path = extract_path_from_cd(expr);
    switch_dir(dir_path);
    free(dir_path);
}
