#include <stdio.h>
#include <string.h>
void encoder1a(FILE * input, FILE * output){
	int c, encoded;
	c = fgetc(input);
	encoded = c;
	while(c!=EOF){
		if((c>='A')&&(c<='Z')){
			encoded = '.';
		}
		fputc(encoded, output);
		c = fgetc(input);
		encoded = c;	
	}	
}
void encoder1b(FILE * input, FILE * output){
	int c, encoded;
	int count = 0;
	c = fgetc(input);
	encoded = c;
	while(c!=EOF){
		if((c>='A')&&(c<='Z')){
			count = count + 1;
			encoded = '.';
			fprintf(stderr,"%d %d\n", (int)(c),(int)(encoded));
		}
		else if(c == '\n'){
			fprintf(stderr, "the number of letters: %d\n", count);
			count = 0;
		}
		else{
			fprintf(stderr,"%d %d\n", (int)(c),(int)(encoded));
		}
		fputc(encoded, output);
		c = fgetc(input);
		encoded = c;
	}
}
void encryption1c(FILE * input, FILE * output, int sign, char value){
	int c;
	int number;
	int first = 0;
	if(value >= '0' && value <= '9')
		number = (int)(value - 48);
	else if(value >= 'A' && value <= 'F')
		number = (int)(value - 55);
	if(sign == 1){
		c = fgetc(input);
		int toAdd = c;
		while(c!=EOF){
			if(c != '\n'){
				fputc(c, output);
				if(first==1){
					toAdd = c;
					first = 0;
				}
			}
			else{
				int i;
				for(i = 0; i<number;i++)
					fputc(toAdd, output);
				fputc('\n', output);
				first = 1;
			}		
			c = fgetc(input);
		}
	}
	else{
		int i = 0;
		c = fgetc(input);
		while(c!=EOF){
			if(i >= number)
				fputc(c, output);
			if(c != '\n'){
				i = i+1;
			}	
			else{
				if(i<number)
					fprintf(output,"-NONE-\n");
				i = 0;
			}
			c = fgetc(input);
		}
	}
}				
int main(int argc, char **argv){
	char value;
	int sign=0;
	int debug = 0;
	int encryptPlus = 0;
	int encryptMinus = 0;
	FILE * input = stdin;
	FILE * output = stdout;
	int i;
	for(i=1; i<argc; i++){
		if(strncmp(argv[i], "-D",2)==0)
			debug = 1;
		else if(strncmp(argv[i] , "+e",2)==0){
			encryptPlus = 1;
			sign = 1;
			value = argv[i][2];
		}
		else if(strncmp(argv[i] , "-e",2)==0){
			encryptMinus = 1;
			value = argv[i][2];
		}
		if(strncmp(argv[i], "-i",2)==0){
			input = fopen(argv[i] + 2, "r");
			if(input == NULL){
				fprintf(stderr,"no input file\n");
				return 1;
			}
		}
	}
	if(encryptPlus == 0 && encryptMinus == 0&& debug == 0)
		encoder1a(input, output);
	else if(encryptPlus == 0 && encryptMinus == 0&& debug == 1)
		encoder1b(input,output);
	else if(encryptPlus == 1 || encryptMinus == 1){
		encryption1c(input, output, sign, value);
	}
	return 0;
}
		
	
