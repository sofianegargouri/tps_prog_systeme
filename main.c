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
#define CHECK(sts,msg) if ((sts) == -1) { perror(msg); exit(-1); }

// Initialisation du temps
time_t now;
struct tm * timeinfo;

void test() {

}

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

int main (int argc, char *argv[]) {
  CLEAR;
  time ( &now );
  timeinfo = localtime ( &now );
  printf("Program started at: "GREEN"%s"RESET"\n", asctime (timeinfo));
  printf("Process ID:         "GREEN"%d"RESET"\n", getpid());


  sigset_t intmask;
  int sts;
  struct sigaction act;

  if (argc < 2) {
    printf("Usage:              ./build/main "RED"<numeroPartie>"RESET"\n");
    exit(0);
  }

  // Partie 3
  if(argv[1][0] == '3') {
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

    alarm(10);

    while(1) {
      pause();
    };

    exit(0);
  }
  if(argv[1][0] == '4') {
    CHECK(fork(), "ne peut créer pas un nouveau processus");
    CHECK(fork(), " ne peut créer pas un nouveau processus)");
    printf("Je suis le process %d, fils de %d\n", getpid(), getppid());
  }
}
