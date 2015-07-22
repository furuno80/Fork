#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/wait.h>
#include <sys/types.h>


int child_function(char *filename) {
	int in_fd = open(filename, O_RDONLY);
	int out_fd = creat("/tmp/outfile", O_WRONLY);
	uint8_t buffer[512];
	ssize_t read_in;

	if (out_fd == -1) {
		perror("Could not open output");
		return 1;
	}
	do {
		read_in = read(in_fd, buffer, 512);
		write(out_fd, buffer, read_in);
	} while (read_in);
	sleep(5);
	close(in_fd);
	close(out_fd);
	return 0;

}

int main(int argc, char *argv[]) {
	char file[80];
	printf("Please specify a file to copy to /tmp?");
	scanf("%80s", file);
	pid_t child = fork();
	if (child == -1) {
		perror("Could not fork");
	} else if (child == 0) { //Parent
		return child_function(file);
	}

	while (waitpid(child, NULL, WNOHANG) == 0) {

		printf("What is your name\n");
		char name[80];
		char color[80];
		scanf("%s", name);
		printf("What is your favorite color?\n");
		scanf("%s", color);

	}
	return 0;
}

