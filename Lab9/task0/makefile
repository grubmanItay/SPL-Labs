
all: myELF

myELF: elf.o 
	gcc -m32 -g -Wall -o myELF elf.o 

elf.o: elf.c
	gcc -g -Wall -m32  -c -o elf.o elf.c

.PHONY: clean

clean: 
	rm -f *.o myELF
