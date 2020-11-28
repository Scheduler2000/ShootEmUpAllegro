#ifndef __AFFICHEUR__
#define __AFFICHEUR__
#include "usine.h"

void afficher_tout(t_objet* objets);
void afficher_joueur(t_objet* objets);
void afficher_bonus(t_objet* objets);
void afficher_bonus_bouclier(t_objet* objets);
void afficher_bonus_tourelle(t_objet *objets);
void afficher_missiles(t_objet* objets);
void afficher_ennemis(t_objet* objets);
void afficher_bonus_vie_sup(t_objet* objets);
void afficher_bonus_dep_sup(t_objet* objets);
void afficher_bonus_tir_sup(t_objet* objets);
void afficher_bonus_missile_tele(t_objet* objets);
void afficher_bonus_missile_rapide(t_objet* objets);
void afficher_bonus_laser(t_objet* objets);


void niveau(t_objet* objets,int *x);
void scrolling(BITMAP* fond,BITMAP* buffer,int* x);
void rayon_laser_geant_hoz(t_objet* objets,int y);
void rayon_laser_geant_ver(t_objet* objets,int x);

#endif
