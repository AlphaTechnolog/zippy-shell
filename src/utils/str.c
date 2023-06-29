#include <string.h>
#include <stdlib.h>

#include "utils/str.h"

char *strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* p = malloc(len);
    if (p == NULL)
        return NULL;

    strcpy(p, s);
    return p;
}

int startswith(const char *str, const char *prefix) {
    size_t prefix_len = strlen(prefix);
    if (strlen(str) < prefix_len) {
        return 0;
    }

    return strncmp(str, prefix, prefix_len) == 0;
}
