#ifndef __OPTIONS__
#define __OPTIONS
#include "usine.h"

typedef enum Difficulte
{
    facile,
    moyen,
    difficile,
    adaptatif,
    Nul = -1
} t_difficulte;

typedef enum music
{
    stop,play,volume
} t_music;

void difficulte_niveau(t_objet* objets);//G�re la difficulte du niveau lorsqu'elle est fix�e sur adaptative
void init_music(t_objet* objets);
void control_music(t_objet* objets,int choix,int vol);

#endif // __OPTIONS__
