#include "philosophe.h"

int main (int argc, char *argv[]) {
  CLEAR;

  if (argc < 2) {
    printf("Usage:              ./build/dejeuner_philosophes "RED"<nombre_philosophes>"RESET"\n");
    exit(0);
  }

  int nb_philosophes = atoi(&argv[1][0]), i = 0;
  t_philosophe *philosophes = (t_philosophe *)malloc(nb_philosophes * sizeof(t_philosophe));

  pthread_t *thread = (pthread_t *)malloc(nb_philosophes * sizeof(pthread_t));
  t_philosophe *p;

  for(i = 0; i < nb_philosophes; i++) {
    p = (t_philosophe *)malloc(sizeof(t_philosophe));
    p->id_philosophe = i;
    p->nb_philosophes = nb_philosophes;
    if(pthread_create(&thread[i], NULL, philosophe, p) == -1) {
      perror("pthread_create()");
      exit(EXIT_FAILURE);
    }
  }
  while(1) {};
}
