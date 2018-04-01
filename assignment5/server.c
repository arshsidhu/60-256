//Arshdeep Sidhu
//Server.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5555

int main(){

	
	int sockfd; // Init original socket
	struct sockaddr_in serverAddr;

	
	int newSocket; // Init new socket and addr struct
	struct sockaddr_in newAddr;

	
	socklen_t addr_size; // Define variables
	char buffer[1024];

	
	sockfd = socket(PF_INET, SOCK_STREAM, 0); // Open socket and zero it
	memset(&serverAddr, '\0', sizeof(serverAddr));

	
	serverAddr.sin_family = AF_INET; // Populate struct
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

	
	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); // bind the original socket to the address

	
	listen(sockfd, 5); // start listening on the original socket with a backlog of 5 connections
	printf("--- Server listening on port %d with backlog of 5 connections ---\n", PORT);

	while(1){
		printf("--- Waiting for connections... ---\n");
		// accept incoming connections, populate the new socket and new socket address
		addr_size = sizeof(newAddr);
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		printf("--- Accepted connection! ---\n");
	
		// more variables
		int cmdLen = 0;
		char args[2][128] = {"", ""};
		memset (args[0], '\0', 100);
		int p[2];
		char *empty = "";
	
	
		while (1){
	
			// receive the command from the client		
			cmdLen = recv(newSocket, buffer, 1024, 0);
			if (cmdLen == -1){
				printf("Error: can't receive command!");
				exit(1);
			}
			else if (cmdLen > 0){ 
				printf("command received: ");
				int i;
				for (i = 0; i < cmdLen; i++){
					printf("%c", buffer[i]);
				}
					
				// populate args
				strncpy(args[0], buffer, i);
				args[0][i] = '\0';
				printf("\n");
			}
			else if (cmdLen == 0){
				break;
			}
			
			// start a pipe
			pipe(p);
	
			// fork and execute the command
			if (fork() == 0){
				close(p[0]);
				dup2(p[1], 1);
				char *args2[] = {args[0], NULL};
				execvp(args2[0], args2);
			}
			else{
				close(p[1]);

				char buf[1];
				int i = 0;
				while(read(p[0], buf, 1) > 0){
					buffer[i] = buf[0];
					i++;
				}
				buffer[i] = '\0';
			}
	
			// send a response to the connected client
			//scanf("%s", buffer);
			send(newSocket, buffer, strlen(buffer), 0);
			//printf("[+] Sent response to client!\n");
		}
		printf("--- Connection broken ---\n\n");
	}
	return 0;
}

