# TP3 Programmation système

##  Sémaphores

### Utilisation de sémaphores non nommés

1 - On peut le partager à partir du processus père créant une variable globale.

2 - Il faut inclure `<semaphore.h>`

4 - Le même système ne fonctionne pas avec des forks.

### Utilisation de threads mutex

1 - Un sémaphore non-nommé ne peut être partagé qu'entre un processus père et ses fils. Ainsi, si un processus a plusieurs fils, seul la relation père-fils peut agir sur le sémaphore, tandis que la relation fils-fils n'a aucun impact.

2 - Cette application se prête au remplacement par un sémaphore nommé car nous avons besoin de la relation fils-fils.

### Utilisation de sémaphores nommés

1 - Un sémaphore nommé crée un fichier dans `/dev/shm`. Ce fichier est accessible en lecture et en écriture par n'importe quel processus de la machine.

2 - `/dev/shm`. Les sémaphores appartiennent à un utilisateur et son inaccessibles à l'écriture par d'autres utilisateurs.
