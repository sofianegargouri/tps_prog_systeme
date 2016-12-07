all: directories tp1 tp2

tp1:
	gcc tp1/main.c -o build/tp1

tp2:
	gcc tp2/main.c -o build/tp2

directories:
	mkdir -p build

build_release:
	rm -f PRS.zip
	zip -r PRS.zip docs tp1.c Makefile README.md

clean:
	rm -rf build
