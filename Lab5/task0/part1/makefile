all: exec

exec: myshell.o LineParser.o
	gcc -m32 -g -Wall myshell.o LineParser.o -o task0

LineParser.o: LineParser.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector LineParser.c -o LineParser.o

myshell.o: myshell.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector myshell.c -o myshell.o


.PHONY: clean
clean:
	rm -f *.o task0
