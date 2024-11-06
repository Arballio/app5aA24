/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
		 Charles-Antoine Brunet
Date: 28 octobre 2023
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"



int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR],
			 int *p_lignes, int *p_colonnes,
			 int *p_maxval, struct MetaData *p_metadonnees)
{	int status = ERREUR;


	FILE *fp = fopen(nom_fichier, "r");

	if (fp == NULL) {
	   return -1;
	}


	return status;
}

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR],
			   int lignes, int colonnes,
			   int maxval, struct MetaData metadonnees)
{
	int status = ERREUR;


	return status;
}

int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	int status = ERREUR;

	return status;
}

int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
    int status = ERREUR;
    int k = 0;
    for(int i = 0; i <= MAX_VALEUR;i++)
    {
        for(int j = 0; j<lignes; j++)
        {
            for(int n = 0; n<colonnes; n++)
            {
                int m = matrice[n][j];

                if(m == i)
                {
                    histogramme[i] += 1;
                }
            }
        }

    }
    status = OK;
    return status;
};

int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{
	int status = ERREUR;

	return status;
}

int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
	int status = ERREUR;

	return status;
}

int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
	int status = ERREUR;

	return status;
}

int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
	int status = ERREUR;

	return status;
}

int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	int status = DIFFERENTES;
	if((lignes1 == lignes2) && (colonnes1 == colonnes2))
    {
        for(int j = 0; j < lignes1; j++)
        {
            for(int n = 0; n < colonnes2; n++)
            {
                if(matrice1[n][j] != matrice2[n][j])
                {
                    return status;
                }
            }
        }
        status = IDENTIQUES;
    }

	return status;
}

int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	int status = ERREUR;
    int matriceTemp[MAX_HAUTEUR][MAX_LARGEUR];
    int k = *p_colonnes;
    switch(sens)
    {
    default :
        status = ERREUR;
        break;

    case SENS_ANTIHORAIRE:

        for(int j = 0; j<*p_lignes; j++)
        {
            for(int n = 0; n<*p_colonnes; n++)
            {
                matriceTemp[n][j] = matrice[j][n];

            }
        }

        for(int j = 0; j<*p_lignes; j++)
        {
            for(int n = 0; n<*p_colonnes; n++)
            {
                matrice[n][j] = matriceTemp[n][j];

            }
        }
        status = OK;
        break;

    case SENS_HORAIRE:

         for(int j ; j<*p_lignes; j++)
        {
            k--;
            for(int n = 0; n< *p_colonnes; n++)
            {
                matriceTemp[n][k] = matrice[j][n];
            }
        }
         for(int j = 0; j<*p_lignes; j++)
        {
            for(int n = 0; n<*p_colonnes; n++)
            {
                matrice[n][j] = matriceTemp[n][j];

            }
        }
        int temp;
         temp = *p_colonnes;
        *p_colonnes = *p_lignes;
        *p_lignes = temp;

        status = OK;
        break;
    }
	return status;
}

// Operations pour les images couleurs
int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
	int status = ERREUR;

	return status;
}

int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	int status = ERREUR;

	return status;
}

int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	int status = ERREUR;

	return status;
}

int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	int status = ERREUR;

	return status;
}

int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	int status = ERREUR;

	return status;
}

