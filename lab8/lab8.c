#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// MAIN PROGRAM FOLLOWS
int main(int argc, char *argv[]){
	int fd[2], pid;

	pipe(fd);

	if((pid = fork()) == 0) {
		close(fd[0]);

		dup2(fd[1],	STDOUT_FILENO);				// Sets child's standard output descript to its write descriptor
		execlp(argv[1], argv[1], (char *)0);	// Command gets executed, piped to parent
		close(fd[1]);
	}
	else {
		sleep(1);
		int len;
		char output[1000];
		memset(output, 0, sizeof(output));

		close(fd[1]);
		len = read(fd[0], output, sizeof(output));
		int fout = open("result.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
		write(fout, output, strlen(output));

		printf("The result of %s is written into result.txt with total %d bytes\n", argv[1], len);

		close(fd[0]);
		close(fout);
	}
	
	return 0;
}