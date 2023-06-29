#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paths/config.h"
#include "utils/logging.h"

char *get_config_path(void) {
    #ifndef CONFIG_PATH_BASE
        error("hmm, cannot find config path base defined somewhere :'/");
    #endif

    char *home_path = getenv("HOME");
    if (home_path == NULL)
        error("Cannot get the HOME path");

    int path_size = (strlen(home_path) + (strlen(CONFIG_PATH_BASE) - 2)) + 1;
    char *path = malloc(sizeof(char) * path_size);
    if (!path)
        error("Cannot allocate mem.");

    sprintf(path, CONFIG_PATH_BASE, home_path);

    return path;
}
