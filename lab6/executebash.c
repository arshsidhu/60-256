// INCLUDE SECTION
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// MAIN PROGRAM FOLLOWS

int main(){
	int pid, status;

	char* buf = "EXAM! EXAM! EXAM!\n";
	write(STDOUT_FILENO, buf, strlen(buf));

	if((pid = fork()) == 0){
		execl("./mybash.sh", "mybash.sh", (char*)0);
		char* buf2 = "Exec failed";
		write(STDOUT_FILENO, buf2, strlen(buf2));
	}
	wait(&status);

	return 0;
}
