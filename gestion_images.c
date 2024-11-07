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

int main()
{
	//AutoValidation();
    test_pgm_pivoter90();
    test_ppm_pivoter90();
    //test_pgm_creer_negatif();
    return 0;
}
