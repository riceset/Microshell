#include <unistd.h>
#include <stdlib.h>

int err(char *str) {
    for (int i = 0; str[i]; i++)
        write(STDERR_FILENO, str + i, 1);
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

int exec(int i, char **argv, char **envp) {
    int fd[2];
    int status;

    if (!has_pipe(i, argv) && is_cd(argv))
        return (cd(argv, i));
    if (has_pipe(i, argv) && pipe(fd) == -1)
        return (err("could not create pipe\n"));

    int pid = fork();
    if (pid == 0) {
        argv[i] = 0; // set the pipe to null
        if (has_pipe) {
            //command output -> pipe write end
            if (dup2(fd[1], STDOUT_FILENO) == -1)
                return (err("could not duplicate file descriptor\n"));

            if (close(fd[0]) == -1 || close(fd[1]) == -1)
                return (err("could not close file descriptor\n"));
        }
        if (is_cd(argv))
            return (cd(argv, i));

        execve(*argv, argv, envp);
        return (err("could not execute command\n"));
    }

    waitpid(pid, &status, 0); // wait for the child to finish
    if (has_pipe) {
        //pipe read end -> command input
        if (dup2(fd[0], STDIN_FILENO) == -1)
            return (err("could not duplicate file descriptor\n"));
        if (close(fd[0]) == -1 || close(fd[1]) == -1)
            return (err("could not close file descriptor\n"));
    }
    return (WIFEXITED(status) && WEXITSTATUS(status));
}