#include <unistd.h>
#include <string.h>
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

int handle_cd(char **cmd) {
	if (strcmp(cmd[0], "cd") == 0)
		return cd(cmd);
	return (-1);
}

void execute_piped_commands(char **cmd, char **env) {
	int fd[2];
	int i, j, last;
	int read_from, write_to, backup_in, backup_out;

	read_from = dup(STDIN_FILENO);
	backup_in = dup(STDIN_FILENO);
	backup_out = dup(STDOUT_FILENO);

	if (read_from == -1 || backup_in == -1 || backup_out == -1)
		error();
}

int main(void) {
	print_err("Hello");
	error();
}
