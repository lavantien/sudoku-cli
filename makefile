all: main.exe

main.exe: main.c
	gcc main.c -std=c11 -Og -Wall -o main

clean:
	rm -rf main.exe
