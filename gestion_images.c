/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 28 octobre 2023
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include "bibliotheque_images.h"
#include "AutoValidation.h"
int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];


#define SELFTEST 0
int main()
{
	#if !(SELFTEST)
	//test_ppm_lire();
	AutoValidation();
	//test_pgm_ecrire();
	//test_pgm_lire();
	#endif




	#if SELFTEST
    int lignes1 = 0, colonnes1 = 0;
    int lignes2 = 0, colonnes2 = 0;
    int maxval = 0;
    int histogramme[MAX_VALEUR+1] = {0};
    char nom[MAX_CHAINE] = {0};
    struct MetaData metadonnees = {0};;

	int retour;

    printf("-> Debut!\n");

	//strcpy(nom,"Sherbrooke_Frontenac_nuit.pgm");
	strcpy(nom,"images/validation.pgm");

	//strcpy(nom,"testfile.pgm");

    retour = pgm_lire(nom, image1,
                      &lignes1, &colonnes1,
                      &maxval, &metadonnees);



	printf("-> Retour: ");

	if (retour == OK){
		printf("-> OK\n\r");
		if((metadonnees.auteur[0]) != '\0'){
			printf("Auteur = %s, Date = %s, Lieu = %s\n\r",
                metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);}
		printf("Line = %d, Colonne = %d\n\r",lignes1,colonnes1);
		printf("max value = %d",maxval);


		//PrintMatrix(image1,lignes1,colonnes1);

		//pgm_copier(image1,lignes1,colonnes1,image2,&lignes2,&colonnes2);

		pgm_ecrire("OUTLECTURE.pgm", image1,
					lignes1, colonnes1,
					maxval, metadonnees);

	}else if(retour == ERREUR_FICHIER)
	{
		printf("-> ERREUR_FICHIER");
	}else
	{
		printf("-> ERREUR");
	}

	/********************Test pour ppm
	strcpy(nom,"Sherbrooke_Frontenac_nuit.ppm");
	//strcpy(nom,"testfile.ppm");

	retour = ppm_lire(nom, imageRGB1,
                      &lignes1, &colonnes1,
                      &maxval, &metadonnees);

		PrintRGBMatrix(imageRGB1,lignes1,colonnes1);


	printf("-> Retour: ");

	if (retour == OK){
		printf("-> OK\n\r");
		if((metadonnees.auteur[0]) != '\0'){
			printf("Auteur = %s, Date = %s, Lieu = %s\n\r",
                metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);}
		printf("Line = %d, Colonne = %d\n\r",lignes1,colonnes1);
		printf("max value = %d",maxval);

		ppm_copier(imageRGB1,lignes1,colonnes1,imageRGB2,&lignes2,&colonnes2);

		ppm_ecrire("test2.ppm", imageRGB2,
					lignes2, colonnes2,
					maxval, metadonnees);

		ppm_ecrire("test.ppm",imageRGB1,lignes1,colonnes1,maxval,metadonnees);

	}else if(retour == ERREUR_FICHIER)
	{
		printf("-> ERREUR_FICHIER");
	}else
	{
		printf("-> ERREUR");
	}
	/************************/

	printf("\n");



   #endif // SELFTEST

printf("-> Fin!\n Press enter to continue.");
	char a;
   scanf("%c",&a);

    return 0;
}
