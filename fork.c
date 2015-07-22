#include <unistd.h>
#include <stdio.h>

int child_function(void) {
	sleep(3);

	return 0;
}

int main(int argc, char *argv[])
{
	pid_t child = fork();
	int datum = 3;
	if(child == -1) {
		perror("Could not fork");
	} else if (child) { //Parent
		printf("New process is %d\n", child);
		datum = 5;
		waitpid(child, NULL, 0);

		//printf("datum = %d\n", datum);
	} else { //Child
		child_function();
		printf("I am the child\n");
		datum = 12;
		//printf("datum = %d\n", datum);
	}
	printf("%d datum = %d (%p)\n", child, datum, &datum);
	return 0;
 }
