#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define TAILLE_ANNEAU 16
#define TAILLE_FILE 15

#define PLACE_R1 1
#define PLACE_R2 3
#define PLACE_R3 5
#define PLACE_R4 7
#define PLACE_R5 10
#define PLACE_R6 14

#define TPS_OP1 3000000
#define TPS_OP2 5000000
#define TPS_OP3 4000000
#define TPS_OP4 6000000
#define TPS_OP5 1000000
#define TPS_OP6 2000000

#define TEMPS_AFF 1500000

#define PLACE_CAPTEUR 15

#define NB_P1_MAX 10
#define NB_P2_MAX 15
#define NB_P3_MAX 12
#define NB_P4_MAX 8

//Structure d'un produit ou d'un composant
typedef struct
{
    int etat;
    int type_produit;
    int operations[5];

    int type_composant;

}Produit;

Produit anneau[TAILLE_ANNEAU]; // Anneau de 16 sections
Produit file_attente[TAILLE_FILE]; // File d'attente des composants


int rand_a_b(int a, int b);
void ajout_composant_file(int i);
Produit supprimer_produit(Produit p);
void suppr_composant_file(int c);

#endif
