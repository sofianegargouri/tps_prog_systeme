#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define CLEAR printf("\033[H\033[J")

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#define NB_FORKS 50000

typedef struct {
  int thread_nb;
  int nb_executions;
} custom_thread;

void *do_nothing() {
  int i = 0;
  pthread_exit(EXIT_SUCCESS);
}

void *print_num_and_count(void *args) {
  struct timespec time1, time2;
  time1.tv_sec = 0;
  time1.tv_nsec = 50000000L;
  custom_thread *temp_thread = args;

  // while(temp_thread->nb_executions < 10) {
  while(1) {
    nanosleep(&time1, &time2);
    temp_thread->nb_executions++;
    printf("Thread "GREEN"%d"RESET"      Exécution "RED"%d"RESET"\n", temp_thread->thread_nb, temp_thread->nb_executions);
  }
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  int pid, j, status;
  void  * ret;

  if (argc < 2) {
    printf("Usage:              ./build/tp2 "RED"<numeroPartie>"RESET"\n");
    printf("1: Créer 50000 threads\n");
    printf("2: Lancer n threads affichant son numéro tous les 100ms\n");
    exit(0);
  }

  // Lancer 500000 threads
  if(argv[1][0] == '1') {
    pthread_t thread;
    for (j = 0; j < NB_FORKS; j++) {
      if(pthread_create(&thread, NULL, do_nothing, NULL) == -1) {
        perror("pthread_create()");
        exit(EXIT_FAILURE);
      }
      if(pthread_join(thread, &ret)) {
        perror("pthread_join()");
        exit(EXIT_FAILURE);
      }
    }
    return EXIT_SUCCESS;
  }

  // Lancer n threads
  if(argv[1][0] == '2') {
    int i = 0, thread_nb, max_threads, nb_executions = 0;
    max_threads = atoi(&argv[2][0]);
    pthread_t thread[max_threads];
    custom_thread *args;

    printf("Création de "GREEN"%d"RESET" threads\n", max_threads);

    for(i = 0; i < max_threads; i++) {
      printf("Création du thread "GREEN"%d"RESET"\n", i + 1);
      args = (custom_thread *)malloc(sizeof (custom_thread));

      thread_nb = i + 1;

      args->thread_nb = thread_nb;
      args->nb_executions = nb_executions;

      if(pthread_create(&thread[i], NULL, print_num_and_count, args) == -1) {
        perror("pthread_create()");
        exit(EXIT_FAILURE);
      }
    }

    for(i = 0; i < max_threads; i++) {
      if(pthread_join(thread[i], &ret)) {
        perror("pthread_join()");
        exit(EXIT_FAILURE);
      }
    }
    // while(1) {}
  }
}
