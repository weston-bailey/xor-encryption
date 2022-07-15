CFLAGS=-Wall -g

all: clean build run

build: main

clean:
	rm -rf main

run:
	./main
