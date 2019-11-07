#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>

/* Déclaration de la structure */
struct dtab{
     
	double * tab;
    
	unsigned int tailleT;
    
	unsigned int capacite;
};


/* ******* FONCTIONS ******** */

struct dtab * dtab_new(unsigned int capa)/*La fonction alloue un nouveau tableau et renvoie une reference vers la structure */
{
	struct dtab* T = malloc(sizeof(struct dtab)); /* pointeur */
	T->tab = malloc(sizeof(double) * capa);   /* allocation de la mémoire */
	T->capacite =capa ;
	T->tailleT = 0; /* initialisation de la taille à 0 */
	return T;
}


int dtab_add(struct dtab *T,double val){ /* fonction qui ajoute val a la fin du tableau et renvoie sa position*/

	if (T->tailleT >= T->capacite) { /* si la capacité n'est pas suffisante on réalloue de la mémoire*/
		T->tab = realloc(T->tab, ((T->capacite + 1) * sizeof(double)));
		T->capacite = T->capacite + 1;
	}
	T->tab[T->tailleT] = val;      /* le premier indice du tableau sera 0*/
	T->tailleT = T->tailleT + 1;
	return T->tailleT;
}

double dtab_get(struct dtab *T,unsigned int i ) /*obtenir la valeur d'indice i, le tableau commence à l'indice 0*/
{
	if (i > T->tailleT) {
		printf("l'indice n'appartient pas au tableau\n");
		return(0);
	}
	else {
		return T->tab[i];
	}
}


void dtab_set(struct dtab *T,unsigned int i, double val) { /* permet d'affecter val à la cellule d'indice i*/
	if (i<T->tailleT){
		T->tab[i] = val;
	}
	else {
		printf("l'indice n'appartient pas au tableau\n");
	}
}


void dtab_remove(struct dtab *T, unsigned int i){ /*supprime la cellule d'indice i du tableau*/
	unsigned int k;
	if( i > T->tailleT ) { /*On verifie que l'indice i n'est pas plus grand que la taille du tableau */
		printf("l'indice n'appartient pas au tableau");
		exit(0) ;
	}
	for (k = i; k < T->tailleT; k++) { /*décalage des élements en "ecrasant" celle d'indice i */
		T->tab[k] = T->tab[k + 1];
		}
	T->tailleT = T->tailleT - 1;
}


void dtab_sort(struct dtab *T) { /* tri du tableau par ordre croissant*/
	unsigned int i, j;
	for (i =1; i< T->tailleT; i++) {      /* on applique le tri par insertion*/
		int cle = T->tab[i];
		for (j = i; j > 0 && T->tab[j - 1] > cle; j--) {
			T->tab[j] = T->tab[j - 1];
      		}
		T->tab[j] = cle;
   	}
}


int dtab_insert(struct dtab * T, double val)   /*insère l'élément val à la bonne place dans un tableau trié*/
{

	unsigned int i = T->tailleT;
	if( T -> tailleT >= T->capacite ) /*on vérifie qu'on ne dépasse pas la taille allouée*/
	{
		T->tab = realloc(T->tab, ((T->capacite + 1) * sizeof(double)));
		T->capacite = T->capacite + 1;

	}

	for (i=T->tailleT ; (i>0)&&(T->tab[i-1]>val) ; i--)
       	{	
		T->tab[i] = T->tab[i - 1];  /*on décale les élements */
	}
	T->tab[i] = val;
	T->tailleT = T->tailleT + 1;
	return i;
}



void dtab_free(struct dtab *T){ /* détruit le tableau dynamique et libère la mémoire allouée */
	free(T->tab);
	free(T);
}

	

void affiche(struct dtab *T) /*affichage du tableau*/
{
	unsigned int i; 
	for (i = 0; i < T->tailleT; i++)
	{
		printf("%lf\n", T->tab[i]);
	}
}

double moyenne(struct dtab *T) /* Calcul la valeur moyenne du tableau */
{ 
	unsigned int i;
	double S ;
	S=0;
	for (i = 0; i < T->tailleT; i++) {
		S = T->tab[i] + S;
	}
	return S / T->tailleT;
}


void extrema (struct dtab *T, double *min, double *max)  /* Retourne la valeur maximale et minimale  du tableau  */
{ 
	double val_min = T->tab[0];
	double val_max = T->tab[0];
	unsigned int i;
	for(i = 0; i < T->tailleT; i++){
		if (T->tab[i] < val_min){	/*recherche du min */
			val_min = T->tab[i];
			}
		else if (T->tab[i] > val_max){ /* recherche du max*/
			val_max = T->tab[i];
			}
	*max = val_max;	
	*min = val_min;
	}
}

float Ecarttype(struct dtab *T) /*Fonction qui calcule l'écart type des éléments du tableau*/
{
   	unsigned int i;
	double moy = moyenne(T);
   	float ecarttype;
	double s = 0;
   	for (i=0;i<T->tailleT;i++)
   	{
		s = s + (T->tab[i] - moy) * (T->tab[i] - moy);
   	}
	ecarttype = sqrt(s / T->tailleT); /* s/taille est la variance */
   	return ecarttype;
   				  
}





