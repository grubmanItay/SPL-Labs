#include "util.h"
#define SYS_WRITE 4
#define STDOUT 1
#define STDIN 0
#define SOPEN 5
#define SREAD 3


int main (int argc , char **argv)
{
int debug = 0;
int inputFlag = 0;
int outputFlag = 0;
int i;
char* input;
char* output;
for(i=0; i<argc; i++){
	if(strncmp(argv[i], "-D",2)==0)
	 	debug = 1;
	 if(strncmp(argv[i], "-i",2)==0){
		input = argv[i]+2;
		inputFlag = 1;
		}
	if(strncmp(argv[i], "-o",2)==0){
		outputFlag = 1;
	 	output = argv[i]+2;

	 }
}
if(debug == 0){
	char buffer[10000];
	int counter = 0;
	int numOfBytes;
	if(inputFlag == 1){
		int desc = system_call(SOPEN, input,0x000,0x400);
		numOfBytes = system_call(SREAD,desc,buffer, 10000);
	}
	else
		numOfBytes = system_call(SREAD,STDIN,buffer, 10000);
	int i;
	for(i = 0;i<numOfBytes-1;i++){
		if(strncmp(buffer+i, " ",1)!=0)
			{
				if(strncmp(buffer+i+1, " ",1)==0||strncmp(buffer+i+1, "\n",1)==0)
					counter ++;
			}
	}
	char* str = itoa(counter);
	if(outputFlag == 0){
		system_call(SYS_WRITE,STDOUT, str,strlen(str));
		system_call(SYS_WRITE,STDOUT,"\n",1);
		}
	else{
		int desc = system_call(SOPEN, output,0x001|64);/*problem*/
		system_call(SYS_WRITE,desc, str,strlen(str));
		system_call(SYS_WRITE,desc,"\n",1);
		system_call(6,desc);
	}
	
}
else{
	char buffer[10000];
	int counter = 0;
	int numOfBytes;
	if(inputFlag == 1){
		int desc = system_call(SOPEN, input,0x000,0x400);
		system_call(SYS_WRITE, 2,"read from: ",11);
		system_call(SYS_WRITE, 2, input,strlen(input));
		system_call(SYS_WRITE,2,"\n",1);
		numOfBytes = system_call(SREAD,desc,buffer, 10000);
		char* str1 = itoa(numOfBytes);
		system_call(SYS_WRITE, 2,"operation ID: ",14);
		system_call(SYS_WRITE, 2,"3",1);
		system_call(SYS_WRITE, 2," return: ",9);
		system_call(SYS_WRITE, 2,str1,strlen(str1));
		system_call(SYS_WRITE,2,"\n",1);
	}
	else{
		numOfBytes = system_call(SREAD,STDIN,buffer, 10000);
		system_call(SYS_WRITE, 2,"read from: ",11);
		system_call(SYS_WRITE, 2, "STDIN",5);	
		system_call(SYS_WRITE,2,"\n",1);
	}
	int i;
	for(i = 0;i<numOfBytes-1;i++){
		if(strncmp(buffer+i, " ",1)!=0)
			{
				if(strncmp(buffer+i+1, " ",1)==0||strncmp(buffer+i+1, "\n",1)==0)
					counter ++;
			}
	}
	char* str = itoa(counter);
	if(outputFlag == 0){
		system_call(SYS_WRITE, 2,"write to: ",10);
		system_call(SYS_WRITE, 2, "STDOUT",6);
		system_call(SYS_WRITE,2,"\n",1);	
		int num = system_call(SYS_WRITE,STDOUT, str,strlen(str));
		char* str2 = itoa(num);
		system_call(SYS_WRITE,STDOUT,"\n",1);
		system_call(SYS_WRITE, 2,"operation ID: ",14);
		system_call(SYS_WRITE, 2,"4",1);
		system_call(SYS_WRITE, 2," return: ",9);
		system_call(SYS_WRITE, 2,str2,strlen(str2));
		system_call(SYS_WRITE,2,"\n",1);
		}
	else{
		system_call(SYS_WRITE, 2,"write to: ",10);
		system_call(SYS_WRITE, 2, output,strlen(output));
		system_call(SYS_WRITE,2,"\n",1);
		int desc = system_call(SOPEN, output,0x001|64);/*problem*/
		int num = system_call(SYS_WRITE,desc, str,strlen(str));
		system_call(SYS_WRITE,desc,"\n",1);
		system_call(6,desc);
		char* str2 = itoa(num);
		system_call(SYS_WRITE, 2,"operation ID: ",14);
		system_call(SYS_WRITE, 2,"4",1);
		system_call(SYS_WRITE, 2," return: ",9);
		system_call(SYS_WRITE, 2,str2,strlen(str2));
		system_call(SYS_WRITE,2,"\n",1);
	
	}
	
}
return 0;
}	 	

