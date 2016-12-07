# TP2 Programmation système

## Processus/threads

1 - Le temps d'exécution du programme `test_fork` est le suivant:

```
real	0m3.198s
user	0m0.020s
sys	0m0.956s
```

Le programme met donc *3.198s* à s'exécuter.

2 - Un thread est comme un processus, cependant, un processus va faire appel à de la mémoire virtuelle tandis que tous les threads d'un programme partagent la même. Les threads s'exécutent les uns après les autres.

- `pthread_create()`: Permet de créer un thread
- `pthread_exit()`: Permet d'arrêter un thread
- `pthread_join()`: Lance un thread lorsque le thread passé en paramètre se termine

Pour utiliser les threads, nous devons inclure la librairie `<pthread.h>`
/!\ Nous devons aussi ajouter l'option `-pthread` lors de la compilation.

4 - Le temps d'exécution de l'application est:

```
real	0m0.573s
user	0m0.072s
sys	0m0.228s
```

Le programme met donc *0.573s* à s'exécuter, soit environ 5.6 fois plus rapide que le programme avec les forks.

## Parallélisme

1 - Pour passer un paramètre à un thread, il faut stocker la valeur de ce paramètre dans une adresse et passer cette adresse en paramètre. Lorsqu'on veut utiliser plusieurs paramètres pour exécuter une fonction depuis un thread, il faut créer une structure avec les valeurs dont nous avons besoin.
