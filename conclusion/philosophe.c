#include "philosophe.h"

void *philosophe(void * args) {
  t_philosophe *hippocrate = args;
  t_fourchette ma_fourchette, fourchette_voisin;
  pthread_t prendre, poser;
  void * ret;
  char sem_fourchette[60];

  strcpy(sem_fourchette, getFourchetteSemaphoreName(hippocrate->id_philosophe));
  if (sem_open(sem_fourchette, O_CREAT | O_EXCL) == -1) {
    printf("")
  }

  printf("Je suis le philosophe "GREEN"%d"RESET"\n", hippocrate->id_philosophe);
  printf("Mon voisin de droite est "GREEN"%d"RESET"\n", VoisinD(hippocrate));
  printf("Mon voisin de gauche est "GREEN"%d"RESET"\n", VoisinG(hippocrate));

  ma_fourchette.id_proprietaire = hippocrate->id_philosophe;
  fourchette_voisin.id_proprietaire = VoisinD(hippocrate);

  while(1) {
      penser();


      pthread_create(&prendre, NULL, prendreFourchette, &ma_fourchette);
      pthread_join(prendre, &ret);

      // prendreFourchette(VoisinD(hippocrate));

      manger();
  }

  // poserFourchette(hippocrate->id_philosophe);
  // poserFourchette(VoisinD(hippocrate));
}

void * prendreFourchette(void * args) {
  t_fourchette *fourchette = args;
  int i = 1;
  char sem[60];

  strcpy(sem, getFourchetteSemaphoreName(fourchette->id_proprietaire));

  // On attend que le semaphore soit ok
  if (sem_getvalue(sem_open(sem, 0), &i) != 0) {

    printf("test");
    sem_open(sem, 0);
    printf("test");
    sem_wait(sem_open(sem, 0));
  }

  // printf("Je prends la fourchette du philosophe %s\n", sem);
  // // On initialise le sem
  // sem_init(sem_open(sem, 0), 0, 0);
  // pthread_exit(0);
}

void* poserFourchette(void * args) {
  t_fourchette *fourchette = args;
  char sem[60];

  strcpy(sem, getFourchetteSemaphoreName(fourchette->id_proprietaire));
  sleep(1);
  // On déverouille le sémaphore
  sem_post(sem_open(sem, 0));
  printf("Je pose ma fourchette\n");


}
void penser() {
  printf("Je pense\n");

}

void manger() {

    printf("Je mange\n");
}

char *getFourchetteSemaphoreName(int proprietaire) {
  char *str = malloc (sizeof (char) * 50), *num_philo= malloc (sizeof (char) * 10);
  strcpy(str,  "/fourchette_");
  snprintf (num_philo, sizeof(num_philo), "%d", proprietaire); // print int 'n' into the char[] buffer
  strcat(str, num_philo);

  return str;
}
