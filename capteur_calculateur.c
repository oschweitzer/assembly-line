#include "capteur_calculateur.h"

extern void arret_systeme();


int type_prod;

// Fonction du capteur qui repere le produit sortant et en informe le calculateur
void *fonc_capteur()
{
    while(1)
    {
        // si le produit est termine
        if(anneau[PLACE_CAPTEUR].etat == 2)
        {
            pthread_mutex_lock(&mutex);
            type_prod = anneau[PLACE_CAPTEUR].type_produit; // on recupere le type de produit, cette variable est partagee avec le calculateur
            printf("P%d termine, sortie de l'anneau\n", type_prod);
            anneau[PLACE_CAPTEUR] = supprimer_produit(anneau[PLACE_CAPTEUR]); // on supprime le produit de l'anneau
            pthread_mutex_unlock(&mutex);

            pthread_mutex_lock(&mutex2);
            pthread_cond_signal(&cond_c);
            pthread_mutex_unlock(&mutex2);
        }
    }
}

// Fonction thread du calculateur qui compte les produits sortant et arrete le systeme si les quotas de produits sont acquis
void *fonc_arret_produit()
{
    int i;

    int stopP1=0, stopP2=0, stopP3=0, stopP4=0;
    while(1)
    {
        pthread_mutex_lock(&mutex2);
        pthread_cond_wait(&cond_c, &mutex2);
        pthread_mutex_unlock(&mutex2);

        switch(type_prod)
        {
            case 1 : // Produit 1
                if(stopP1 != 1)
                {
                    calc.compteurProduit[type_prod-1]++; // on incremente le compteur de produit 1
                }

                break;

            case 2 : // Produit 2
                if(stopP2 != 1)
                {
                    calc.compteurProduit[type_prod-1]++; // on incremente le compteur de produit 2
                }

                break;

            case 3 : // Produit 3
                if(stopP3 != 1)
                {
                    calc.compteurProduit[type_prod-1]++; // on incremente le compteur de produit 3
                }

                break;

            case 4 : // Produit 4
                if(stopP4 != 1)
                {
                    calc.compteurProduit[type_prod-1]++; // on incremente le compteur de produit 4
                }

                break;
        }

        printf("Nombre de produits finis : \n");

        // on affiche les comptes des produits finis
        for(i=0;i<4;i++)
        {
            printf("P%d : %d\n", i+1, calc.compteurProduit[i]);
        }
        printf("\n");


        if(calc.compteurProduit[0] >= NB_P1_MAX) // si le nombre recquis de P1 est atteint
        {
            stopP1 = 1;
            suppr_composant_file(1); // on supprime les composants C1 de la file
        }

        if(calc.compteurProduit[1] >= NB_P2_MAX) // si le nombre recquis de P2 est atteint
        {
            stopP2 = 1;
            suppr_composant_file(2); // on supprime les composants C2 de la file
        }

        if(calc.compteurProduit[2] >= NB_P3_MAX) // si le nombre recquis de P3 est atteint
        {
            stopP3 = 1;
            suppr_composant_file(3); // on supprime les composants C3 de la file
        }

        if(calc.compteurProduit[3] >= NB_P4_MAX) // si le nombre recquis de P4 est atteint
        {
            stopP4 = 1;
            suppr_composant_file(4); // on supprime les composants C4 de la file
        }

        if(stopP1 == 1 && stopP2 == 1 && stopP3 == 1 && stopP4 == 1) // si tous les produits ont atteint leur nombre recquis
        {
            printf("Le systeme va s'arreter\n\n");
            arret_systeme();
            pthread_cancel(capteur.analyse);
            printf("Thread capteur ferme\n");
            pthread_mutex_destroy(&mutex2);
            printf("mutex detruit\n");
            pthread_cancel(calc.arret_produit);
        }
    }
}

// Fonction qui cree les thread pour le capteur et pour le calculateur
int init_capt_calc()
{
    int ret = 0;

    ret = pthread_create(&capteur.analyse, 0, fonc_capteur, NULL);
    if (ret)
    {
        fprintf (stderr, "%s", strerror (ret));
    }

    ret = pthread_create(&calc.arret_produit, 0, fonc_arret_produit, NULL);
    if (ret)
    {
        fprintf (stderr, "%s", strerror (ret));
    }

    bzero(calc.compteurProduit, sizeof(calc.compteurProduit)); // on met le tableau des compteurs a zero

    return 0;
}
