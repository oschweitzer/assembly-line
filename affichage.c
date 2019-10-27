#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"

//Fonction qui permet d'afficher l'anneau
void affiche_anneau()
{

    int i,j;
    printf("Affichage de l'anneau : \n");

    for(i=0;i<TAILLE_ANNEAU;i++)
    {
        if(i == PLACE_R1)
        {
            printf("R%d : ", 1);
        }
        else if(i == PLACE_R2)
        {
            printf("R%d : ", 2);
        }
        else if(i == PLACE_R3)
        {
            printf("R%d : ", 3);
        }
        else if(i == PLACE_R4)
        {
            printf("R%d : ", 4);
        }
        else if(i == PLACE_R5)
        {
            printf("R%d : ", 5);
        }
        else if(i == PLACE_R6)
        {
            printf("R%d : ", 6);
        }
        else
        {
            printf("     ");
        }

        if(anneau[i].type_produit == 0)
        {
            if(anneau[i].type_composant == 0)
            {
                printf("0\n");
            }
            else
            {
                printf("C%d\n", anneau[i].type_composant);
            }

        }
        else
        {
            printf("P%d(", anneau[i].type_produit);
            printf("etat : %d", anneau[i].etat);

            printf(", [");

            for(j=0;j<5;j++)
            {
                if(anneau[i].operations[j] != 0)
                {
                    printf("Op%d, ", anneau[i].operations[j]);
                }
            }
            printf("])\n");
        }

    }
    printf("\n\n");

}

//Fonction qui permet d'afficher la file
void affiche_file()
{
    int i;

    printf("File d'attente des composants : \n");
    for(i=0;i<TAILLE_FILE;i++)
    {
        printf("|C%d", file_attente[i].type_composant);
    }
    printf("\n\n");
}
