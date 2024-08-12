#include "micro.h"

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