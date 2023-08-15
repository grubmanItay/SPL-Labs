all: exec

exec: task1.o
	gcc -m32 -g -Wall task1.o 

task1.o: task1.c
	gcc -m32 -g -Wall -ansi -c -nostdlib -fno-stack-protector task1.c -o task1.o

debug:
	gcc -g -o debug task1.c

.PHONY: clean
clean:
	rm -f *.o
