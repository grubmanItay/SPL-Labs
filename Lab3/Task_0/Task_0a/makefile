all: exec

exec: lab3_mergesort.o
	gcc -m32 -g -Wall lab3_mergesort.o 

lab3_mergesort.o: lab3_mergesort.c
	gcc -m32 -g -Wall -ansi -c -nostdlib -fno-stack-protector lab3_mergesort.c -o lab3_mergesort.o

debug:
	gcc -g -o debug lab3_mergesort.c

.PHONY: clean
clean:
	rm -f *.o
