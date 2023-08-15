all: main.exe

main.exe: main.o
	gcc -Wall -o main.exe main.o
main.o: main.c
	gcc -m32 -Wall -o main.o main.c
.PHONY: clean
clean:
	rm -f *.o *.exe
