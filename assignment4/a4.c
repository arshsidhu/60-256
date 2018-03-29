// Assignment 4
// Arshdeep Sidhu

// INCLUDE SECTION
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

// STRUCT DEFINITIONS FOLLOW

typedef struct colour{
	int r;
	int g;
	int b;
} Colour;

// FUNCTION PROTOTYPES FOLLOW
Colour sToCol(char* str);
void alarmHandler(int dummy){};

// MAIN PROGRAM FOLLOWS
int main(int arg_c, char* arg_v[]){
	signal(SIGALRM, alarmHandler);

	if(arg_c != 7 && arg_c != 9) exit(1);

	Colour cols[5];
	for(int i=0;i<5;i++){
		cols[i] = sToCol(arg_v[i+2]);
	}

	int len = 1000, children = 10;

	// When variable len/len , children entered 
	if(arg_c == 9){
		len = atoi(arg_v[7]) - atoi(arg_v[7]) % 4;
		children = atoi(arg_v[8]) + atoi(arg_v[8]) % 2;
	}

	int pid[children], v, edLen;
	char* name = arg_v[1];
	char c[3];
	strcat(name, ".ppm");

	// Writing header to image
	int newImg = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);

	if(arg_c == 7){
		char* tmpS = "P6\n1000 1000\n255\n";
		write(newImg, tmpS, strlen(tmpS));
		edLen = strlen(tmpS);
	}
	else{
		write(newImg, "P6\n", 3);
		write(newImg, arg_v[7], strlen(arg_v[7]));
		write(newImg, " ", 1);
		write(newImg, arg_v[7], strlen(arg_v[7]));
		write(newImg, "\n255\n", 5);
		edLen = 2 * strlen(arg_v[7]) + 9;
	}

	close(newImg);

	// loops through all children
	for(int i=0;i<children;i++){

		if((pid[i] = fork()) == 0){

			pause();


			int newImg = open(name, O_WRONLY);
			lseek(newImg, (len / children) * len * 3 * i + edLen, SEEK_SET);

			// prints one row to the image
			for(int j=0;j<(len/children);j++){

				if(i < children/2){
					*c = cols[1].r;
					*(c+1) = cols[1].g;
					*(c+2) = cols[1].b;
					for(int k=0;k<(len/2);k++){
						write(newImg, c, 3);
					}
					*c = cols[2].r;
					*(c+1) = cols[2].g;
					*(c+2) = cols[2].b;
					for(int k=0;k<(len/2);k++){
						write(newImg, c, 3);
					}

					if((v = 2 * (i*(len/children) + j - (len/4))) >= 0){
						*c = cols[0].r;
						*(c+1) = cols[0].g;
						*(c+2) = cols[0].b;
						lseek(newImg, (-1 * len * 3) + (len/2)*3 - v*3/2, SEEK_CUR);
						for(int l=0;l<v;l++){
							write(newImg, c, 3);

						}
						lseek(newImg, len/2*3 - v*3/2, SEEK_CUR);
					}
				}
				else{
					*c = cols[3].r;
					*(c+1) = cols[3].g;
					*(c+2) = cols[3].b;
					for(int k=0;k<len/2;k++){
						write(newImg, c, 3);
					}
					*c = cols[4].r;
					*(c+1) = cols[4].g;
					*(c+2) = cols[4].b;
					for(int k=0;k<len/2;k++){
						write(newImg, c, 3);
					}

					if((v = 2 * (3*len/4 - i*(len/children) - j)) > 0){
						*c = cols[0].r;
						*(c+1) = cols[0].g;
						*(c+2) = cols[0].b;
						lseek(newImg, (-1 * len * 3) + len/2*3 - v*3/2, SEEK_CUR);
						for(int l=0;l<v;l++){
							write(newImg, c, 3);

						}
						lseek(newImg, len/2*3 - v*3/2, SEEK_CUR);
					}
				}
			}
			close(newImg);
			exit(0);

		}
	}
	// Sends a signal to all of the children to write to the image
	for(int i=0;i<children;i++){
		kill(pid[i], SIGALRM);
		sleep(1);
	}

	return 0;
}

// FUCNTION DEFINITIONS FOLLOW

/*	changes a colour's string name to a Colour struct which contains an rgb value
	input: char* str
	output: the corresponding Colour struct
*/
Colour sToCol(char* str){
	Colour tmp;

	if(strcmp(str,"red") == 0){
		tmp = (Colour){.r = 255, .g = 0, .b = 0};
	}
	else if(strcmp(str,"green") == 0){
		tmp = (Colour){.r = 0, .g = 255, .b = 0};
	}
	else if(strcmp(str,"blue") == 0){
		tmp = (Colour){.r = 0, .g = 0, .b = 255};
	}
	else if(strcmp(str,"orange") == 0){
		tmp = (Colour){.r = 255, .g = 165, .b = 0};
	}
	else if(strcmp(str,"cyan") == 0){
		tmp = (Colour){.r = 0, .g = 255, .b = 255};
	}
	else if(strcmp(str,"magenta") == 0){
		tmp = (Colour){.r = 255, .g = 0, .b = 255};
	}
	else if(strcmp(str,"ocean") == 0){
		tmp = (Colour){.r = 0, .g = 119, .b = 190};
	}
	else if(strcmp(str,"violet") == 0){
		tmp = (Colour){.r = 238, .g = 130, .b = 238};
	}
	else if(strcmp(str,"yellow") == 0){
		tmp = (Colour){.r = 255, .g = 255, .b = 0};
	}
	else {
		tmp = (Colour){.r = 0, .g = 0, .b = 0};
	}

	return tmp;
}