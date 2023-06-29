#ifndef CHDIR_H
#define CHDIR_H

char *expand_tilde(char *path);
char *extract_path_from_cd(char *expr);
void switch_dir(char *path);
void cd(char *expr);

#endif
