all: exec

exec: task0b.o
	gcc -m32 -g -Wall task0b.o 

task0b.o: task0b.c
	gcc -m32 -g -Wall -ansi -c -nostdlib -fno-stack-protector task0b.c -o task0b.o

debug:
	gcc -g -o debug task0b.c

.PHONY: clean
clean:
	rm -f *.o
