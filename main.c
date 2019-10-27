#include <stdio.h>
#include <stdlib.h>
#include "simul.h"

int main (int argc, char *argv[])
{
    srand(time(NULL)); // initialisation de rand
    lancer_simulation();
    return 0;
}
