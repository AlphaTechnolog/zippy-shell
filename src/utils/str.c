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
