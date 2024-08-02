#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *new_dir = "/";

	if (chdir(new_dir) != 0)
		return (1);

	printf("Switched to %s\n", new_dir);
	system("ls");

	return (0);
}
