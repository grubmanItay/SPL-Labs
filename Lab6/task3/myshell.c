#include "LineParser.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#define BUFFER_SIZE 2048
int debug=0;

int ** createPipes(int nPipes){
    int** pipes;
    pipes=(int**) calloc(nPipes, sizeof(int));
    int i;
    for (i=0; i<nPipes;i++){
        pipes[i]=(int*) calloc(2, sizeof(int));
        pipe(pipes[i]);
    }  
    return pipes;

    }
void releasePipes(int **pipes, int nPipes){
	int i;
        for (i=0; i<nPipes;i++){
            free(pipes[i]);
        
        }  
    free(pipes);
}
int *leftPipe(int **pipes, cmdLine *pCmdLine){
    if (pCmdLine->idx == 0) return NULL;
    return pipes[pCmdLine->idx -1];
}

int *rightPipe(int **pipes, cmdLine *pCmdLine){
    if (pCmdLine->next == NULL) return NULL;
    return pipes[pCmdLine->idx];
}


void printPath(){
  char path_name[PATH_MAX];
  getcwd(path_name,PATH_MAX);
  fprintf(stdout,"%s\n",path_name);
}
int specialCommand(cmdLine* command){
  int isSpecial=0;
  if(strcmp(command->arguments[0],"quit")==0){
    isSpecial=1;
    _exit(EXIT_SUCCESS);
    }
  if(strcmp(command->arguments[0],"cd")==0){
    isSpecial=1;
    if(chdir(command->arguments[1])<0)
      perror("bad cd command");
  }
  if(isSpecial)
    freeCmdLines(command);
  return isSpecial;
}
void execute(cmdLine* pCmdLine){
  int input=0;
  int ouput=1;
  int numOfPipes =0;
  if(!specialCommand(pCmdLine)){
    int childPid;
    if(!(childPid=fork())){
      if(pCmdLine->inputRedirect){
        close(input);
        if(!fopen(pCmdLine->inputRedirect, "r")){
          perror(strerror(errno));
          exit(EXIT_FAILURE);
        }
      }
      if(pCmdLine->outputRedirect){
        close(ouput);
        if(!fopen(pCmdLine-> outputRedirect, "w+")){
          perror(strerror(errno));
          exit(EXIT_FAILURE);
        }
      }
      if(pCmdLine->next != NULL){
      		numOfPipes++;
		cmdLine* first = pCmdLine;
      		while(pCmdLine->next != NULL){
      			pCmdLine = pCmdLine->next;
      			numOfPipes++;
      			fprintf(stderr,"%d\n",numOfPipes);
      		}
		pCmdLine = first;
		int** pipes;
		pipes = createPipes(numOfPipes);
      }
      else if(execvp(pCmdLine->arguments[0],pCmdLine->arguments)<0){
           perror(strerror(errno));
           _exit(EXIT_FAILURE);
      }
    }
    if(debug)
      fprintf(stderr, "PID: %d\nExecuting command: %s\n",childPid,pCmdLine->arguments[0] );
    if(pCmdLine->blocking)
      waitpid(childPid,NULL,0);
  }
}
void singlePipe(cmdLine* input){
    pid_t child1_pid, child2_pid;
    int p[2];
    if (pipe(p)==-1){
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }
    child1_pid = fork();
    if (child1_pid==-1){
        int error_code = errno;
        perror(strerror(error_code));
        exit(EXIT_FAILURE);
    }
    if (!child1_pid){
        close(1);
        dup2(p[1],1);
        close(p[1]);
        if(execvp(input->arguments[0] ,input->arguments)<0)
          perror(strerror(errno));
    }
    else {
        close(p[1]);
        child2_pid = fork();
        if (child2_pid==-1){
            perror(strerror(errno));
            exit(EXIT_FAILURE);
        }
        if (!child2_pid){
            close(0);
            dup2(p[0],0);
            close(p[0]);
            if (execvp(input->next->arguments[0] ,input->next->arguments)<0)
              perror(strerror(errno));
        }
        else {
            close(p[0]);
            waitpid (child1_pid,NULL,0);
            waitpid (child2_pid,NULL,0);
        }
    }
}




int main(int argc, char const *argv[]) {
  FILE* input = stdin;
  char buf[BUFFER_SIZE];
  int i;
  for(i=1;i<argc;i++){
    if((strcmp("-D",argv[i])==0)){
      debug=1;
    }
  }
  while(1){
    printPath();
    fgets(buf,BUFFER_SIZE,input);
    cmdLine* line = parseCmdLines(buf);
int i;
while(line->next != NULL)
{
fprintf(stderr, "%s\n",line);
}
    execute(line);

    freeCmdLines(line);
  }
  return 0;
}