/* *************************** */




int main() /*Fonction principale qui affiche les résultats des fonctions précédentes*/
{

	printf("PARTIE 2: TABLEAUX DYNAMIQUES\n\n");


   	/*Déclaration des variables utilisées*/
	
	struct dtab *T;
   	char Fichier[20];
   	unsigned int i;
   	double moy;
   	double min;
   	double max;
   	float ecarttype;


	T=dtab_new(1);      /*Création du tableau dynamique de capacité 1, la fonction dtab_add allouera de l'espace si besoin*/
				                     
   	
	/*Demande et ouverture du fichier*/

	FILE* fichier = NULL;
	printf("Veuillez entrer le nom du fichier: ");
	scanf("%s", Fichier);
	fichier = fopen(Fichier, "r");    /* On ouvre le fichier */
   	
	if(fichier == NULL) /*test d'ouverture du fichier*/
   	{
		printf("Problème d'ouverture du fichier");
   	}
   	else
   	{
		char line [100];
		while ( fgets(line, sizeof line, fichier) != NULL) /*On ajoute l'élement de chaque ligne dans le fichier à notre tableau T*/
		{	
		            
			dtab_add(T, atof(line));
        	}
	}
   	fclose(fichier);  /*fermeture du fichier*/
	
   	
	FILE* fsortie = NULL; /* Fichier réutilisable par l'utilisateur */
	fsortie = fopen("resultats.txt", "w+"); /* ecriture et lecture dans le fichier */
	printf("\n\nAffichage du tableau trié\n");
	fprintf(fsortie, "%s\n\n", "Affichage du tableau trié avant modification\n");
	dtab_sort(T);    /*on tri le tableau*/

	for (i = 0; i < T->tailleT; i++) /* on affiche les valeurs et on les écrit dans le fichier de sortie*/
   	{
		printf("%f\n", T->tab[i]);
		fprintf(fsortie, "%f\n", T->tab[i]);
   	}
   
     
   
/*ANALYSE STATISTIQUE*/   

	moy = moyenne(T);
	ecarttype = Ecarttype(T);
	extrema(T, &min, &max);
	
/*On affiche les données statistiques dans la console*/
	printf("\nANALYSE STATISTIQUE:\n\n");
   	printf("\nLa moyenne est: %f\n", moy);
   	printf("\nL'ecart-type est: %f\n", ecarttype);
   	printf("\nLe min est: %f\n",min );
   	printf("\nLe max est: %f\n\n",max);
   	
/*On écrit dans le fichier de sortie les données statistiques*/
	fprintf(fsortie, "\n\n%s\n\n", "ANALYSE STATISTIQUE");
   	
	fprintf(fsortie, "%s\n", "La moyenne est:");
	fprintf(fsortie, "%f\n\n", moy);
       
	fprintf(fsortie, "%s\n", "Le min est:");
	fprintf(fsortie, "%f\n\n", min);
	fprintf(fsortie, "%s\n", "Le max est:");
	fprintf(fsortie, "%f\n\n", max);
     
	fprintf(fsortie, "%s\n", "L'ecart-type est:");
	fprintf(fsortie, "%f\n\n", ecarttype);
   	


/*OPERATIONS SUPPLEMENTAIRES*/

	printf("\n\nOPERATION SUPPLEMENTAIRE\n\n");
	
	/*Afficher une valeur du tableau*/

	int position;
	printf("AFFICHER UNE VALEUR : A quelle position voulez-vous consulter une valeur ? ");
	scanf("%d", &position);
	double ValeurDemandee = dtab_get(T, position);
	printf("Valeur demandee : %f\n\n", ValeurDemandee);

	/*Remplacer une valeur du tableau*/

	double new;
	printf("REMPLACER UNE VALEUR : Par quelle valeur voulez-vous la remplacer ? ");
	scanf("%lf", &new);
	dtab_set(T, position, new);
	printf("Nouvelle valeur de la case %d : %f\n\n", position, T->tab[position]);

	/*Inserer une valeur au tableau*/

	double valinsert;
	printf("INSERER UNE VALEUR : Quelle valeur voulez-vous inserer ? ");
	scanf("%lf", &valinsert);
	dtab_insert(T, valinsert);
	printf("\n");
	
/*On affiche le nouveau tableau après insertion et remplacement*/

	printf("\n\nAffichage du tableau modifié\n\n");
	affiche(T);
	fprintf(fsortie, "\n\n%s\n\n", "Affichage du tableau modifié et trié");
	dtab_sort(T);
	for (i = 0; i < T->tailleT; i++)
   	{
		fprintf(fsortie, "%f\n", T->tab[i]);
   	}
	


	dtab_free(T); /* On libère la mémoire allouée*/
   	fclose(fsortie); /* on ferme le fichier de sortie*/
   	return 0;

}
