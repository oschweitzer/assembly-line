#include "simul.h"

//Fonction qui permet de definir ce que le robot doit faire avec les composants
void  gestion_composant(int num_robot, int nb_composant, int place_robot)
{
    pthread_mutex_lock(& mutex);

    //Si le robot a stocke le bon nombre de composant et s'il ne stocke pas deja un produit, il cree un Produit
    if(robots[num_robot].compteur_composant == nb_composant && robots[num_robot].p.etat == 0)
    {
        pthread_mutex_unlock(& mutex);

        printf("R%d fait op%d sur P%d pour creer P%d...\n\n", num_robot+1, num_robot+1, num_robot+1, num_robot+1);

        pthread_mutex_lock(&mutex_r);
        //on cree le produit et on le stocke sur le robot
        robots[num_robot].p.etat = 1;
        robots[num_robot].p.operations[0] = num_robot+1;
        robots[num_robot].p.type_produit = num_robot+1;

        //on enleve le nombre de composant necessaire pour le produit, ainsi on garde les composants qu'on a pu stocker en plus
        robots[num_robot].compteur_composant =  robots[num_robot].compteur_composant  - nb_composant;

        pthread_mutex_unlock(&mutex_r);

        // selon le robot l'operation dure plus ou moins de temps
        switch(num_robot)
        {
            case 0 : // Robot 1

                usleep(TPS_OP1);
                break;

            case 1 : // Robot 2

                usleep(TPS_OP2);
                break;

            case 2 : // Robot 3

                usleep(TPS_OP3);
                break;

            case 3 : // Robot 4

                usleep(TPS_OP4);
                break;

            case 4 : // Robot 5

                usleep(TPS_OP5);
                break;

            case 5 : // Robot 6

                usleep(TPS_OP6);
                break;
        }


        printf("R%d a termine op%d et cree P%d\n\n", num_robot+1, num_robot+1, num_robot+1);

        pthread_mutex_lock(& mutex);

        //si la section devant le robot est vide il met le produit sur l'anneau
        if(anneau[place_robot].type_composant == 0 && anneau[place_robot].type_produit == 0)
        {
            pthread_mutex_unlock(& mutex);
            placer_produit_anneau(place_robot, num_robot); // on place le produit dans l'anneau
        }
        else
        {
            pthread_mutex_unlock(& mutex);
        }
    }
    else if(anneau[place_robot].type_composant == (num_robot+1)) //Le robot prend les composants
    {
        printf("R%d prend un C%d\n\n", num_robot+1, num_robot+1);

        anneau[place_robot] = supprimer_produit(anneau[place_robot]); //on supprime le composant de l'anneau
        pthread_mutex_unlock(& mutex);

        robots[num_robot].compteur_composant++;// on incremente le compteur de composant
    }
    else
    {
        pthread_mutex_unlock(& mutex);
    }
}

