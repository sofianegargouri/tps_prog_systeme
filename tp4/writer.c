#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>

#include "lect_red.h"

buffer_t * buff;
int page_sz;
sem_t * semaphore;
//Function écrire
void * ecrire()
{
	// Le rédacteur attend le droit d'écrire
	// C'est à dire qu'il attend un jeton dans son Tampon Ecriture
	int i;
	for(i=0; i < VALEUR_FIN; i++)	{

		sleep(1);

		buff->next_value = i + 2;
		buff->next_index = (buff->next_index + 1) % FIFO_SIZE;
		buff->buff[i] = i + 1;

		//msync pr save modif
		msync(buff, page_sz, MS_SYNC);
		
		sem_post(semaphore);
	}
}

//Main
void main() {
	int fd;
	void *ret;
	pthread_t writingThread, readingThread;

	page_sz = sysconf(_SC_PAGE_SIZE);
	semaphore = sem_open("write_prs", O_CREAT | O_EXCL, 0666);

	fd = shm_open("/r11.dat", O_RDWR | O_CREAT, 0666);

	ftruncate(fd, page_sz);

	buff = (buffer_t *) mmap(0, page_sz, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	buff->next_index = 0;
	buff->next_value = 1;

	ecrire();

	sem_unlink("write_prs");
	munmap(buff, page_sz);
	close(fd);
	shm_unlink("/r11.dat");
}
