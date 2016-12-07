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
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHECK(sts,msg) if ((sts) == -1) { perror(msg); exit(-1); }

#define MAX_TENTATIVES 5
#define ALARM_TIMEOUT 10
#define PASSWORD "password"

// Initialisation du temps
time_t now;
struct tm * timeinfo;
int interrupt_input = 0;

static void handleSignal(int sig, siginfo_t *siginfo, void *context) {
  time ( &now );
  timeinfo = localtime ( &now );
  switch(sig) {
    // Si le signal est une interruption
    case SIGINT:
    printf("\nCtrl+C Pressed at:  "YELLOW"%s"RESET"\n", asctime (timeinfo));
    break;
    // Si le signal est une alarme
    case SIGALRM:
    printf("\nProgram exited at:  "RED"%s"RESET"\n", asctime (timeinfo));
    exit(0);
    break;
    default:
    printf("Action");
    break;
  }
}

static void handlePart3Signal(int sig, siginfo_t *siginfo, void *context) {
  switch(sig) {
    // Si le signal est une interruption
    case SIGINT:
    printf("\n"RED"Ctrl+C disabled"RESET"\n");
    break;
    case SIGALRM:
    exit(2);
    break;
    default:
    printf("Action");
    break;
  }
}

/**
 * Handles parent processes
 *
 * Codes d'erreurs renvoyés par le processus enfant:
 *     0: ok
 *     1: max tentatives dépassées
 *     2: temps écoulé
 */
static void parentHandler(int pid) {
  int status, sts;
  sigset_t intmask;
  // Initialisation du masque
  sts = sigemptyset(&intmask);
  sts = sigaddset(&intmask, SIGINT);
  // Bloquage du Ctrl+C uniquement pour le processus parent
  sts = sigprocmask(SIG_BLOCK, &intmask, NULL);
  // On attend un code de sortie du processus fils dont le pid est passé en paramètre
  waitpid(pid, &status, 0);
  if ( WIFEXITED(status) ) {
    int es = WEXITSTATUS(status);
    // On fait nos printf en fonction du code de sortie
    switch(es) {
      case 0:
      printf("\n"GREEN"Welcome home !"RESET"\n");
      break;
      case 1:
      printf("\n"YELLOW"Max number of retries !"RESET"\n");
      break;
      case 2:
      printf("\n"YELLOW"BOOM !"RESET"\n");
      break;
    }
  }
  while (1) {
    pause();
  }
}

/**
 * Handles child processes
 */
static void childHandler() {
  struct sigaction act;
  char input[20];
  int tentatives = 0;

  // SA_RESTART nous permet de ne pas valider le scanf en cas de Ctrl+C
  act.sa_flags = SA_RESTART;
  // On définit la fonction qui gère les signaux
  act.sa_sigaction = handlePart3Signal;
  // On ajoute un listener sur les signaux d'interruptions
  sigaction(SIGINT, &act, NULL);
  // On ajoute un listener sur les signaux d'alarme
  sigaction(SIGALRM, &act, NULL);
  // On ajoute une alarme
  alarm(ALARM_TIMEOUT);

  // Tant qu'il nous reste des tentatives et que le mot de passe saisi n'est pas le bon
  while (strcmp(PASSWORD, input) != 0 && MAX_TENTATIVES > tentatives) {
    printf("\nRetries left: %d", MAX_TENTATIVES - tentatives);
    printf("\nEnter password (%s): ", PASSWORD);
    scanf("%s", input);
    tentatives++;
  }
  // Si on a le bon mot de passe
  if (strcmp(PASSWORD, input) == 0) {
    exit(0);
  }
  else {
    exit(1);
  }
}

int main (int argc, char *argv[]) {
  CLEAR;
  time ( &now );
  timeinfo = localtime ( &now );
  printf("Program started at: "GREEN"%s"RESET"\n", asctime (timeinfo));
  printf("Process ID:         "GREEN"%d"RESET"\n", getpid());


  sigset_t intmask;
  int sts, status = -1;
  struct sigaction act;

  if (argc < 2) {
    printf("Usage:              ./build/tp1 "RED"<numeroPartie>"RESET"\n");
    exit(0);
  }

  // Partie 2
  if(argv[1][0] == '2') {
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handleSignal;

    // Initialise et affecte le masque
    // sts = sigemptyset(&intmask);
    // CHECK(sts, "appel de sigemptyset");
    // sts = sigaddset(&intmask, SIGINT);
    // CHECK(sts, "appel de sigaddset");

    // Bloquer Ctrl+C
    // sts = sigprocmask(SIG_BLOCK, &intmask, NULL);
    // CHECK(sts, "appel de sigprocmask");

    // ATTENTION ! Ne pas désactiver le Ctrl+C si on veut le catch !
    // On ajoute un "listener" à Ctrl+C
    sigaction(SIGINT, &act, NULL);
    // On ajoute un "listener" au signal émis par alarm
    sigaction(SIGALRM, &act, NULL);

    while(1) {
      pause();
    };

    exit(0);
  }
  if(argv[1][0] == '3') {
    // Exercices de compréhension
    // pid_t type = fork();
    //
    // // Si type == 0 c'est un processsus enfant
    // if (type == 0) {
    //   printf(GREEN"%d"RESET": \"Je suis le fils de "GREEN"%d"RESET"\"\n", getpid(), getppid());
    //   exit(0);
    // }
    // // Si type > 0, c'est le processus parent
    // else if (type > 0) {
    //   printf(GREEN"%d"RESET": \"Je suis ton père\"\n", getpid());
    //  wait(&status);
    // }
    // // Sinon, il y a eu échec lors de la création du processus enfant
    // else {
    //   printf(RED"Erreur lors de la création du processus enfant"RESET"\n");
    // }
    //
    // // On passe status = -1 pour attendre la réponse d'un processus fils.
    // wait(&status);
    //
    // while(1) {};

    // Synthèse
    pid_t type = fork();

    // Si type == 0 c'est un processus enfant
    if (type == 0) {
      childHandler();
    }
    // Si type > 0, c'est le processus parent. A ce moment, type = pid du processus enfant
    else if (type > 0) {
      parentHandler(type);
    }
    // Sinon, il y a eu échec lors de la création du processus enfant
    else {
      printf(RED"Erreur lors de la création du processus enfant"RESET"\n");
    }
  }
}
