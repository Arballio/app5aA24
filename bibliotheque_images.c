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
int MetaParser(char *strIN,char *strOUT, int pos)
{
	//memset(strOUT,0,sizeof(1024*8));

	int i = 0;

	while(pos != 0)
	{
		do{i++;}while(strIN[i] != ';' && strIN[i] != '\0');

			pos--;
	}

	i++;
	int j =0;
	while(strIN[i] != 0 && strIN[i] !=';' &&strIN[i] !='\n')
	{
			strOUT[j] = strIN[i++]; j++;

	}

	strOUT[++j] = 0;
	//printf("\n\n%s, %d, %s ",strIN,pos,strOUT);

	if(strOUT[0] == 0)
	{
		return ERREUR_FORMAT;
	}
	else{
		return OK;
	}
}



/********************************************************************/
//						Fonction publique
/********************************************************************/

void PrintMatrix(int matrix[MAX_HAUTEUR][MAX_LARGEUR],int ligne, int col)
{
    printf("\n\r\t\[");               //Imprimer le début du tableau
    for(int i = 0,LigneMax = 0; i < ligne; i++)    // Augmenter i pendant que i est plus petit que la taille en n des matrices
    {
        for(int j = 0; j< col;j++)  // Augmenter j pendant que j est plus petit que la taille en n des matrices
        {
        	if((LigneMax>21))
				{
					printf("]\n[");                  //Imprimer la fin de la rangée
					LigneMax = 0;
				}
           printf("%d, ",matrix[i][j]); //Imprimer l'élément de la matrice à la position i,j
			LigneMax++;
        }
    }
    printf("]\n");

}

void PrintRGBMatrix(struct RGB matrix[MAX_HAUTEUR][MAX_LARGEUR],int ligne, int col)
{
    printf("\n");
    for(int i = 0; i < ligne; i++)    // Augmenter i pendant que i est plus petit que la taille en n des matrices
    {
        printf("\r\t\[");               //Imprimer le début d'une rangée

        for(int j = 0,color = 0; j< col;)  // Augmenter j pendant que j est plus petit que la taille en n des matrices
        {
            //Imprimer l'élément de la matrice à la position i,j
        if(color == 0){
						printf("%d, ",matrix[i][j].valeurR);
						color++;
					}else if(color == 1){
					printf("%d, ",matrix[i][j].valeurG);
					color++;
					}else{
					printf("%d, ",matrix[i][j].valeurB);
					color = 0;
					j++;
					}
        }
        printf("]\n");                  //Imprimer la fin de la rangée
    }
}


