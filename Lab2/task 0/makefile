all: exec

exec: count-words.o
	gcc -m32 -g -Wall count-words.o 

count-words.o: count-words.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector count-words.c -o count-words.o

debug:
	gcc -g -o debug count-words.c

.PHONY: clean
clean:
	rm -f *.o
