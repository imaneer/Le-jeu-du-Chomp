#ifndef __TABLETTE__
#define __TABLETTE__

#define NB_LIGNES 8
#define NB_COLONNES 16

typedef struct {
    int tablette[NB_LIGNES][NB_COLONNES];
}Tablette;

Tablette creer_tablette();
void manger(Tablette *tab, int x, int y);

#endif
