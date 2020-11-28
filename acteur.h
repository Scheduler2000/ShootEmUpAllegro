#ifndef __ACTEUR__
#define __ACTEUR__
#include "usine.h"

void actions(t_objet* objets);
void deplacer_joueur(t_objet* objets);
void actions_joueur(t_objet* objets);
void deplacer_boss(t_objet* objets);
void tir_normal(t_joueur* j,t_objet* objets);
void tir_rapide(t_joueur* j,t_objet* objets);
void laser(t_joueur* j,t_objet* objets);
void missile_teleguide(t_joueur* j,t_objet* objets);
void collision(t_objet* objets);
int visee(t_objet* objets,int x,int y);
void tourelle(t_joueur* j,t_objet* objets);

#endif // __ACTEUR__
