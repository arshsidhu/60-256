// INCLUDE SECTION
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

// Dummy function to hold signals
void sigHandler(int sig){};

// MAIN PROGRAM FOLLOWS

int main(int arg_c, char* arg_v[]) {
	pid_t pid1, pid2;
	char* buf1 = "EXAM! EXAM! EXAM!\n";
	char* buf2 = "HELP! HELP! HELP!\n";
	char* buf3 = "STUDY! STUDY! STUDY!\n";

	signal(SIGUSR1, sigHandler);
	signal(SIGUSR2, sigHandler);

	int f = open(arg_v[1], O_WRONLY | O_CREAT | O_TRUNC, 0755);

	if ((pid1 = fork()) > 0) {

		// Second child
		if((pid2 = fork()) == 0) {
			printf("Parent created child: %d\n", getpid());
			pause();
			printf("%d has written to the file: %s", getpid(), buf2);
			write(f, buf2, strlen(buf2));
			sleep(5);

			kill(getppid(), SIGUSR2);
		}
	}
	// First child
	else {
		printf("Parent created child: %d\n", getpid());
		printf("%d has written to the file: %s", getpid(), buf1);
		write(f, buf1, strlen(buf1));
		sleep(5);

		kill(getppid(), SIGUSR1);
	}

	pause();
	kill(pid2, SIGUSR2);

	pause();
	printf("Parent has written to the file: %s", buf3);
	write(f, buf3, strlen(buf3));
	sleep(5);

	close(f);	

	return 0;
}