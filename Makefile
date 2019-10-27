CC=gcc
LIBS ?= -lpthread
OBJS=affichage.o structure.o simul.o capteur_calculateur.o main.o

all: chaine_montage

chaine_montage: $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	$(RM) -f chaine_montage *~ $(OBJS)
