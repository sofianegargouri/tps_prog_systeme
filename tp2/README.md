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

3 - L'arborescence des processus est la suivante:

```
tp2(13230)─┬─{tp2}(13231)
           ├─{tp2}(13232)
           ├─{tp2}(13233)
           ├─{tp2}(13234)
           └─{tp2}(13235)
```

Les threads d'un même processus sont parallèles les uns aux autres.

## Concurrence

### Mise en évidence d'un problème

1 - On remarque que nos deux chaînes de caractères sont confondues: `bBoOnNjJoOuUrR,,  eEtT  bBiIeEnNvVeEnNuUeE  SsUuRr  VvOotTrReE  aAcCtTiIVviITtéé`

### Mise en place d'un mécanisme de protection

1 - Ce procédé s'appelle l'attente active (aussi appelé polling en anglais). Il faut l'éviter car il consomme des ressources inutilement en bouclant infiniment en attente d'une réponse. Ce procédé peut-être remplacé par l'envoi de signaux par exemple (dans un cas général, non spécifique au C). Par exemple, dans AngularJS, il est possible de `broadcast` un signal, identifié par un string, et de passer des données en paramètres. Dans un autre composant par exemple, il est possible d'exécuter une fonction lorsque le signal du `broadcast` est détecté. (Envoi de signaux en AngularJS)[http://www.dotnettricks.com/learn/angularjs/understanding-emit-broadcast-and-on-in-angularjs]

2 - Cela permet généralement de résoudre le problème, mais pas parfaitement. En effet, cela résout le problème lorsque les deux threads ne s'éxecutent pas en même temps. Si par exemple dans notre main, nous mettons:
```
sleep(1);
busy = 0;
```
Les deux threads vont s'exécuter en même temps, et nous aurons, dans notre cas, la première lettre des deux threads affichée, puis le dernier à avoir effectué le changement de variable `busy` terminera son exécution.
