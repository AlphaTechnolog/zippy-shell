#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/str.h"
#include "utils/logging.h"
#include "config/zippyrc.h"
#include "cJSON.h"

char *read_rc_file(char *filename) {
    FILE* file = fopen(filename, "r");

    // allocating memory to always free it.
    if (file == NULL) {
        char *default_config = malloc(sizeof(char) * 2024);
        sprintf(default_config, "{ \"prompt\": \"$ \" }");
        return default_config;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* file_contents = (char*) malloc(file_size + 1);
    if (file_contents == NULL) {
        fprintf(stderr, "Failed to allocate memory for file contents\n");
        fclose(file);
        exit(1);
    }

    fread(file_contents, 1, file_size, file);
    file_contents[file_size] = '\0';
    fclose(file);

    return file_contents;
}

RcFile *parse_rc_file(char *json_string) {
    RcFile *rc_file = malloc(sizeof(RcFile));
    if (rc_file == NULL)
        error("Cannot allocate memory for rc_file");

    memset(rc_file, 0, sizeof(RcFile));

    cJSON* root = cJSON_Parse(json_string);
    if (root == NULL) {
        int errlen = 0
            + strlen("Failed to parse JSON: ")
            + strlen(cJSON_GetErrorPtr())
            + 5;

        char *err = malloc(sizeof(char) * errlen);
        sprintf(err, "Failed to parse JSON: %s\n", cJSON_GetErrorPtr());

        // calling error and deallocating memory.
        error(err, 1);
    }

    // Getting prompt configuration.
    cJSON* prompt_item = cJSON_GetObjectItem(root, "prompt");

    char *default_prompt = malloc(sizeof(char) * strlen("$ ") + 1);
    sprintf(default_prompt, "$ ");

    rc_file->prompt = default_prompt;

    if (prompt_item != NULL) {
        char *duplicated_prompt = strdup(prompt_item->valuestring);
        rc_file->prompt = duplicated_prompt;
    }

    cJSON_Delete(root);

    return rc_file;
}

void free_rc_file(RcFile *rc_file) {
    free(rc_file->prompt);
    free(rc_file);
}
