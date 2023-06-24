all: main

main: main.c
	gcc main.c -std=c17 -O3 -Wall -o main

test: test.c
	gcc test.c -std=c17 -O3 -Wall -o test

clean:
	rm -rf main test

.PHONY: all main test clean
