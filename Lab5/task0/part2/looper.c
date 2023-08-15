#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handler(int sig){
	printf("looper recived: %s\n", strsignal(sig));
	if(sig == SIGTSTP) 
		printf("stopping the process\n");
	if(sig == SIGCONT) 
		printf("continuting the process\n");
	if(sig == SIGINT) 
		printf("interrupt the process\n");
	signal(sig, SIG_DFL);
	raise(sig);
	if(sig==SIGTSTP)
		signal(SIGCONT, handler);
	if(sig == SIGCONT)
		signal(SIGTSTP, handler);	
}
		

int main(int argc, char **argv){ 
	signal(SIGINT, handler);
	signal(SIGCONT, handler);
	signal(SIGTSTP, handler);
	while(1) {
		sleep(2);
	}

	return 0;
}
