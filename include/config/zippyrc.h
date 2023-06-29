#ifndef CONFIG_ZIPPYRC_H
#define CONFIG_ZIPPYRC_H

typedef struct RcFile {
    char *prompt;
} RcFile;

char *read_rc_file(char *filename);
RcFile *parse_rc_file(char *json_string);
void free_rc_file(RcFile *rc_file);

#endif
