#include "Joueur.h"


Joueur adversaire(Joueur joueur) {
    if (joueur == JOUEUR_1)
        return JOUEUR_2;
    return JOUEUR_1;
}
