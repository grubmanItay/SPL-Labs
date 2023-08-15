#include <stdio.h>
#include<stdlib.h>
int main(int argc, char **argv){
	FILE* input;
	input = fopen(argv[1],"r");
	fseek(input, 0L, SEEK_END);
	size_t size = ftell(input);
	fseek(input, 0L, SEEK_SET);
	unsigned char* buffer = malloc(size);
	
	fread(buffer,sizeof(char),size,input);
	PrintHex(buffer,size);	
	return 0;
}
int PrintHex(unsigned char* buffer, size_t size){
		int i;
		for (i = 0; i<size-1; i++)
			printf("%02X ",buffer[i]);
		printf("\n");
		return 0;
}
