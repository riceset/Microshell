#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int err(char *str)
{
    while (*str)
    {
        write(2, str, 1);
        str++;
    }
    return 1;
}

int cd(char **argv, int i)
{
    if (i != 2)
        return err("error: cd: bad arguments\n");
    if (chdir(argv[1]) == -1)
        return err("error: cd: cannot change directory to "), err(argv[1]), err("\n");
    return 0;
}

int exec(char **argv, int i, char **envp) {
    int fd[2];
    int status;
    int has_pipe = argv[i] && strcmp(argv[i], "|") == 0;

    if (!has_pipe && strcmp(argv[0], "cd") == 0)
        return (cd(argv, i));

    if (has_pipe && pipe(fd) == -1) {
        return (err("error: fatal\n"));
    }

    int pid = fork();

    if (pid == 0) {
        argv[i] = 0;

        if (has_pipe) {
            if (dup2(fd[1], STDOUT_FILENO) == -1) {
                return (err("error: fatal\n"));
            }
            if (close(fd[0]) == -1 || close(fd[1]) == -1) {
                return (err("error: fatal\n"));
            }
        }

        if (strcmp(argv[0], "cd") == 0) {
            return (cd(argv, i));
        }

        execve(argv[0], argv, envp);

        return (err("error: cannot execute"));
    }

    waitpid(pid, &status, 0);
    if (has_pipe) {
        if (dup2(fd[0], STDIN_FILENO) == -1) {
            return (err("error: fatal\n"));
        }

        if (close(fd[0]) == -1 || close(fd[1]) == -1) {
            return (err("error: fatal\n"));
        }
    }

    return (WIFEXITED(status) && WEXITSTATUS(status));
}

int main(int argc, char **argv, char **envp) {
    int status, i;

    i = status = 0;

    if (argc > 1) {
        while (argv[i] && argv[i + 1]) {
            argv += (i + 1);
            i = 0;

            while (argv[i] != NULL && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0) {
                i++;
            }

            if (i > 0) {
                status = exec(argv, i, envp);
            }
        }
    }

    return (status);
}