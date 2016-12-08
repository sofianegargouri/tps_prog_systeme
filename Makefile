all: directories tp_one tp_two tp_three
# ajouter dej_philo

tp_one:
	gcc tp1/main.c -o build/tp1

tp_two:
	gcc tp2/main.c -o build/tp2  -pthread

tp_three:
	gcc tp3/main.c -o build/tp3  -pthread

dej_philo:
	rm /dev/shm/fourchette_*
	gcc -o build/dejeuner_philosophes conclusion/main.c conclusion/philosophe.c -pthread

directories:
	mkdir -p build

build_release:
	rm -f PRS.zip
	zip -r PRS.zip docs tp1 tp2 tp3 conclusion Makefile README.md

clean:
	rm -rf build
