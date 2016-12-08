#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

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
#define VoisinD(philosophe) (((philosophe->id_philosophe)+1 < (philosophe->nb_philosophes)) ? ((philosophe->id_philosophe)+1) : (0))
#define VoisinG(philosophe) (((philosophe->id_philosophe)-1 > 0) ? ((philosophe->id_philosophe)-1) : ((philosophe->nb_philosophes) - 1))

typedef struct {
  int id_philosophe;
  int nb_philosophes;
  int nb_penser;
  int nb_manger;
} t_philosophe;

typedef struct {
  int id_proprietaire;
} t_fourchette;

char *getFourchetteSemaphoreName(int);

void* prendreFourchette(void *);
void* poserFourchette(void *);
void penser();
void manger();
void* philosophe(void *);
