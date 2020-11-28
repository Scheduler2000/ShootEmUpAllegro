#ifndef __MENU__
#define __MENU__
#include <allegro.h>

typedef enum Difficulte
{
    facile,
    moyen,
    difficile,
    adaptatif,
    Nul = -1
} t_difficulte;


typedef struct Reglage
{
    t_difficulte difficulte;
    int volume;
} t_reglalge;



typedef enum Choix
{
    NouvellePartie,
    ChargerPartie,
    Reglage,
    Quitter,
    None = -1
} t_choix;


BITMAP* DessinerChargerPartie(BITMAP* buffer);
void AfficherChargerPartie(BITMAP* buffer, int* niveau);
void ChoixChargerPartie(BITMAP* buffer, int* niv);

void AfficherMenu(BITMAP* buffer,t_choix* choixMenu);
void AfficherReglage(BITMAP* buffer,t_reglalge* reglage);
BITMAP* DessinerMenu(BITMAP* buffer);
BITMAP* DessinerReglage(BITMAP* buffer);
void ChoixReglage(BITMAP* reglalge,t_reglalge* reglage);
t_choix ChoixMenu(BITMAP* menu);
BITMAP* LoadBitmap(char *fileName, int ratio); // Prgm pour une future resolution dynamique

void QuitterJeu();
void InitialiserAllegro();

#endif // __MENU__
