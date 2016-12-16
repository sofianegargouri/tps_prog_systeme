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

#ifndef _LECT_RED_H_
#define _LECT_RED_H_

/** Noms des fichiers spéciaux associés aux objets du noyau
 *  !!! doivent être modifiés si utilisation d’un serveur commun à plusieurs étudiants
 */
#define SEM_RED_NAME    "sem_red"
#define SEM_LECT_NAME   "sem_lect"
#define MUTEX_NAME      "mutex"
#define MMAP_NAME       "mapping"

/** Nombre de "cases" du tampon partagé par les processus lecteurs
 *  et rédacteurs
 */
#define     FIFO_SIZE       5

/** Nombre de processus lecteurs (lecteurs)             */
#define     NB_LECT     3

/** Dernière valeur écrite (par l'un des rédacteurs) et lue par
 *  chaque lecteur
 */
#define     VALEUR_FIN      25

/** Structure du tampon partagé par les rédacteurs et les lecteurs
 *  Note: les deux premières composantes ne sont réellement utiles
 *      que dans le cas où il y a plusieurs rédacteurs
 */
typedef struct {
    int  next_index;     /* indice de la prochaine case à remplir   */
    int  next_value;     /* prochaine valeur à écrire               */
    int  buff[VALEUR_FIN];/* le buffer                       */
} buffer_t;


/** Variante de la macro CHECK définie dans les TP précédents.
 *  Lorsque stat vaut val alors l'opération dont le résultat
 *  est stat, a échoué.
 *  Pour la plupart des appels système Posix, la valeur signalant
 *  l'échec est -1. Elle correspond à NULL lorsque l'appel système
 *  retourne un pointeur.
 */
#ifdef  _DEBUG
#define CHECK_IF(stat, val, msg)    \
    if ( (stat) == (val) )      \
    {                               \
            perror(msg);            \
        exit( EXIT_FAILURE );   \
      }  \
      else printf("%s ... OK\n", msg)
#else
#define CHECK_IF(stat, val, msg)    \
    if ( (stat) == (val) )          \
    {                           \
            perror(msg);            \
        exit( EXIT_FAILURE );   \
    }
#endif
#endif
