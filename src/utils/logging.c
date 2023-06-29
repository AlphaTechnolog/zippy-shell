#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void error(char *message, ...) {
    fprintf(stderr, "[Fatal]: %s\n", message);

    va_list args;
    va_start(args, message);

    int free_after_use = va_arg(args, int);

    if (free_after_use)
        free(message);

    va_end(args);

    exit(1);
}
