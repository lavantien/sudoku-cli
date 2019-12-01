all: main.exe

main.exe: main.o
    gcc -o main.exe main.o

main.o: main.c
    gcc -c main.c -std=c11 -Og -Wall

clean:
    rm main.o main.exe
