# TP4 Programmation système

## Mémoire partagée

### Utilisation de fichiers

1 - `open()`: ouvrir
    `read()`: lire
    `write()`: écrire
    `remove()`: Supprimer

2 - Le descripteur du fichier ouvert lorsque que le père exécute l’appel système fork() est le même

### Utilisation de mémoire partagée

1 - `shm_open()`: ouvre un objet mémoire partagé
    `ftruncate()`: allocation de mémoire
    `mmap()`: mappe l'objet
    `munmap()`: démappe l'objet
    `shm_close()`: ferme l'objet mémoire
    `shm_unlink()`: supprime le lien. Lorsque plus aucun lien n'existe, l'objet est supprimé

2 - `/dev/shm`

3 - Il faut ajouter les flags `S_IROTH` pour la lecture, et `S_IWOTH` pour l'écriture
    Exemple: `shm_open(<nom_fichier>, O_RDWR | O_CREAT, S_IROTH | S_IWOTH)`

4 - `msync()` met à jour le cache du fichier ouvert par notre processus.

5 - En utilisant des sémaphores

## Le problème des rédacteurs-lecteurs

1 - Le fichier reader.c contient le code du lecteur et writer.c celui du rédacteur.
    Jusque là, 1 seul rédacteur est implémenté. Lorsqu'il y a un seul lecteur, tout fonctionne correctement. Cependant, si nous ajoutons d'autres lecteurs, un seul d'entre eux 
