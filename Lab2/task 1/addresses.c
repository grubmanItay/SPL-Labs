#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int addr5;//initialize
int addr6=567;
int addr7;

int foo();//text
void point_at(void *p);
void foo1();
void foo2();

int main (int argc, char** argv){
    int addr2;//stack
    int addr3;//stack
    char* yos="ree";//text rodata
    int * addr4 = (int*)(malloc(50));//bss
    long dist12 = (size_t)addr4 - (size_t)&addr5;//+
    printf("the bss size is: %ld\n",dist12);
    printf("- &addr2: %p\n",&addr2);/*stored in the stack*/
    printf("- &addr3: %p\n",&addr3);/*stored in the stack*/
    printf("- foo: %p\n",foo);/*stored in the text*/
    printf("- &addr5: %p\n",&addr5);/*stored in the initialized*/
    
	point_at(&addr5);
	
    printf("- &addr6: %p\n",&addr6);/*stored in the BSS*/
    printf("- yos: %p\n",yos);/*stored in the initiallized data segment*/
    printf("- addr4: %p\n",addr4);/*stored in the heap*/
    printf("- &addr4: %p\n",&addr4);/*the address of the tail of the pointer. stored in the stack*/
    
    printf("- &foo1: %p\n" ,&foo1);
    printf("- &foo2: %p\n" ,&foo2);
    printf("- &foo2 - &foo1: %ld\n" ,&foo2 - &foo1);/*both stored in the BSS and the numerical value of foo2 is bigger than foo1 because ? */
    printf(" - size of long: %p\n" , sizeof(long));/*long integer data type is not enough for dist because the size of long is up to 2^31-1 (4 bytes) and the distance of the adresses can be 2^32*/
    int iarray[3];
    float farray[3];
    double darray[3];
    char carray[3];
    printf("- &iarray: %p\n",&iarray);/* the beginning of the i array memory*/
    printf("- &iarray +1: %p\n",&iarray+1);/*the end of the iarray memory (3* 4 bytes for int)*/
    printf("- &farray: %p\n",&farray);/* 3*4 under iarray because of float*/
    printf("- &farray +1: %p\n",&farray+1);/* the beginning of iarray and the end of farray*/
    printf("- &darray: %p\n",&darray);/* 3*8 under farray because double*/
    printf("- &darray +1: %p\n",&darray+1);/* the end of darray, beginning of farray*/
    printf("- &carray: %p\n",&carray);/* 3 *1 under darray because char*/
    printf("- &carray +1: %p\n",&carray + 1);/* end of carray, beginning of darray*/
    int arr1[] = {1,2,3};
    char arr2[] = {'a','b','c'};
    int* arr1ptr =arr1;
    char* arr2ptr = arr2;
    int *p;
    printf("first element of arr1 : %d\n", *arr1ptr);
    printf("second element of arr1 : %d\n", *(arr1ptr+1));
    printf("third element of arr1 : %d\n", *(arr1ptr+2));
    printf("first element of arr2 : %c\n", *arr2ptr);
    printf("second element of arr2 : %c\n", *(arr2ptr+1));
    printf("third element of arr2 : %c\n", *(arr2ptr+2));
    printf("the value of p is : %p\n", p);
    return 0;
}

int foo(){
    return -1;
}

void point_at(void *p){
    int local;
	static int addr0 =2;
    static int addr1;
    long dist1 = (size_t)&addr6 - (size_t)p;
    long dist2 = (size_t)&local - (size_t)p;
    long dist3 = (size_t)&foo - (size_t)p;
    
    printf("dist1: (size_t)&addr6 - (size_t)p: %ld\n",dist1);/*both stored in the bss*/
    printf("dist2: (size_t)&local - (size_t)p: %ld\n",dist2);/*local stored in the stack and p in the bss*/
    printf("dist3: (size_t)&foo - (size_t)p:  %ld\n",dist3);/*???*/
	
	printf("- addr0: %p\n", & addr0);/*the numerical value of adress 0 biggert than address 1 because address 0 initialized and stored in the initiallized data segment and address 1 didnt initaillized and stored in the uninitialliezd data segment*/
    printf("- addr1: %p\n",&addr1);
}

void foo1 (){    
    printf("foo1\n"); 
}

void foo2 (){    
    printf("foo2\n");    
}
