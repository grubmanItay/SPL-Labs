all: exec

exec: task2.o
	gcc -m32 -g -Wall task2.o 

task2.o: task2.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector task2.c -o task2.o

.PHONY: clean
clean:
	rm -f *.o
