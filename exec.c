#include <unistd.h>
#include <stdlib.h>

int has_pipe(int i, char **argv) {
    return (argv[i] && strcmp(argv[i], "|") == 0);
}

int is_cd(char **argv) {
    return (strcmp(*argv, "cd") == 0);
}

int exec(int i, char **argv, char **envp) {
    int fd[2];

    if (!has_pipe(i, argv) && is_cd(argv))
        return (cd(argv, i));
    if (has_pipe(i, argv) && pipe(fd) == -1)
        return (err("could not create pipe\n"));

    int pid = fork();
    if (pid == 0) {
        argv[i] = 0; // set the pipe to null
    }
}