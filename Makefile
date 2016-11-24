all: directories main

main:
	gcc main.c -o build/main

directories:
	mkdir -p build

clean:
	rm -rf build
