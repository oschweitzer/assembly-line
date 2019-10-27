#ifndef SIMUL_H
#define SIMUL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

#include "structure.h"
#include "affichage.h"
#include "capteur_calculateur.h"
#include "robots.h"


void tourner_anneau();
void lancer_simulation();
void arret_systeme();
void avancer_file();

static pthread_mutex_t mutex_f = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_r = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_a = PTHREAD_COND_INITIALIZER;

pthread_t thread_anneau;
pthread_t thread_file;

int compteur_anneau_plein;
int arret;

#endif // SIMUL_H
