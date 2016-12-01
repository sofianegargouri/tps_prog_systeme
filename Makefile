all: directories main

main:
	gcc main.c -o build/main

directories:
	mkdir -p build

build_release:
	rm -f PRS.zip
	zip -r PRS.zip docs main.c Makefile README.md

clean:
	rm -rf build
