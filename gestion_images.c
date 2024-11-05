/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 28 octobre 2023
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

void PrintMatrix(int matrix[MAX_HAUTEUR][MAX_LARGEUR],int ligne, int col)
{
    printf("\n");
    for(int i = 0; i < ligne; i++)    // Augmenter i pendant que i est plus petit que la taille en n des matrices
    {
        printf("\r\t\[");               //Imprimer le début d'une rangée

        for(int j = 0; j< col;j++)  // Augmenter j pendant que j est plus petit que la taille en n des matrices
        {
           printf("%d, ",matrix[i][j]); //Imprimer l'élément de la matrice à la position i,j
        }
        printf("]\n");                  //Imprimer la fin de la rangée
    }
}


int main()
{
    int lignes1, colonnes1;
    int lignes2, colonnes2;
    int maxval;
    int histogramme[MAX_VALEUR+1];
    char nom[MAX_CHAINE];
    struct MetaData metadonnees;

	int retour;

    printf("-> Debut!\n");

	//strcpy(nom,"Sherbrooke_Frontenac_nuit.pgm");
	strcpy(nom,"testfile.pgm");

    retour = pgm_lire(nom, image1,
                      &lignes1, &colonnes1,
                      &maxval, &metadonnees);

	// exemple detraitement d'un code de retour (erreur ou reussite)
	printf("-> Retour: ");

	if (retour == OK){
		printf("-> OK\n\r");
		if((metadonnees.auteur[0]) != '\0'){
			printf("Auteur = %s, Date = %s, Lieu = %s\n\r",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);}
		printf("Line = %d, Colonne = %d\n\r",lignes1,colonnes1);
		printf("max value = %d",maxval);


		PrintMatrix(image1,lignes1,colonnes1);
	}else if(retour == ERREUR_FICHIER)
	{
		printf("-> ERREUR_FICHIER");
	}else
	{
		printf("-> ERREUR");
	}

	printf("\n");

	// autre exemple d'appel de fonction
    pgm_ecrire("test1.txt", image1,
               lignes1, colonnes1,
               maxval, metadonnees);

    printf("-> Fin!\n");

	char a;
    scanf("%c",&a);

    return 0;
}
