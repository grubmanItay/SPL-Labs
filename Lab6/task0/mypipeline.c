#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main (int argc , char* argv[]){
	char *input1[] = {"ls", "-l", 0};
	char *input2[] = {"tail", "-n", "2", 0};
	int returnVal;
	int p[2];
	pipe(p);
	int debug = 0;
	int i;
	for(i=0; i<argc; i++){
		if(strncmp(argv[i], "-D",2)==0)
	 		debug = 1;
	 }
	if (debug == 0){
		int child1ID;
		int child2ID;
		child1ID = fork();
		if(child1ID > 0){
			close(p[1]);
			child2ID = fork();
			if(fork()>0){
				close(p[0]);
				waitpid(child1ID, NULL, 0);
				waitpid(child2ID, NULL, 0);
			}
			else{
				close(0);
				dup(p[0]);
				close(p[0]);
				returnVal = execvp(input2[0], argv);
				if(returnVal <0){
					perror("could'nt execute");
					_exit(0);
				}
			}
		}
		else{
			close(1);
			dup(p[1]);
			close(p[1]);
			returnVal = execvp(input1[0], argv);
			if(returnVal <0){
				perror("could'nt execute");
				_exit(0);
			}
		}
	}
	else{
		int child1ID;
		int child2ID;
		fprintf(stderr,"(parent_process>forking...)\n");
		child1ID = fork();
		if(child1ID > 0){
			fprintf(stderr,"(parent_process>created process with id: %d)\n", child1ID);
			fprintf(stderr,"(parent_process>closing the write end of the pipe...)\n");
			close(p[1]);
			fprintf(stderr,"(parent_process>forking...)\n");
			child2ID = fork();
			if(fork()>0){
				fprintf(stderr,"(parent_process>created process with id: %d)\n", child2ID);
				fprintf(stderr,"(parent_process>closing the read end of the pipe...)\n");
				close(p[0]);
				waitpid(child1ID, NULL, 0);
				waitpid(child2ID, NULL, 0);
			}
			else{
				close(0);
				dup(p[0]);
				fprintf(stderr,"(child2>redirecting stdin to the read end of the pipe)\n");
				close(p[0]);
				fprintf(stderr,"(child1>going to execute cmd...)\n");
				returnVal = execvp(input2[0], argv);
				if(returnVal <0){
					perror("could'nt execute");
					_exit(0);
				}
			}
		}
		else{
			close(1);
			dup(p[1]);
			fprintf(stderr,"(child1>redirecting stdout to the read end of the pipe)\n");
			close(p[1]);
			fprintf(stderr,"(child1>going to execute cmd...)\n");
			returnVal = execvp(input1[0], argv);
			if(returnVal <0){
				perror("could'nt execute");
				_exit(0);
			}
		}
	}
	return 0;
}
