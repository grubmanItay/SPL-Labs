#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
char censor(char c) {
  if(c == '!')
    return '*';
  else
    return c;
}
 
char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  	int i;
  	for(i = 0; i<array_length;i++){
  		*(mapped_array + i) = (*f)(array[i]);
  	}
  return mapped_array;
}
char my_get(char c){
	int s = fgetc(stdin);
	return s;
	}
char encrypt(char c){
	if(c >= 'A' && c<='z')
		c = c + 2;
	return c;
	}
char decrypt(char c){
if(c >= 'A' && c<='z')
	c = c - 2;
return c;
}
char dprt(char c){
	printf("%d\n", c);
	return c;
}
char cprt(char c){
	if(c >= 'A' && c<='z')
		printf("%c\n", c);
	else
		printf("*\n");
	return c;
}
char quit(char c){
	if(c == 'q')
		exit(0);
	else
		return c;
 }
 struct fun_desc {
  char *name;
  char (*fun)(char);
};
int main(int argc, char **argv){
	char* carray = malloc(sizeof(char[5]));
	strcpy(carray,"");
	struct fun_desc menu[] = { { "Censor", censor }, { "Encrypt", encrypt }, { "Decrypt", decrypt }, {"Print dec", dprt}, {"Print string", cprt}, {"Get string", my_get}, {"Quit", quit}, {NULL, NULL}};
	int size = sizeof menu/sizeof menu[0]-2;
	while(1){
		printf("Please choose a function:\n");
		int i = 0;
		while(menu[i].name != NULL){
			printf("%d) %s\n",i, menu[i].name);
			i++;
		}
		printf("Option: ");
		int choice;
		scanf("%d" ,&choice);
		fgetc(stdin);
		if (choice > size || choice < 0 ){
			printf("Not within bounds\n");
			
			exit(0);
		}
		else{
			printf("Within bounds\n");
			strcpy(carray,map(carray, 5, menu[choice].fun));
			printf("DONE.\n\n\n");
		}
	}	
}
