.DEFAULT_GOAL := main

main: main.c dll.h
	gcc main.c -o main

test: main
	./main

clean:
	rm -f main
