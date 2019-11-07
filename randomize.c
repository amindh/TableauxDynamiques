/*! \file randomize.c
 *
 * Auteur  : Xavier Serpaggi
 * Date    : 15/09/2017
 *
 * Génère des nombres aléatoires et les stocke dans un fichier
 * dont le nom est passé en paramètre ('-' signifie stdout).
 *
 * Les nombres ont des valeurs dans l'intervalle [-1000;1000[.
 *
 * Le nombre de valeurs par défaut est 1000000. Si on veut un
 * nombre différent, on passe un second paramètre au programme.
 *
 *
 * Pour compiler ce fichier il faut utiliser la commande suivante
 *
 * gcc -W -Wall -pedantic -o randomize randomize.c utils.c
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define NB_NB (1000000L)

/*! fonction affichant l'aide en cas de problème.
 *
 *  \param argc et argv sont les paramètres reçus par main.
 *  \param msg est un message à afficher ou NULL.
 */
void usage(int argc, char **argv, char *msg) {
		if ( msg != NULL) {
			fprintf(stderr, "%s\n", msg) ;
			fprintf(stderr, "\n") ;
		}

		if ( argc < 0 ) return ; /* test pour éviter que le compilateur ne se plaigne... */

		fprintf(stderr, "%s <fichier> [nb vals]\n", argv[0]) ;
		fprintf(stderr, "  <fichier> ne doit pas exister.\n") ;
		fprintf(stderr, "  De plus, si <fichier> est le caractère - la sortie se fait sur la sortie standard.\n") ;
}


int main(int argc, char *argv[])
{
	FILE *f ;
	unsigned long i, nb ;
	char *endptr ;
	char err ;

	/* Il n'y a pas assez d'argument sur la ligne de commande */
	if ( argc < 2 ) {
		usage(argc, argv, "Nom de fichier manquant.") ;

		return 1 ;
	}

	/* Est-ce que le fichier est l'argument spécial '-' ?
	 * Auquel cas, on doit afficher sur la console et non pas écrire dans un fichier.
	 */
	if ( strncmp("-", argv[1], 1) == 0 ) {
		f = stdout ;
	} else {
		f = fopen(argv[1], "wx") ; /* x : extension GNU pour ne pas écraser un fichier existant */
		if ( f == NULL ) {
			usage(argc, argv, "Impossible d'ouvrir le fichier.") ;
			return 2 ;
		}
	}

	/* L'utilisateur a-t-il passé un nombre en paramètre ?
	 * Et ce nombre est-il valide ?
	 */
	nb = NB_NB ;
	if ( argc > 2 ) {
		/* On tente de transformer la chaine de caractère représentant un nombre en
		 * ce nombre. On fait l'hypothèse qu'il est exprimé en base 10 !
		 */
		nb = strtoul(argv[2], &endptr, 10) ;
		
		err = 0 ;
		if ((errno == ERANGE && nb == LONG_MAX)||(errno != 0 && nb == 0)) {
			perror("strtoul");
			/*
			exit(EXIT_FAILURE);
			*/
			err = 1 ;
		}

		if (endptr == argv[2]) {
			fprintf(stderr, "Aucun nombre trouvé.\n");
			/*
			exit(EXIT_FAILURE);
			*/
			err = 1 ;
		}
		if ( err == 1 ) nb = NB_NB ;
	}
	
	/* Tout semble en ordre, il n'y a plus qu'à générer les nombres ...
	 * On dit ce que l'on fait.
	 */
	fprintf(stderr, "Génération de %lu nombres dans le fichier %s ...\n", nb, argv[1]) ;

	/* Initialisation du générateur aléatoire pour avoir des séquences différentes
	 * à chaque exécution du programme.
	 */
	srand(time(NULL)) ;

	for ( i = 0 ; i < nb ; i++ ) {
		/* La fonction rand_ab_f est définie dans le fichier utils.c
		 * et son prototype se trouve dans le fichier utils.h.
		 */
		fprintf(f, "%.6f\n", rand_ab_f(-1000,1000)) ;
	}

	/* Enfin, on n'oublie pas de rendre le fichier au système d'exploitation.
	 */
	fclose(f) ;
	
	return 0 ;
}
