#include <unistd.h>
#include <stdlib.h>

//printing

void print_chr(int c) {
	write(STDERR_FILENO, &c, 1);
}

void print_err(char *str) {
	for (int i = 0; str[i]; i++) {
		print_chr(str[i]);
	}
	print_chr('\n');
}

int error(void) {
	print_err("error: fatal");
	return (1);
}

//end printing

//helpers

size_t my_strlen(const char *str) {
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t count_commands(char **cmd) {
	size_t i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

//end helpers

//built-in

int cd(char **cmd) {
	int commands_count;

	commands_count = count_commands(cmd);
	if (commands_count != 2) {
		print_err("error: cd: bad arguments");
		return (1);
	}
	if (chdir(cmd[1]) == -1) {
		print_err("error: cd: cannot change to directory");
		return (1);
	}
	return (0);

}

//end built-in

int main(void) {
	print_err("Hello");
	error();
}
