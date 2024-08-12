#ifndef MICRO_H
#define MICRO_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int has_more_arguments(char **argv, int i);
int is_valid_argument(char *arg);
int has_valid_arguments(int i);

int exec(int i, char **argv, char **envp);
int err(char *str);
int cd(char **argv, int i);
int has_pipe(int i, char **argv);
int is_cd(char **argv);

#endif