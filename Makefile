CFLAGS=-Wall -g

all: clean build run

build: main

clean:
	rm -rf main

run:
	sh reset.sh
	./main list.txt hello