// fonction qui permet aux robots d'effectuer les operations sur les produits
void gestion_robot(int place_robot, int num_robot)
{
    pthread_mutex_lock(& mutex);

    //si il y a un produit devant le robot et que ce dernier n'en stocke pas
    if(anneau[place_robot].type_produit != 0 && robots[num_robot].p.etat == 0)
    {
        pthread_mutex_unlock(& mutex);
        switch(num_robot)
        {
            case 0 : // Robot 1
                switch(anneau[PLACE_R1].type_produit)
                {
                    case 2 : //si il y a un P2
                        operation_produit(PLACE_R1, num_robot+1, 2, 4, 0); //on fait l'op1 si les bonnes operations precedentes ont ete faites
                        break;

                    case 3 : //si il y a un P3
                        operation_produit(PLACE_R1, num_robot+1, 1, 3, 0); //on fait l'op1 si les bonnes operations precedentes ont ete faites

                        operation_produit(PLACE_R1, num_robot+1, 3, 5, 0); //on fait l'op1 si les bonnes operations precedentes ont ete faites
                        break;

                    case 4 : //si il y a un P4

                        operation_produit(PLACE_R1, num_robot+1, 2, 6, 1);//on fait l'op1 si les bonnes operations precedentes ont ete faites

                        break;
                }
                break;

            case 1 : // Robot 2
                switch(anneau[PLACE_R2].type_produit)
                {
                    case 1 : //si il y a un P1
                        operation_produit(PLACE_R2, num_robot+1, 1, 1, 0); //on fait l'op2 si les bonnes operations precedentes ont ete faites
                        break;
                }
                break;

            case 2 : // Robot 3
                switch(anneau[PLACE_R3].type_produit)
                {
                    case 1 : //si il y a un P1
                        operation_produit(PLACE_R3, num_robot+1, 2, 2, 0); //on fait l'op3 si les bonnes operations precedentes ont ete faites
                        break;

                    case 3 : //si il y a un P3

                        operation_produit(PLACE_R3, num_robot+1, 4, 1, 1); //on fait l'op3 si les bonnes operations precedentes ont ete faites

                        break;
                }
                break;

            case 3 : // Robot 4
                switch(anneau[PLACE_R4].type_produit)
                {
                    case 2 : //si il y a un P2
                        operation_produit(PLACE_R4, num_robot+1, 1, 2, 0); //on fait l'op4 si les bonnes operations precedentes ont ete faites
                        break;
                }
                break;

            case 4 : // Robot 5
                switch(anneau[PLACE_R5].type_produit)
                {
                    case 1 : //si il y a un P1

                        operation_produit(PLACE_R5, num_robot+1, 3, 3, 1); //on fait l'op5 si les bonnes operations precedentes ont ete faites

                        break;

                    case 3 : //si il y a un P3
                        operation_produit(PLACE_R5, num_robot+1, 2, 1, 0); //on fait l'op5 si les bonnes operations precedentes ont ete faites
                        break;
                }
                break;

            case 5 : // Robot 6
                switch(anneau[PLACE_R6].type_produit)
                {
                    case 2 : //si il y a un P2

                        operation_produit(PLACE_R6, num_robot+1, 3, 1, 1);//on fait l'op6 si les bonnes operations precedentes ont ete faites

                        break;

                    case 4 : //si il y a un P4
                        operation_produit(PLACE_R6, num_robot+1, 1, 4, 0); //on fait l'op6 si les bonnes operations precedentes ont ete faites
                        break;
                }
                break;
        }
    }
    else
    {
        pthread_mutex_unlock(& mutex);
    }

    pthread_mutex_lock(& mutex);
    if(anneau[place_robot].type_composant == 0 && anneau[place_robot].type_produit == 0) // si la section devant le robot est vide
    {
        pthread_mutex_unlock(& mutex);

        pthread_mutex_lock(&mutex_r);
        if(robots[num_robot].p.type_produit != 0) // si le robot stocke un produit
        {
            pthread_mutex_unlock(&mutex_r);
            placer_produit_anneau(place_robot, num_robot); // on place le produit sur l'anneau
        }
        else
        {
            pthread_mutex_unlock(&mutex_r);
        }
    }
    else
    {
        pthread_mutex_unlock(& mutex);
    }
}


// Fonction qui place le produit sur l'anneau
void placer_produit_anneau(int place_robot, int num_robot)
{
    int i;

    pthread_mutex_lock(&mutex);

    //on recopie le produit stocke sur la section
    anneau[place_robot].type_produit = robots[num_robot].p.type_produit;
    anneau[place_robot].etat = robots[num_robot].p.etat;

    for(i=0;i<5;i++)
    {
       anneau[place_robot].operations[i] = robots[num_robot].p.operations[i];
    }
    pthread_mutex_unlock(&mutex);

    // on remet le produit stocke sur le robot a zero => le robot ne stocke plus de produit
    robots[num_robot].p.etat = 0;
    robots[num_robot].p.type_produit = 0;
    bzero(robots[num_robot].p.operations, sizeof(robots[num_robot].p.operations));
}

