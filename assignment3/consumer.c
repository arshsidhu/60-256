//Assignment 3
//Arshdeep Sidhu
//104567665

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// MAIN PROGRAM FOLLOWS
int main(){
	char num[3], newNum[3], buf[100];

	// reads the number
	int fd = open("storage.txt", O_RDWR);
	read(fd, num, 2);

	int n = atoi(num);
	n -= 3;

	// writes it back into the file
	sprintf(newNum, "%d", n);
	lseek(fd, 0, SEEK_SET);
	write(fd, newNum, 2);

	// prompts
	sprintf(buf, "from consumer: current total is %d\n", n);
	write(STDOUT_FILENO, buf, strlen(buf));
	close(fd);

	// Executes producer
	char* args[] = {"./producer.sh", NULL};
	execvp(args[0], args);
	printf("error\n");

	return 0;
}