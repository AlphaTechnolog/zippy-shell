#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "paths/config.h"
#include "config/zippyrc.h"
#include "utils/str.h"
#include "shell/chdir.h"
#include "shell/eval.h"
#include "shell/listener.h"

void cleaning(char *config_path, char *config_content, RcFile *rc_file) {
    free(config_path);
    free(config_content);
    free_rc_file(rc_file);
}

void render_prompt(RcFile *rc_file) {
    struct termios term, term_orig;
    tcgetattr(STDIN_FILENO, &term);
    term_orig = term;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    char *input = NULL;
    size_t input_size = 0;

    while (1) {
        printf("%s", rc_file->prompt);
        fflush(stdout);

        size_t input_len = 0;

        while (1) {
            char c;
            if (read(STDIN_FILENO, &c, 1) < 0) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            if (c == '\n') {
                break;
            } else if (c == '\x0c') {
                // CTRL+L
                system("clear");
                printf("%s", rc_file->prompt);
                fflush(stdout);
                input_len = 0;
            } else if (c == 127 || c == '\b') {
                // Backspace
                if (input_len > 0) {
                    input_len--;
                    printf("\b \b");
                    fflush(stdout);
                }
            } else if (c == '\x15') {
                while (input_len > 0) {
                    input_len--;
                    printf("\b \b");
                    fflush(stdout);
                }
            } else {
                if (input_len == input_size) {
                    input_size += 1024;
                    input = realloc(input, input_size);
                    if (input == NULL) {
                        perror("realloc");
                        exit(EXIT_FAILURE);
                    }
                }

                input[input_len++] = c;
                printf("%c", c);
                fflush(stdout);
            }
        }

        if (input_len == 0)
            continue;

        input = realloc(input, input_len + 1);
        if (input == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }

        input[input_len] = '\0';
        if (strcmp(input, "exit") == 0) {
            printf("\n");
            break;
        }

        if (strcmp(input, "clear") == 0) {
            system("clear");
            continue;
        }

        if (startswith(input, "cd")) {
            printf("\n");

            cd(
                strlen(input) > 2 && startswith(input, "cd ")
                    ? input
                    : NULL
            );

            continue;
        }

        printf("\n");
        eval(input);
        fflush(stdout);
    }

    free(input);

    tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
}

void start_listening(void) {
    char *config_path = get_config_path();
    char *config_content = read_rc_file(config_path);
    RcFile *rc_file = parse_rc_file(config_content);
    render_prompt(rc_file);
    cleaning(config_path, config_content, rc_file);
}
