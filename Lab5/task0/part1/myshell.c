#include "LineParser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <unistd.h>

#define size 2048

void printCWD(){
	char path[PATH_MAX];
	getcwd(path,PATH_MAX);
	fprintf(stdout,"%s\n", path);
}

void execute(cmdLine* pCmdLine){
	if(strcmp(pCmdLine->arguments[0],"quit")==0)
		exit(EXIT_SUCCESS);
	int ret = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
	if(ret<0){
		perror("could not execute the command");
		exit(EXIT_FAILURE);
	}
}

int main (int argc , char* argv[]){
	FILE* input = stdin;
	char buffer[size];
	while(1){
		printCWD();
		fgets(buffer, size, input);
		cmdLine* line = parseCmdLines(buffer);
		execute(line);
		freeCmdLines(line);
		}
	return 0;
}