int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR],
			 int *p_lignes, int *p_colonnes,
			 int *p_maxval, struct MetaData *p_metadonnees)
{
	int status = ERREUR, meta = 0;
	char tempbuffer[MAX_HAUTEUR] = {0};

	FILE *fp = fopen(nom_fichier, "r");

	memset(p_metadonnees->auteur,0,sizeof(p_metadonnees->auteur)); //Reinitialise les tableaux au cas ou
	memset(p_metadonnees->dateCreation,0,sizeof(p_metadonnees->dateCreation));
	memset(p_metadonnees->lieuCreation,0,sizeof(p_metadonnees->lieuCreation));

	if (fp == NULL) {
			fclose(fp);
	   return ERREUR_FICHIER;
	} else {
		//Gestion metadata
		while (meta < 3) {

			if(fgets(tempbuffer, sizeof(tempbuffer), fp) == NULL){break;}

			if(tempbuffer[0] == '#'){

				status = MetaParser(tempbuffer,p_metadonnees->auteur,0);
					if(status < 0)return status;
				status = MetaParser(tempbuffer,p_metadonnees->dateCreation,1);
					if(status < 0)return status;
				status = MetaParser(tempbuffer,p_metadonnees->lieuCreation,2);
					if(status < 0)return status;

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

				*p_colonnes = atoi(temp2);
				memset(temp2,0,sizeof(temp2));

				while(tempbuffer[i] != ' ' && tempbuffer[i] != 0)
				{
					temp2[j++] = tempbuffer[i];
					i++;

					if(i>10000)break;
				}
				*p_lignes = atoi(temp2);

				if(*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
					{
					 return ERREUR_TAILLE;
					}


				meta++;
			}
			else if(meta == 2)
			{
				*p_maxval = atoi(tempbuffer);
				status = OK;
				meta++;

			}
			else{
				return ERREUR_FORMAT;
			}
		memset(tempbuffer,0,sizeof(tempbuffer));
		}

		//Gestion tableau
		int i = 0,L = 0,C = 0;
		char temp[20] = {0};

		if(fgets(tempbuffer, sizeof(tempbuffer), fp) == NULL){}
		else{
				while(1)
			{
				int j = 0;

				while(tempbuffer[i] != ' ' && tempbuffer[i] != '\n' && tempbuffer[i] != '\r'&& tempbuffer[i] != '\0')//section un nombre ascii dans la ligne lu du fichier
				{
						temp[j++] = tempbuffer[i++];
				}

				i++;

				if(tempbuffer[i]== '\n' || tempbuffer[i]== '\0' || tempbuffer[i]== '\r')//Si fin de ligne, lit une prochaine
					{
						memset(tempbuffer,0,sizeof(tempbuffer));
						fgets(tempbuffer, sizeof(tempbuffer), fp);
						i = 0;
					}

				if(L < *p_lignes)//Remplie la matrice
				{
					if(C<*p_colonnes){
						matrice[L][C++] = atoi(temp);
					}else{
						matrice[++L][C=0] = atoi(temp);
						C++;
					}
				}
				else if(tempbuffer[i] == '\0')//Fin du fichier/matrice pleine
				{
					//PrintMatrix(matrice,*p_lignes,*p_colonnes);
					fclose(fp);
					return OK;
				}
				else
				{
						break;
				}

				memset(temp,0,sizeof(temp));


			}
		}

		memset(tempbuffer,0x0,sizeof(tempbuffer));
	}

	PrintMatrix(matrice,*p_lignes,*p_colonnes);

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
			fprintf(fp,"#%s;%s;%s\n",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
		}
		fprintf(fp,"P2\n");
		fprintf(fp,"%d %d\n",colonnes,lignes);
		fprintf(fp,"%d\n",maxval);

		for(int L = 0,LigneMax = 0; L < lignes; L++)    // Augmenter l pendant que l est plus petit que la taille en lignes des matrices
		{
			//fprintf(fp,"\r");               //Imprimer le début d'une rangée

			for(int C = 0; C< colonnes;C++)  // Augmenter c pendant que c est plus petit que la taille en colonnes des matrices
			{
				if((LigneMax>21))
				{
					fprintf(fp,"\n");                  //Imprimer la fin de la rangée
					LigneMax = 0;
				}

				fprintf(fp,"%d ",matrice[L][C]); //Imprimer l'élément de la matrice à la position l,c

				LigneMax++;

			}
			//fprintf(fp,"\n");
		}
	}


	fclose(fp);
	status = OK;

	return status;
}

int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	if(lignes1 == 0 || colonnes1 == 0)
		return ERREUR;

	*p_lignes2 = lignes1;
	*p_colonnes2 = colonnes1;

	for(int L = 0; L < lignes1; L++)    // Augmenter l pendant que l est plus petit que la taille en lignes des matrices
		{
			//fprintf(fp,"\r");               //Imprimer le début d'une rangée

			for(int C = 0; C< colonnes1;C++)  // Augmenter c pendant que c est plus petit que la taille en colonnes des matrices
			{
				matrice2[L][C] = matrice1[L][C];
			}
		}


	return OK;
}

int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
    int status = ERREUR;
    //int k = 0;
    for(int i = 0; i <= MAX_VALEUR;i++)     //Parcourir toutes les valeurs possible d'un pixel
    {
        for(int j = 0; j<lignes; j++)           //Parcourir toutes les valeurs possible d'une ligne
        {
            for(int n = 0; n<colonnes; n++)     //Parcourir toutes les valeurs possible d'une colonne
            {
                int m = matrice[n][j];

                if(m == i)
                {
                    histogramme[i] += 1;    //Augmenter la valeur du tableau histogramme lorsque i est égal
                }
            }
        }

    }
    status = OK;
    return status;
};

