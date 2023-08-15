all: exec

exec: looper.o
	gcc -m32 -g -Wall looper.o -o task0


looper.o: looper.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector looper.c -o looper.o


.PHONY: clean
clean:
	rm -f *.o task0
