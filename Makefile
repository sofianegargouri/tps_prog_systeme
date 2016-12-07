all: directories tp_one tp_two

tp_one:
	gcc tp1/main.c -o build/tp1

tp_two:
	gcc tp2/main.c -o build/tp2  -pthread

directories:
	mkdir -p build

build_release:
	rm -f PRS.zip
	zip -r PRS.zip docs tp1 tp2 Makefile README.md

clean:
	rm -rf build
