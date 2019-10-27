#ifndef ROBOTS_H
#define ROBOTS_H

#include "structure.h"

typedef struct
{
    pthread_t operation;
    int compteur_composant;
    Produit p;

}Robot; //Objet robot

Robot robots[6]; //Tableau des robots contenant les 6 robots du systeme

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //mutex pour proteger l'anneau

void  gestion_composant(int num_robot, int nb_composant, int place_robot);
void gestion_robot(int place_robot, int num_robot);
void placer_produit_anneau(int place_robot, int num_robot);
int operation_produit(int place_robot, int numero_robot, int place_op, int num_op_prec, int derniere_op);
void *fonc_robot(void *k);

#endif // ROBOTS_H
