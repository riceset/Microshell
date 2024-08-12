#include "micro.h"

int err(char *str) {
    for (int i = 0; str[i]; i++)
        write(STDERR_FILENO, str + i, 1);
    return (1);
}

int cd(char **argv, int i) {
    if (i != 2)
        return (err("cd: bad arguments\n"));
    if (chdir(argv[1]) == -1)
        return (err("cd: cannot change directory to "), err(argv[1]), err("\n"));
    return (0);
}

int has_pipe(int i, char **argv) {
    return (argv[i] && strcmp(argv[i], "|") == 0);
}

int is_cd(char **argv) {
    return (strcmp(*argv, "cd") == 0);
}