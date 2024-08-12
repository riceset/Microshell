#include <string.h>
#include <stdlib.h>

int exec(int i, char **argv, char **envp);

int has_more_arguments(char **argv, int i) {
    return (argv[i] && argv[i + 1]);
}

int is_valid_argument(char *arg) {
    if (arg == NULL) {
        return (0);
    } else if (strcmp(arg, "|") == 0) {
        return (0);
    } else if (strcmp(arg, ";") == 0) {
        return (0);
    }
    return (1);
}

int has_valid_arguments(int i) {
    return (i > 0);
}

int main(int argc, char **argv, char **envp) {
    int i = 0;
    int status = 0;

    if (argc > 1) {
        while (has_more_arguments(argv, i)) {
            argv += (i + 1);
            i = 0;
            while (is_valid_argument(argv[i]))
                i++;
            if (has_valid_arguments(i))
                status = exec(argv, i, envp);
        }
    }
}