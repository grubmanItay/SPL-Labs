#include <stdio.h>
#include<stdlib.h>

typedef struct virus {
    unsigned short SigSize;
    unsigned char* sig;
    char virusName[16];
} virus;
int PrintHex(unsigned char* buffer, size_t size){
	int i;
	for (i = 0; i<size; i++)
		printf("%02X ",buffer[i]);
	printf("\n");
	return 0;
}

void readVirus(virus* vir, FILE* input){
	unsigned char* sizeBuffer = malloc(2);
	fread(sizeBuffer,sizeof(char),2,input);
	vir->SigSize = (sizeBuffer[1] << 8) | sizeBuffer[0];
	unsigned char* buffer = malloc(vir->SigSize+16);
	fread(buffer,sizeof(char),vir->SigSize+16,input);
	vir->sig = buffer;
	int i;
	for(i = 0; i<16; i++)
		vir->virusName[i] = buffer[vir->SigSize + i];
}

void printVirus(virus* vir, FILE* output){
	printf("Virus name: %s\n",vir->virusName);
	printf("Virus size: %d\n",vir->SigSize);
	printf("signature: \n");
	PrintHex(vir->sig, vir->SigSize);
	printf("\n");
}
typedef struct link link;
 
struct link {
    link *nextVirus;
    virus *vir;
};
void list_print(link *virus_list, FILE* output){
     /* Print the data of every link in list to the given stream. Each item followed by a newline character. */
     while(virus_list != NULL){
	        printVirus(virus_list->vir,output);
      	        virus_list = virus_list->nextVirus;
      }
}
link* list_append(link* virus_list, link* to_add){
     /* Add the given link to the list
        (either at the end or the beginning, depending on what your TA tells you),
        and return a pointer to the list (i.e., the first link in the list).
        If the list is null - return the given entry. */
        if(virus_list->vir != NULL)
        	to_add->nextVirus = virus_list;
        return to_add;
  }
       
 
void list_free(link *virus_list){
     /* Free the memory allocated by the list. */
        while(virus_list != NULL){
	      link* temp = virus_list->vir;
	      virus_list = virus_list->nextVirus;
	      free(temp);
      }
}
void detect_virus(char *buffer, unsigned int size, link *virus_list){
	int i;
	link* current;
	for(i=0;i<size;i++){
		current = virus_list;
		while(current != NULL){
			virus* currentVirus = current->vir;
			if(size-i>=currentVirus->SigSize){
		        	if(memcmp(buffer + i,currentVirus->sig,currentVirus->SigSize)==0){
		      			printf("the location of the first byte: %p\nthe virus name: %s\nthe size of the virus: %d\n",&buffer[i], currentVirus->virusName,currentVirus->SigSize);
		      		}
		        }
		      current = current->nextVirus;	 
		}
	}
	free(current);
}
int main(){
	link *virus_list = malloc(sizeof(link));
	int loaded = 0;
	while(1){
		printf("1) Load signatures\n2) Print signatures\n3) Detect viruses\n4) Quit\n");
		int choice;
		scanf("%d" ,&choice);
		fgetc(stdin);
		if(choice == 1){
			char* path;
			scanf("%[^\n]s",path);
			FILE *input = fopen(path,"r");
			if(input != NULL){
				while(!feof(input)){
					virus* temp = malloc(sizeof(virus));
					link* tempLink = malloc(sizeof(link));
					readVirus(temp,input);
					if (temp->SigSize > 0){
						tempLink->vir = temp;
						virus_list = list_append(virus_list,tempLink);
					}
				}
				loaded = 1;
			}
		}
		if(choice == 2){
			if(loaded == 1){
				list_print(virus_list,stdout);
			}
		}
		if(choice == 3){
			char* buffer = malloc(10000);
			char* path;
			scanf("%[^\n]s",path);
			FILE *input = fopen(path,"r");
			fseek(input, 0L, SEEK_END);
			size_t size = ftell(input);
			fseek(input, 0L, SEEK_SET);
			fread(buffer,sizeof(char),size,input);
			detect_virus(buffer,size,virus_list);
			free(buffer);
		}
		if(choice == 4){
			list_free(virus_list);
			exit(0);
		}
	}
	return 0;
}

