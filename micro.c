#include "micro.h"

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
                status = exec(i, argv, envp);
        }
    }
}