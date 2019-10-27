#include "structure.h"

//Fonction qui retourne un entier aléatoire compris entre a(inclus) et b(exclu)
int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}

//Fonction qui creee aleatoirement un composant et le place dans la file
void ajout_composant_file(int i)
{
    Produit composant;
    composant.type_composant = rand_a_b(1,5);
    composant.etat = 0;
    composant.type_produit = 0;


    file_attente[i] = composant;
}

//Fonction qui suprimme le composant de numero specifie dans le parametre
void suppr_composant_file(int c)
{
    int i,j=0;
    int tab[3] = {0};
    for(i=0;i<TAILLE_FILE;i++)
    {
        if(file_attente[i].type_composant == c)
        {
            switch(c)
            {
                case 1 :

                    file_attente[i].type_composant = rand_a_b(2,5);

                    break;

                case 2 :

                    tab[0] = 1;
                    tab[1] = 3;
                    tab[2] = 4;
                    j = rand_a_b(0,3);
                    file_attente[i].type_composant = tab[j];

                    break;

                case 3 :

                    tab[0] = 1;
                    tab[1] = 2;
                    tab[2] = 4;
                    j = rand_a_b(0,3);
                    file_attente[i].type_composant = tab[j];

                    break;

                case 4 :

                    file_attente[i].type_composant = rand_a_b(1,4);

                    break;
            }
        }
    }
}

//Fonction qui supprime le produit p et renvoie un produit vide
Produit supprimer_produit(Produit p)
{
    int i;

    p.etat = 0;
    p.type_composant = 0;
    p.type_produit = 0;
    for(i=0;i<5;i++)
    {
        p.operations[i] = 0;
    }

    return p;
}
