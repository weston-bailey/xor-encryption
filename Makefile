CFLAGS=-Wall -g

all: clean build run

build: main

clean:
	rm -rf main

run:
	sh reset.sh
	echo "first run"
	./main list.txt hello
	echo "second run"
	./main list.txt hello
