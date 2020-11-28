#include "option.h"

void difficulte_niveau(t_objet* objets)//Gère la difficulte du niveau lorsqu'elle est fixée sur adaptative
{
    if(objets->j2->active==0)
    {
        switch(objets->j1->vie_restante)
        {
        case 0:
        case 1:
            objets->niv->diff=facile;
            break;
        case 2:
            objets->niv->diff=moyen;
            break;
        case 3:
            objets->niv->diff=difficile;
            break;
        default:
            objets->niv->diff=difficile;
            break;
        }
    }
    else
    {
        switch(objets->j1->vie_restante + objets->j2->vie_restante)
        {
        case 0:
        case 1:
        case 2:
            objets->niv->diff=facile;
            break;
        case 3:
        case 4:
            objets->niv->diff=moyen;
            break;
        case 5:
        case 6:
            objets->niv->diff=difficile;
            break;
        default:
            objets->niv->diff=difficile;
            break;
        }
    }
}

void init_music(t_objet* objets)
{
    const char c='d';
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,&c);
    SAMPLE *music;
    music = load_wav("Bit Rush.wav");
    if (!music)
    {
        allegro_message("Pas pu charger musique de fond!");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    play_sample(music,255,128,1000,10);
    objets->niv->musique=music;
}

void control_music(t_objet* objets,int choix,int vol)
{
    switch(choix)
    {
    case stop:
        stop_sample(objets->niv->musique);
        break;
    case play:
        play_sample(objets->niv->musique,vol,128,1000,10);
        break;
    case volume:
        adjust_sample(objets->niv->musique,vol,128,1000,10);
        break;
    }
}