// Fonction qui effectue une operation sur un produit
int operation_produit(int place_robot, int numero_robot, int place_op, int num_op_prec, int derniere_op)
{
    int i;
    int op_effectue = 0;

    pthread_mutex_lock(&mutex);

    // si l'op precedente a ete faite et que l'op a faire n'a pas ete deja faite
    if(anneau[place_robot].operations[place_op-1] == num_op_prec && anneau[place_robot].operations[place_op] == 0)
    {
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex_r);
        // on prend le produit de l'anneau pour le stocker sur le robot
        robots[numero_robot-1].p.etat = anneau[place_robot].etat;
        robots[numero_robot-1].p.type_produit = anneau[place_robot].type_produit;

        for(i=0;i<5;i++)
        {

            robots[numero_robot-1].p.operations[i] = anneau[place_robot].operations[i];
        }

        pthread_mutex_unlock(&mutex_r);

        pthread_mutex_lock(&mutex);
        anneau[place_robot] = supprimer_produit(anneau[place_robot]);
        pthread_mutex_unlock(&mutex);


        pthread_mutex_lock(&mutex_r);
        printf("R%d fait operation%d sur P%d...\n\n", numero_robot, numero_robot, robots[numero_robot-1].p.type_produit);
        robots[numero_robot-1].p.operations[place_op] = numero_robot;
        pthread_mutex_unlock(&mutex_r);

        switch(numero_robot)
        {
            case 1:
                usleep(TPS_OP1);
                break;
            case 2:
                usleep(TPS_OP2);
                break;
            case 3 :
                usleep(TPS_OP3);
                break;
            case 4:
                usleep(TPS_OP4);
                break;
            case 5:
                usleep(TPS_OP5);
                break;
            case 6:
                usleep(TPS_OP6);
                break;
        }

        printf("R%d a termine operation%d sur P%d\n\n", numero_robot, numero_robot, robots[numero_robot-1].p.type_produit);

        if(derniere_op == 1)
        {
            pthread_mutex_lock(&mutex_r);
            robots[numero_robot - 1].p.etat = 2;
            pthread_mutex_unlock(&mutex_r);
        }

        pthread_mutex_lock(&mutex);
        if(anneau[place_robot].type_composant == 0 && anneau[place_robot].type_produit == 0) // la section devant le robot est vide
        {
            pthread_mutex_unlock(&mutex);
            placer_produit_anneau(place_robot, numero_robot-1); // on place le produit sur l'anneau
        }
        else
        {
            pthread_mutex_unlock(&mutex);
        }
    }
    else
    {
        pthread_mutex_unlock(&mutex);
    }

    return op_effectue;
}

// Fonction qu'execute chaque robot
void *fonc_robot(void *k)
{
    while(1)
    {
        int num_robot = (intptr_t)k;
        int nb_composant = 0;

        switch(num_robot) //on differencie les differents robots
        {

            case 0 : //Robot 1

                nb_composant = 3;
                gestion_composant(num_robot, nb_composant, PLACE_R1);
                gestion_robot(PLACE_R1, num_robot);

                break;

            case 1 : //Robot 2

                nb_composant = 3;
                gestion_composant(num_robot, nb_composant, PLACE_R2);
                gestion_robot(PLACE_R2, num_robot);

                break;

            case 2 : // Robot 3

                nb_composant = 1;
                gestion_composant(num_robot, nb_composant, PLACE_R3);
                gestion_robot(PLACE_R3, num_robot);

                break;

            case 3: // Robot 4

                nb_composant = 2;
                gestion_composant(num_robot, nb_composant, PLACE_R4);
                gestion_robot(PLACE_R4, num_robot);

                break;

            case 4: // Robot 5

                gestion_robot(PLACE_R5, num_robot);


                break;

            case 5: //Robot 6

                gestion_robot(PLACE_R6, num_robot);

                break;
        }
    }

    pthread_exit(NULL);
}


// Fonction qu'execute la file
void *fonc_file()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);

        // si la section d'entree est vide on y place un composant
        if(anneau[0].type_composant == 0 && anneau[0].type_produit == 0)
        {
          anneau[0] = file_attente[TAILLE_FILE-1];
          pthread_mutex_unlock(&mutex);
          avancer_file(); // on fait avancer le tapis des composants
        }
        else
        {
            pthread_mutex_unlock(&mutex);
        }

        pthread_mutex_lock(&mutex_f);
        pthread_cond_signal(&cond_a); // on previent l'anneau qu'il peut tourner
        pthread_mutex_unlock(&mutex_f);
    }

    pthread_exit(NULL);
}

// fonction qui fait avancer la file des composants
void avancer_file()
{
    usleep(TEMPS_AFF);
    printf("Le tapis des composants avance...\n\n");
    int i;
    for(i=TAILLE_FILE-1;i>=0;i--)
    {
        if(i == 0)
        {
            ajout_composant_file(i);
        }
        else
        {
            file_attente[i] = file_attente[i-1];
        }
    }
    affiche_file();
}

