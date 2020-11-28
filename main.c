#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "usine.h"
#include "menu.h"
 #include "jeu.h"



int main()
{
    BITMAP* buffer;
    t_choix choixMenu;
    int niveau = 0;
    t_reglalge reglage;
    InitialiserAllegro();
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    show_mouse(screen);
etiq:
    clear(buffer);
    AfficherMenu(buffer,&choixMenu);

    switch(choixMenu)
    {
    case NouvellePartie :
        lancer_niveau(1);
        lancer_niveau(2);
        lancer_niveau(3);
        break;
    case ChargerPartie:
        AfficherChargerPartie(buffer,&niveau);
        for(niveau;niveau <= 3;niveau++)
            lancer_niveau(niveau);
        break;
    case Reglage:
        AfficherReglage(buffer,&reglage);
        goto etiq;
        break;
    case Quitter:
        QuitterJeu();
        break;
    }
    return 0;
}
END_OF_MAIN();

