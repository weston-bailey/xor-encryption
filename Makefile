CFLAGS=-Wall -g

all: clean build run

build: main

clean:
	rm -rf main
	cat _list.txt > list.txt

run:
	./main list.txt