int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{
	int resultat = ERREUR, valeurComp = 0,couleur = 0;
	int histogramme[MAX_VALEUR+1] = {0};
	resultat = pgm_creer_histogramme(matrice,lignes,colonnes,histogramme);

	if(resultat <= 0)   //si l'histogramme ne retourne pas d'erreur
    {
         valeurComp = histogramme[0];
        for(int i = 0; i < MAX_VALEUR+1; i++) //Parcourir toutes les valeurs possible d'un
        {
            if(valeurComp<histogramme[i])       //Comparer la valeur précédente la plus élevée avec la valeur de l'histograme[i]
            {
                valeurComp = histogramme[i];
                couleur = i;
            }
        }
        resultat = couleur;
    }
    else{
        resultat = ERREUR;
    }

	return resultat;
}

int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
	int status = ERREUR;

	if(lignes == 0 || colonnes == 0){return status;}
        status = OK;
		for(int L = 0; L < lignes; L++)    // Augmenter l pendant que l est plus petit que la taille en lignes des matrices
		{
			//fprintf(fp,"\r");               //Imprimer le début d'une rangée

			for(int C = 0; C< colonnes;C++)  // Augmenter c pendant que c est plus petit que la taille en colonnes des matrices
			{
			    if((matrice[L][C]+valeur)>=maxval)
                {
                     matrice[L][C] = maxval ;       //Pixel est égal a la valeur max si le résultat est plus grand que valeurmax
                }
                else if((matrice[L][C]+valeur)<=0)
                {
                    matrice[L][C] = 0;                 //Pixel est égal a 0x si le résultat est plus petit que valeurmax
                }
                else
                {
                    matrice[L][C] = matrice[L][C]+valeur;   //Pixel est égal a la valeur initiale du pixel + valeur
                }
			}

		}
		return status;
}

int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
	int status = ERREUR;

	if(lignes == 0 || colonnes == 0){return status;}
    status = OK;
		for(int L = 0; L < lignes; L++)    // Augmenter l pendant que l est plus petit que la taille en lignes des matrices
		{
			//fprintf(fp,"\r");               //Imprimer le début d'une rangée

			for(int C = 0; C< colonnes;C++)  // Augmenter c pendant que c est plus petit que la taille en colonnes des matrices
			{
				matrice[L][C] = (maxval-matrice[L][C]);
			}
		}
		return status;
}

int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
	int status = ERREUR;

	int TempMat[MAX_HAUTEUR][MAX_LARGEUR] = {{0}};

	if(lignes1 < 0 || colonnes1 < 0 ||lignes1 > lignes2 || colonnes1 > colonnes2 || colonnes1 >= MAX_HAUTEUR
		|| lignes1 >= MAX_HAUTEUR || colonnes2 >= MAX_HAUTEUR || lignes2 >= MAX_HAUTEUR || colonnes1 >= *p_colonnes|| lignes1 >= *p_lignes
		|| colonnes2 >= *p_colonnes|| lignes2 >= *p_lignes){return status;}

		for(int L = lignes1,n=0; L <= lignes2; L++,n++)    // Augmenter l pendant que l est plus petit que la taille en lignes des matrices
		{
			for(int C = colonnes1,j=0; C<= colonnes2;C++,j++)  // Augmenter c pendant que c est plus petit que la taille en colonnes des matrices
			{
				TempMat[n][j] = matrice[L][C];
			}
		}

		//PrintMatrix(matrice,lignes2, colonnes2);

		*p_lignes = (lignes2-lignes1+1);
		*p_colonnes = (colonnes2-colonnes1+1);

		//PrintMatrix(TempMat,lignes2,colonnes2);
		status = OK;
	memset(matrice,0,sizeof(int)*(MAX_HAUTEUR)*(MAX_LARGEUR));
	//PrintMatrix(matrice,lignes2, colonnes2);

	memcpy(matrice,TempMat,sizeof(int)*(MAX_HAUTEUR)*(MAX_LARGEUR));
	//PrintMatrix(matrice,lignes2, colonnes2);
		return status;
}

