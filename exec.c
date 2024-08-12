#include "micro.h"

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
        if (has_pipe(i, argv)) {
            //command output -> pipe write end
            if (dup2(fd[1], STDOUT_FILENO) == -1)
                return (err("could not duplicate file descriptor\n"));

            if (close(fd[0]) == -1)
                return (err("could not close file descriptor\n"));
            if (close(fd[1]) == -1)
                return (err("could not close file descriptor\n"));
        }
        if (is_cd(argv))
            return (cd(argv, i));

        execve(*argv, argv, envp);
        return (err("could not execute command\n"));
    } else if (pid > 0) {
        if (has_pipe(i, argv)) {
            //pipe read end -> command input
            if (close(fd[1]) == -1)
                return (err("could not close file descriptor\n"));
            if (dup2(fd[0], STDIN_FILENO) == -1)
                return (err("could not duplicate file descriptor\n"));
            if (close(fd[0]) == -1)
                return (err("could not close file descriptor\n"));
        }
        waitpid(pid, &status, 0); // wait for the child to finish
    } else {
        return err("fork failed\n");
    }

    return (WIFEXITED(status) && WEXITSTATUS(status));
}