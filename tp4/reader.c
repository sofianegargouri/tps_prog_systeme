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
sem_t semaphore;
//Function écrire
void * lire()
{
  int fd;
  while ((fd = shm_open("/r11.dat", O_RDWR, 0666)) != -1) {
    printf("ok\n");
		sem_wait(sem_open("write_prs", 0));
    int page_sz = sysconf(_SC_PAGE_SIZE);
    CHECK_IF(buff = (buffer_t *) mmap(0, page_sz, PROT_READ, MAP_SHARED, fd, 0), MAP_FAILED, "erreur mmap");
    printf("buff"YELLOW"["RESET"%d"YELLOW"]"RESET" = "GREEN"%d"RESET"\n", buff->next_index, buff->next_value);
    close(fd);
  }
}

//Main
void main() {
  int fd;
  int page_sz;

  lire();

  munmap(buff, page_sz);
  close(fd);
  shm_unlink("/r11.dat");
}
