// INCLUDE SECTION
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdio.h>

// MAIN PROGRAM FOLLOWS

int main(int argc, char* argv[]){
	int pid, status;
	char* buf = "Exec failed";

	bool lastHasTwo = false;
	if(argc % 2 == 1) lastHasTwo = true;

	for(int i=0;i<argc/2;i++){
		if((pid = fork()) == 0){
			char buf2[100];
			sprintf(buf2, "\nProcess Num: %d\n", getpid());
			write(STDOUT_FILENO, buf2, strlen(buf2));

			// Last command has only one argument
			if(i == (argc/2) - 1 && lastHasTwo == false){
				execlp(argv[i*2 + 1], argv[i*2 + 1], (char*)0);
				write(STDOUT_FILENO, buf, strlen(buf));
			}
			// A command that has two arguments
			else{
				execlp(argv[i*2 + 1], argv[i*2 + 1], argv[i*2 + 2], (char*)0);
				write(STDOUT_FILENO, buf, strlen(buf));
			}
		}
		wait(&status);
		write(STDOUT_FILENO, "\n", 1);
	}

	return 0;
}
