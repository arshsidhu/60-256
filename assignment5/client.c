//Arshdeep Sidhu
//Client.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5555

int main(){

	
	int cliSoc; // define variables 
	struct sockaddr_in serverAddr;
	char buffer[1024];
	int resLen;

	
	cliSoc = socket(PF_INET, SOCK_STREAM, 0); // open the socket
	memset(&serverAddr, '\0', sizeof(serverAddr));
	printf("--- Socket opened ---\n");

	
	serverAddr.sin_family = AF_INET; // set socket address and port
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	
	printf("--- Connecting... ---\n");
	
	if (connect(cliSoc, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0){ // connect socket to the address and port
		printf("Error: Can't connect to the server\n");
		exit(1);
	}
	printf("--- Connected to server! ---\n");
	char command[128];

	while(1){

		printf("Enter command: ");
		scanf("%s", command);
		if (send(cliSoc, command, strlen(command), 0) == -1){
			printf("Error: can't send command!");
			exit(1);
		}

		// receive a response from the server
		resLen = recv(cliSoc, buffer, 1024, 0);
		if (resLen == -1){
			printf("Error: can't receive response!");
			exit(1);
		}
		else if (resLen > 0){
			for (int i = 0; i < resLen; i++){
				if (buffer[i] == '\n'){
					printf("    ");
					continue;
				}
				printf("%c", buffer[i]);
			}
			printf("\n\n");
		}
		else if (resLen == 0){
			printf("--- Server not responding, exiting... ---\n");
			break;
		}
	}
	
	close(cliSoc);

	return 0;
}
