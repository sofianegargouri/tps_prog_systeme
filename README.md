# TP1 Programmation système

## Commande et fonction kill

1 - Afficher la liste des signaux pouvant être émis par la commande `kill`

> kill -l

```
1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
6) SIGABRT 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
63) SIGRTMAX-1	64) SIGRTMAX
```

2 - Écrire un programme dont la fonction main affiche son PID et est constituée de l’instruction `while(1) ;` exécutez-le et notez le comportement obtenu, lorsque vous lui envoyez les signaux suivants : `SIGINT, SIGCHLD, SIGUSR1`

`SIGINT` arrête le programme
`SIGCHLD` rien ne se passe
`SIGUSR1` arrête le programme avec le message: `User defined signal 1`

3 - Donner la commande man permettant d’obtenir de l’aide sur la fonction kill() (inclure dans le compte-rendu, le début de ces informations)

> man 2 kill

```
NAME
       kill - send signal to a process

SYNOPSIS
       #include <sys/types.h>
       #include <signal.h>

       int kill(pid_t pid, int sig);
```

4 - Même question sur les fonctions `alarm()` et `pause()`

> man alarm

```
NAME
       alarm - set an alarm clock for delivery of a signal

SYNOPSIS
       #include <unistd.h>

       unsigned int alarm(unsigned int seconds);
```


> man pause

```
NAME
       pause - wait for signal

SYNOPSIS
       #include <unistd.h>

       int pause(void);
```

5 - Remplacer l’instruction `while(1) ;` par `alarm(20) ; pause() ;` Exécuter ce programme, et expliquer le comportement de cette application.

`alarm(20)` dit au programme d'envoyer un signal dans 20 secondes, tandis que `pause()` met en pause le programme en attente d'un signal (justement envoyé par `alarm(20)`)

## Ignorer un signal

1 - Dans quel fichier sont contenues les définitions des noms symboliques identifiant les différentes sources de signaux ?

Les définitions des noms symboliques sont contenues dans `unistd.h`

2 - Quel fichier faut-il en fait inclure en tête de programme ?

`signal.h`

3 - Écrire et tester le programme de la page 69, qui désactive le traitement du contrôle-C

## Traiter un signal

1 - Modifier le programme précédent de manière à ce que le message suivant Le contrôle-C est désactivé s’affiche à chaque fois que l’utilisateur tape contrôle-C

## L'appel système fork()

1 - Tester, analyser et expliquer le comportement du programme dont la fonction main contient les instructions suivantes :
`CHECK(fork(), "ne peut créer pas un nouveau processus");`
`CHECK(fork(), " ne peut créer pas un nouveau processus)");`
`printf("Je suis le process %d, fils de %d\n", getpid(), getppid());`

La fonction `fork()` crée le même programme et l'éxecute, il le duplique.

2 - Que réalise l’appel système exit() ?

`exit()` arrête le process courant et renvoie l'int mis en paramètre à son process parent

3 - Écrire un programme dont la fonction main se termine par une boucle infinie (while(1) ;) précédée de la création d’un processus fils, chargé d’afficher son pid, celui de son père puis qui se termine.
Comment, lors de l’exécution du programme, mettre alors en évidence la présence d’un processus zombie.



5 - Interrompre l’exécution du programme en lui envoyant un signal, puis exécutez à nouveau la commande ps. Que devient le zombie ?


6 - Modifier le programme précédent de façon à ce qu’il n’y ait pas de création d’un tel processus (cf. fonctions de type wait())
