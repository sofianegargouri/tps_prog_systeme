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
#include <ctype.h>
#include <semaphore.h>
#define NB_FORKS 50000

typedef struct {
  int thread_nb;
  int nb_executions;
} custom_thread_part2;

typedef struct {
  char *string;
} custom_thread_part3;

sem_t semaphore;
static pthread_mutex_t mutex;
struct timespec time1, time2;

void *toLowerCase(void *args) {
  custom_thread_part3 *temp_thread = args;

  char *phrase=temp_thread->string;
  int i = 0;
  sem_wait(&semaphore);
  while(phrase[i] != '\0') {
    printf("%c", tolower(phrase[i]));
    fflush(stdout);
    nanosleep(&time1, &time2);
    i++;
  }
  printf("\n");
  sem_post(&semaphore);
}

void *toUpperCase(void *args) {
  custom_thread_part3 *temp_thread = args;

  char *phrase=temp_thread->string;
  int i = 0;
  sem_wait(&semaphore);
  while(phrase[i] != '\0') {
    printf("%c", toupper(phrase[i]));
    fflush(stdout);
    nanosleep(&time1, &time2);
    i++;
  }
  printf("\n");
  sem_post(&semaphore);
}

void toLowerCase_fork(char *args) {
  pthread_mutex_lock(&mutex);
  int i = 0;
  while(args[i] != '\0') {
    printf("%c", tolower(args[i]));
    fflush(stdout);
    nanosleep(&time1, &time2);
    i++;
  }
  printf("\n");
  pthread_mutex_unlock(&mutex);
}

void toUpperCase_fork(char *args) {
  pthread_mutex_lock(&mutex);
  int i = 0;
  while(args[i] != '\0') {
    printf("%c", toupper(args[i]));
    fflush(stdout);
    nanosleep(&time1, &time2);
    i++;
  }
  printf("\n");
  pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {
  int pid, j, status;
  time1.tv_sec = 0;
  time1.tv_nsec = 50000000L;
  void  * ret;

  if (argc < 2) {
    printf("Usage:              ./build/tp2 "GREEN"<numeroPartie>"RESET"\n");
    printf("        1: Créer 50000 threads\n");
    printf("        2: Lancer n threads affichant son numéro tous les 100ms\n");
    exit(0);
  }

  // Afficher deux chaînes de caractères l'une après l'autre
  if(argv[1][0] == '1') {
    sem_init(&semaphore, 1, 1);
    // pthread_t *to_lowercase = (pthread_t *)malloc(sizeof(pthread_t));
    // pthread_t *to_uppercase = (pthread_t *)malloc(sizeof(pthread_t));

    if (argc < 3) {
      printf("Usage:              ./build/tp3 1 "GREEN"\"<chaine de caractères>\""RESET"\n");
      exit(1);
    }

    // custom_thread_part3 *args;
    //
    // args->string = argv[2];
    //
    // if(pthread_create(to_lowercase, NULL, toLowerCase, args) == -1) {
    //   perror("pthread_create()");
    //   exit(EXIT_FAILURE);
    // }
    // if(pthread_create(to_uppercase, NULL, toUpperCase, args) == -1) {
    //   perror("pthread_create()");
    //   exit(EXIT_FAILURE);
    // }
    // if(pthread_join(*to_lowercase, &ret)) {
    //   perror("pthread_join()");
    //   exit(EXIT_FAILURE);
    // }
    // if(pthread_join(*to_uppercase, &ret)) {
    //   perror("pthread_join()");
    //   exit(EXIT_FAILURE);
    // }

    /**
     * threads mutex
     */

    pid_t process1 = fork();
    pid_t process2 = fork();
    pthread_mutex_init(&mutex, NULL);
    int status;

    if (process1 == 0 && process2 == 0) {
      toUpperCase_fork(argv[2]);
      toLowerCase_fork(argv[2]);
    }
    if(process1 > 0) {
      waitpid(process1, &status, 0);
    }
    if(process2 > 0) {
      waitpid(process1, &status, 0);
    }
    // Sinon, il y a eu échec lors de la création du processus enfant
    if (process1 == -1 || process2 == -1 ) {
      printf(RED"Erreur lors de la création du processus enfant"RESET"\n");
    }
    pthread_mutex_destroy(&mutex);
  }

  // Lancer n threads
  if(argv[1][0] == '2') {
  }

  if(argv[1][0] == '3') {
  }
}