// Fonction du thread anneau
void *fonc_anneau()
{
    int section_pleine = 0;
    while(1)
    {

        int i;

        pthread_mutex_lock(&mutex_f);
        pthread_cond_wait(&cond_a, &mutex_f); // l'anneau attend que la file ait mis un composants
        pthread_mutex_unlock(&mutex_f);


        for(i=0;i<TAILLE_ANNEAU;i++)
        {
            if(anneau[i].type_composant > 0 || anneau[i].type_produit > 0) //si l'anneau est plein
            {
                section_pleine++;
            }
            else
            {
                section_pleine = 0;
            }
        }

        if(section_pleine >= TAILLE_ANNEAU) //si l'anneau est plein
        {
            printf("Anneau plein\n\n");
            compteur_anneau_plein++; // on incremente un compteur qui va permettre de faire faire un tour a l'anneau

            if(compteur_anneau_plein >= 18) // si l'anneau plein a fait un peu plus qu'un tour et qu'il l'est toujours
            {
                for(i=0;i<TAILLE_ANNEAU;i++)
                {
                    pthread_mutex_lock(&mutex);
                    if(anneau[i].type_composant != 0)
                    {
                        pthread_mutex_unlock(&mutex);
                        printf("Suppression des composants de l'anneau\n\n");
                        supprimer_produit(anneau[i]); // on supprime les composants presents sur l'anneau

                    }
                    else if(anneau[i].operations[1] == 0 || anneau[i].operations[2] == 0)
                    {
                        pthread_mutex_unlock(&mutex);
                        printf("Suppression des produits recemment crees de l'anneau\n\n");
                        supprimer_produit(anneau[i]); // on supprime les produits n'ayant qu'une operation de faite
                    }
                    else
                    {
                        pthread_mutex_unlock(&mutex);
                    }
                }
            }

            if(compteur_anneau_plein == 25)// en cas de blocage tres long
            {
                // on supprime les produits stockes sur les robots
                for(i=0;i<6;i++)
                {
                    pthread_mutex_lock(&mutex_r);
                    printf("Suppression des produits stockes des robots\n\n");
                    robots[i].p = supprimer_produit(robots[i].p);
                    pthread_mutex_unlock(&mutex_r);

                }

                compteur_anneau_plein = 1;
            }

        }

        usleep(TEMPS_AFF);
        tourner_anneau(); // on tourne l'anneau

    }

    pthread_exit(NULL);
}

// Fonction qui fait tourner l'anneau
void tourner_anneau()
{
    Produit tmp = anneau[TAILLE_ANNEAU-1];
    int i;

    printf("L'anneau tourne...\n\n");
    for(i=TAILLE_ANNEAU-1;i>-1;i--)
    {
        if(i==0)
        {
            pthread_mutex_lock(&mutex);
            anneau[i] = tmp;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_lock(&mutex);
            anneau[i] = anneau[i-1];
            pthread_mutex_unlock(&mutex);
        }
    }

    affiche_anneau(); // on affiche l'anneau
    usleep(TEMPS_AFF); // on attend pour que l'utilisateur puisse lire l'anneau
}

//Fonction qui permet d'arreter le systeme
void arret_systeme()
{
    int i;
    for(i=0;i<6;i++)
    {
        pthread_cancel(robots[i].operation);
        printf("Thread R%d ferme\n", i+1);
    }

    pthread_cancel(thread_anneau);
    printf("Thread anneau ferme\n");

    pthread_cancel(thread_file);
    printf("Thread file ferme\n");

    pthread_cond_destroy(&cond_a);
    printf("cond_a detruit\n");

    pthread_mutex_destroy(&mutex);
    printf("mutex detruit\n");

    arret = 1;
}

// Fonction principale qui initialise et cree les threads
void lancer_simulation()
{
    int i ,num;
    int ret = 0;
    compteur_anneau_plein = 0;
    arret = 0;

    //On remplit aléatoirement la file avec des composants
    for(i=0;i<TAILLE_FILE;i++)
    {
        ajout_composant_file(i);
    }

    printf("Demarrage de la chaine...\n\n");

    ret = pthread_create(&thread_anneau, 0, fonc_anneau, NULL); // on cree le thread de l'anneau
    if (ret)
    {
        fprintf (stderr, "%s", strerror (ret));
    }

    sleep(1);

    ret = pthread_create(&thread_file, 0, fonc_file, NULL); // on cree le thread de la file
    if (ret)
    {
        fprintf (stderr, "%s", strerror (ret));
    }

    sleep(1);

    /* creation des threads robots*/
    for (num = 0; num < 6; num++)
    {
        robots[num].compteur_composant = 0;
        ret = pthread_create(& robots[num].operation, 0, fonc_robot, (void *) (intptr_t)num);
        if (ret)
        {
            fprintf (stderr, "%s", strerror (ret));
        }
    }

    init_capt_calc(); // on initialise le capteur et le calculateur

    affiche_file(); // on affiche la file
    affiche_anneau(); // on affiche l'anneau

    while(arret == 0)
    {
    }

    printf("Systeme arrete\n");
}
