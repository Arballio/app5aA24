/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
		 Charles-Antoine Brunet
Date: 28 octobre 2023
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"


/********************************************************************/
//						Fonction privé
/********************************************************************/

//Cette fontion retire le premier token des metadatas. Commence a 0
void MetaParser(char *strIN,char *strOUT, int pos)
{
	int i = 0;

	while(pos != 0)
	{
		while(strIN[i] != ';'){i++;}

			pos--;
	}

	while(strIN[i] != 0 && strIN[i] !=';')
	{
		int j =0;

			strOUT[j] = strIN[i++]; j++;

	}

}



/********************************************************************/
//						Fonction publique
/********************************************************************/
int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR],
			 int *p_lignes, int *p_colonnes,
			 int *p_maxval, struct MetaData *p_metadonnees)
{	int status = ERREUR;


	char tempbuffer[MAX_HAUTEUR] = {0};

	FILE *fp = fopen(nom_fichier, "r");
	int meta = 0;

	if (fp == NULL) {
			fclose(fp);
	   return ERREUR_FICHIER;
	} else {
		//Gestion metadata
		while (meta < 3) {

			if(fgets(tempbuffer, sizeof(tempbuffer), fp) == NULL){break;}

			if(tempbuffer[0] == '#'){

				MetaParser(tempbuffer,p_metadonnees->auteur,1);
				MetaParser(tempbuffer,p_metadonnees->dateCreation,2);
				MetaParser(tempbuffer,p_metadonnees->lieuCreation,3);
				//L++;

			} else if(tempbuffer[0] == 'P'){
				if(tempbuffer[1] == '2')
				{
					//Fichier PGM ok
				}else {return ERREUR_FORMAT;}

				meta++;
			}
			else if(meta == 1){
					char temp2[10] ={0};
					int i = 0,j=0;

					while(tempbuffer[i] != ' ' && tempbuffer[0] != '\n'){temp2[i] = tempbuffer[i];i++;}

					i++;

				*p_lignes = atoi(temp2);
				memset(temp2,0,sizeof(temp2));

				while(tempbuffer[i] != ' ' && tempbuffer[i] != 0)
				{
					temp2[j++] = tempbuffer[i];
					i++;

					if(i>10000)break;
				}
				*p_colonnes = atoi(temp2);

				meta++;
			}
			else if(meta == 2)
			{
				*p_maxval = atoi(tempbuffer);
				status = OK;
				meta++;

			}
		memset(tempbuffer,0,sizeof(tempbuffer));
		}

		//Gestion tableau

		//V2
		int i = 0,L = 0,C = 0;
		char temp[20] = {0};

		if(fgets(tempbuffer, sizeof(tempbuffer), fp) == NULL){

		}
		else{
				while(1)
			{


			int j = 0;

			while(tempbuffer[i] != ' ' && tempbuffer[i] != '\n' && tempbuffer[i] != '\r')
            {
					temp[j] = tempbuffer[i];
					j++;i++;
            }

			i++;

			if(tempbuffer[i]== '\n' || tempbuffer[i+1]== '\n' || tempbuffer[i]== '\r')
				{
					memset(tempbuffer,0,sizeof(tempbuffer));
					fgets(tempbuffer, sizeof(tempbuffer), fp);
					i = 0;
				}

			if(L < *p_lignes)
			{
				if(C<*p_colonnes){
					matrice[L][C] = atoi(temp);
					C++;
				}else{
					C=0;
					L++;
					matrice[L][C] = atoi(temp);
					C++;
				}
			}
			else if(tempbuffer[i] == '\0')//Fin du fichier
			{
				return OK;
			}
			else
			{
					break;
			}

			memset(temp,0,sizeof(temp));


			}
		}

		memset(tempbuffer,0x30,sizeof(tempbuffer));

        //V1
		/*for(int R = 0;R<(*p_lignes);R++)
			{
				for(int L = 0;L<*p_colonnes;L++)
				{
					//tempbuffer[0] = fgetc(fp);

					for(int i = 0; 0x29 <tempbuffer[i] && tempbuffer[i]<0x40 ;i++){
						tempbuffer[i] = fgetc(fp);
					}

					fgetc(fp);

					matrice[R][L] = atoi(tempbuffer);
					memset(tempbuffer,0x30,sizeof(tempbuffer));
				}
			}*/


	//status = OK;
	}

	fclose(fp);

	return status;
}

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR],
			   int lignes, int colonnes,
			   int maxval, struct MetaData metadonnees)
{
	int status = ERREUR;

	FILE *fp = fopen(nom_fichier, "w");

	if (fp == NULL) {
			fclose(fp);
	   return ERREUR_FICHIER;
	} else{
		if((metadonnees.auteur[0]) != '\0'){
			fprintf(fp,"%s %s %s\n",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
		}
		fprintf(fp,"P2\n");
		fprintf(fp,"%d %d\n",lignes,colonnes);
		fprintf(fp,"%d\n",maxval);

		for(int L = 0; L < lignes; L++)    // Augmenter l pendant que l est plus petit que la taille en lignes des matrices
		{
			//fprintf(fp,"\r");               //Imprimer le début d'une rangée

			for(int C = 0; C< colonnes;C++)  // Augmenter c pendant que c est plus petit que la taille en colonnes des matrices
			{
			   fprintf(fp,"%d ",matrice[C][C]); //Imprimer l'élément de la matrice à la position l,c
			}
			fprintf(fp,"\n");                  //Imprimer la fin de la rangée
		}
	}


	fclose(fp);
	status = OK;

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
    //int k = 0;
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

int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)//#TODO
{
	int status = ERREUR;

	return status;
}

int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)//#TODO
{
	int status = ERREUR;

	return status;
}

int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)//#TODO
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

