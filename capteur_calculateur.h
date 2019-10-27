#ifndef CAPTEUR_CALCULATEUR_H
#define CAPTEUR_CALCULATEUR_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

#include "robots.h"
#include "structure.h"

typedef struct
{
    pthread_t analyse;

}Capteur;

typedef struct
{
    int compteurProduit[4];
    pthread_t arret_produit;

}Calculateur;

Calculateur calc;
Capteur capteur;

static pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_c = PTHREAD_COND_INITIALIZER;

void *fonc_capteur();
void *fonc_arret_produit();
int init_capt_calc();

#endif