int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	int status = DIFFERENTES;
	if((lignes1 == lignes2) && (colonnes1 == colonnes2))//si la taille des deux matrices sont identiques
    {
        for(int j = 0; j < lignes1; j++)    // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            for(int n = 0; n < colonnes2; n++)// Augmenter n pendant que n est plus petit que la taille en colonnes des matrices
            {
                if(matrice1[n][j] != matrice2[n][j])
                {
                    return status;      //Arrêter la boucle et retourner DIFFERENTES si la valeur n'est pas identique
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
    int k = *p_colonnes,temp;
    switch(sens)
    {
    default :
        status = ERREUR;    //Si le sens n'est pas bon
        break;

    case SENS_ANTIHORAIRE:      // si le sens est antihoraire
        for(int j = 0 ; j<*p_lignes; j++)   // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            k = *p_colonnes;
            for(int n = 0; n< *p_colonnes; n++) // Augmenter n pendant que n est plus petit que la taille en colonnes des matrices
            {
                k--;
                matriceTemp[k][j] = matrice[j][n];
            }
        }
         for(int j = 0; j<*p_lignes; j++)     // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            for(int n = 0; n<*p_colonnes; n++)// Augmenter n pendant que n est plus petit que la taille en colonnes des matrices
            {
                matrice[n][j] = matriceTemp[n][j]; //transferer la matrice tournée dans la matrice

            }
        }
        temp = *p_colonnes;
        *p_colonnes = *p_lignes; //Modifier la taille des colonnes et des lignes
        *p_lignes = temp;
        status = OK;
        break;

    case SENS_HORAIRE:  // si le sens est horaire
        k = *p_lignes;
         for(int j = 0 ; j<*p_lignes; j++)   // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            k--;
            for(int n = 0; n< *p_colonnes; n++)// Augmenter n pendant que n est plus petit que la taille en colonnes des matrices
            {
                matriceTemp[n][k] = matrice[j][n];
            }
        }
         for(int j = 0; j<*p_lignes; j++)     // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            for(int n = 0; n<*p_colonnes; n++)// Augmenter n pendant que n est plus petit que la taille en colonnes des matrices
            {
                matrice[n][j] = matriceTemp[n][j];  //transferer la matrice tournée dans la matrice

            }
        }
         temp = *p_colonnes;
        *p_colonnes = *p_lignes;    //Modifier la taille des colonnes et des lignes
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


	char tempbuffer[MAX_HAUTEUR+MAX_HAUTEUR+MAX_HAUTEUR] = {0};
	int meta = 0;


	FILE *fp = fopen(nom_fichier, "r");

	memset(p_metadonnees->auteur,0,sizeof(p_metadonnees->auteur));
	memset(p_metadonnees->dateCreation,0,sizeof(p_metadonnees->dateCreation));
	memset(p_metadonnees->lieuCreation,0,sizeof(p_metadonnees->lieuCreation));

	if (fp == NULL) {
			fclose(fp);
	   return ERREUR_FICHIER;
	} else {
		//Gestion metadata
		while (meta < 3) {

			if(fgets(tempbuffer, sizeof(tempbuffer), fp) == NULL){break;}

			if(tempbuffer[0] == '#'){

				status = MetaParser(tempbuffer,p_metadonnees->auteur,0);
					if(status < 0)return status;
				status = MetaParser(tempbuffer,p_metadonnees->dateCreation,1);
					if(status < 0)return status;
				status = MetaParser(tempbuffer,p_metadonnees->lieuCreation,2);
					if(status < 0)return status;
				//L++;

			} else if(tempbuffer[0] == 'P'){
				if(tempbuffer[1] == '3')
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

				*p_colonnes = atoi(temp2);
				memset(temp2,0,sizeof(temp2));

				while(tempbuffer[i] != ' ' && tempbuffer[i] != 0)
				{
					temp2[j++] = tempbuffer[i];
					i++;

					if(i>10000)break;
				}
				*p_lignes = atoi(temp2);

				meta++;
			}
			else if(meta == 2)
			{
				*p_maxval = atoi(tempbuffer);
				status = OK;
				meta++;
			}
			else{
				return ERREUR_FORMAT;
			}
		memset(tempbuffer,0,sizeof(tempbuffer));
		}


		if(*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
		{
		 return ERREUR_TAILLE;
		}
		//Gestion tableau

		//V2
		int i = 0,L = 0,C = 0,color = 0;
		char temp[20] = {0};

		if(fgets(tempbuffer, sizeof(tempbuffer), fp) == NULL){

		}
		else{
				while(1)
			{


			int j = 0;

			while(tempbuffer[i] != ' ' && tempbuffer[i] != '\n' && tempbuffer[i] != '\r'&& tempbuffer[i] != '\0')
            {
					temp[j] = tempbuffer[i];
					j++;i++;

					if(i>100)
						break;
            }

			i++;

			if(tempbuffer[i]== '\n' || tempbuffer[i+1]== '\0' || tempbuffer[i]== '\r')
				{
					memset(tempbuffer,0,sizeof(tempbuffer));
					fgets(tempbuffer, sizeof(tempbuffer), fp);
					i = 0;
				}

			if(L < *p_lignes)
			{
				if(C<*p_colonnes){
						if(color == 0){
							matrice[L][C].valeurR = atoi(temp);
							color++;
						}else if(color == 1){
						matrice[L][C].valeurG = atoi(temp);
						color++;
						}else{
						matrice[L][C].valeurB = atoi(temp);
						color = 0;
						C++;
						}
				}else{
					//C=0;
					if(color == 0){
							L++;
						matrice[L][0].valeurR = atoi(temp);
						color++;
					}else if(color == 1){
					matrice[L][0].valeurG = atoi(temp);
					color++;
					}else{
					matrice[L][0].valeurB = atoi(temp);
					color = 0;
					C= 1;
					}
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
	}

	fclose(fp);

	return status;
}

int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	int status = ERREUR;

	FILE *fp = fopen(nom_fichier, "w");

	if (fp == NULL) {
			fclose(fp);
	   return ERREUR_FICHIER;
	} else{
		if((metadonnees.auteur[0]) != '\0'){
			fprintf(fp,"#%s;%s;%s\n",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
		}
		fprintf(fp,"P3\n");
		fprintf(fp,"%d %d\n",colonnes,lignes);
		fprintf(fp,"%d\n",maxval);

		for(int L = 0,color = 0,LigneMax = 0; L < lignes; L++)    // Augmenter l pendant que l est plus petit que la taille en lignes des matrices
		{
			//fprintf(fp,"\r");               //Imprimer le début d'une rangée

			for(int C = 0; C< colonnes;)  // Augmenter c pendant que c est plus petit que la taille en colonnes des matrices
			{
				if((LigneMax>21))
				{
					fprintf(fp,"\n");                  //Imprimer la fin de la rangée
					LigneMax = 0;
				}

			   if(color == 0){
						fprintf(fp,"%d ",matrice[L][C].valeurR ); //Imprimer l'élément de la matrice à la position l,c couleur R
						color++;
					}else if(color == 1){
					fprintf(fp,"%d ",matrice[L][C].valeurG ); //Imprimer l'élément de la matrice à la position l,c couleur G
					color++;
					}else{
					fprintf(fp,"%d ",matrice[L][C].valeurB ); //Imprimer l'élément de la matrice à la position l,c couleur B
					color = 0;
					C++;
					}

					LigneMax++;
			}
			fprintf(fp,"\n");                  //Imprimer la fin de la rangée
		}
	}


	fclose(fp);

	status = OK;

	return status;

}

int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
    if(lignes1 == 0 || colonnes1 == 0)
    {
        return ERREUR;
    }
    else
    {
        *p_lignes2 = lignes1;
        *p_colonnes2 = colonnes1;

        for(int L = 0; L < lignes1; L++)    // Augmenter l pendant que l est plus petit que la taille en lignes des matrices
            {
                //fprintf(fp,"\r");               //Imprimer le début d'une rangée

                for(int C = 0; C< colonnes1;C++)  // Augmenter c pendant que c est plus petit que la taille en colonnes des matrices
                {
                    matrice2[L][C].valeurR = matrice1[L][C].valeurR;
                    matrice2[L][C].valeurG = matrice1[L][C].valeurG; //mettre la valeur du pixel de la matrice1 dans l'emplacement correspondant de la matrice2
                    matrice2[L][C].valeurB = matrice1[L][C].valeurB;
                }
            }
	return OK;
    }
}

int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	int status = DIFFERENTES;
	if((lignes1 == lignes2) && (colonnes1 == colonnes2))        //si la valeur des lignes et des colonnes sont identique
    {
        for(int j = 0; j < lignes1; j++)        // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            for(int n = 0; n < colonnes2; n++)  // Augmenter n pendant que n est plus petit que la taille en lignes des matrices
            {
                if((matrice1[n][j].valeurR != matrice2[n][j].valeurR)
                   ||(matrice1[n][j].valeurG != matrice2[n][j].valeurG)     //Arrêter la boucle et retourner DIFFERENTES si les valeur ne sont pas identique
                   ||(matrice1[n][j].valeurB != matrice2[n][j].valeurB))
                {
                    return status;
                }
            }
        }
        status = IDENTIQUES;//indiquer IDENTIQUE
    }

	return status;
}
int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	int status = ERREUR;
    int matriceTempR[MAX_HAUTEUR][MAX_LARGEUR],matriceTempG[MAX_HAUTEUR][MAX_LARGEUR],matriceTempB[MAX_HAUTEUR][MAX_LARGEUR];
    int k = *p_lignes,temp;
    switch(sens)
    {
    default :
        status = ERREUR;    // si le sens donné est erroné
        break;

    case SENS_ANTIHORAIRE:          // si le sens est Antihoraire

        for(int j = 0 ; j<*p_lignes; j++)       // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            k = *p_colonnes;
            for(int n = 0; n< *p_colonnes; n++) // Augmenter n pendant que n est plus petit que la taille en lignes des matrices
            {
                k--;
                matriceTempR[k][j] = matrice[j][n].valeurR;
                matriceTempG[k][j] = matrice[j][n].valeurG;
                matriceTempB[k][j] = matrice[j][n].valeurB;
            }
        }
         for(int j = 0; j<*p_lignes; j++)       // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            for(int n = 0; n<*p_colonnes; n++)  // Augmenter n pendant que n est plus petit que la taille en lignes des matrices
            {
                matrice[n][j].valeurR = matriceTempR[n][j];
                matrice[n][j].valeurG = matriceTempG[n][j];     //transferer la matrice tournée dans la matrice
                matrice[n][j].valeurB = matriceTempB[n][j];

            }
        }
         temp = *p_colonnes;
        *p_colonnes = *p_lignes;    //Modifier la taille des colonnes et des lignes
        *p_lignes = temp;
        status = OK;
        break;

    case SENS_HORAIRE:          // si le sens est horaire





         for(int j = 0 ; j<*p_lignes; j++)                  // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            k--;
            for(int n = 0; n< *p_colonnes; n++)             // Augmenter n pendant que n est plus petit que la taille en lignes des matrices
            {
                matriceTempR[n][k] = matrice[j][n].valeurR;
                matriceTempG[n][k] = matrice[j][n].valeurG;
                matriceTempB[n][k] = matrice[j][n].valeurB;
            }
        }
         for(int j = 0; j<*p_lignes; j++)                   // Augmenter j pendant que j est plus petit que la taille en lignes des matrices
        {
            for(int n = 0; n<*p_colonnes; n++)              // Augmenter n pendant que n est plus petit que la taille en lignes des matrices
            {
                matrice[n][j].valeurR = matriceTempR[n][j];
                matrice[n][j].valeurG = matriceTempG[n][j];     //transferer la matrice tournée dans la matrice
                matrice[n][j].valeurB = matriceTempB[n][j];

            }
        }
         temp = *p_colonnes;
        *p_colonnes = *p_lignes;            //Modifier la taille des colonnes et des lignes
        *p_lignes = temp;

        status = OK;
        break;
    }
	return status;
}

