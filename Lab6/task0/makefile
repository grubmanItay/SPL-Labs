all: exec

exec: mypipeline.o
	gcc -m32 -g -Wall mypipeline.o 

mypipeline.o: mypipeline.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector mypipeline.c -o mypipeline.o


.PHONY: clean
clean:
	rm -f *.o
