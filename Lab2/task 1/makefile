all: exec

exec: addresses.o
	gcc -m32 -g -Wall addresses.o 

addresses.o: addresses.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector addresses.c -o addresses.o

.PHONY: clean
clean:
	rm -f *.o
