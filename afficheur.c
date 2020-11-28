#include "afficheur.h"
#include <allegro.h>
void afficher_tout(t_objet* objets)
{
    clear(objets->niv->hitbox);
    clear(objets->niv->buffer);

    scrolling(objets->niv->fond,objets->niv->buffer,&(objets->niv->avancement_fond));
    afficher_ennemis(objets);
    afficher_joueur(objets);
    afficher_bonus(objets);
    afficher_missiles(objets);
    if(objets->niv->x < screen->w+objets->niv->niveau1->w && objets->niv->niveau_actuel==1)
        masked_blit(objets->niv->niveau1,objets->niv->buffer,0,0,screen->w+objets->niv->niveau1->w-3*objets->niv->x,screen->h/2,objets->niv->niveau1->w,objets->niv->niveau1->h);
    if(objets->niv->x < screen->w+objets->niv->niveau2->w && objets->niv->niveau_actuel==2)
        masked_blit(objets->niv->niveau2,objets->niv->buffer,0,0,screen->w+objets->niv->niveau2->w-3*objets->niv->x,screen->h/2,objets->niv->niveau2->w,objets->niv->niveau2->h);
    if(objets->niv->x < screen->w+objets->niv->niveau3->w && objets->niv->niveau_actuel==3)
        masked_blit(objets->niv->niveau3,objets->niv->buffer,0,0,screen->w+objets->niv->niveau3->w-3*objets->niv->x,screen->h/2,objets->niv->niveau3->w,objets->niv->niveau3->h);

    blit(objets->niv->buffer,screen,0,0,0,0,screen->w,screen->h);
}

void afficher_joueur(t_objet* objets)
{
    if(objets->j1->powerup->bouclier->cooldown>0)
    {
        blit(objets->j1->powerup->bouclier->hitbox,objets->niv->hitbox,0,0,objets->j1->posx-1,objets->j1->posy-1,objets->j1->taille_x+1,objets->j1->taille_y+1);
        masked_blit(objets->img->bou,objets->niv->buffer,0,0,objets->j1->posx-1,objets->j1->posy-1,objets->img->bou->w,objets->img->bou->h);
    }
    else if(objets->j1->active==1 && objets->j1->vie>0)
    {
        blit(objets->j1->hitbox,objets->niv->hitbox,0,0,objets->j1->posx,objets->j1->posy,objets->j1->taille_x,objets->j1->taille_y);
        masked_blit(objets->img->j1,objets->niv->buffer,0,0,objets->j1->posx,objets->j1->posy,objets->img->j1->w,objets->img->j1->h);
    }


    if(objets->j2->powerup->bouclier->cooldown>0)
    {
        blit(objets->j2->powerup->bouclier->hitbox,objets->niv->hitbox,0,0,objets->j2->posx-1,objets->j2->posy-1,objets->j2->taille_x+1,objets->j2->taille_y+1);
        masked_blit(objets->img->bou,objets->niv->buffer,0,0,objets->j2->posx-1,objets->j2->posy-1,objets->img->bou->w,objets->img->bou->h);
    }
    else if(objets->j2->active==1 && objets->j2->vie>0)
    {
        blit(objets->j2->hitbox,objets->niv->hitbox,0,0,objets->j2->posx,objets->j2->posy,objets->j2->taille_x,objets->j2->taille_y);
        masked_blit(objets->img->j2,objets->niv->buffer,0,0,objets->j2->posx,objets->j2->posy,objets->img->j2->w,objets->img->j2->h);
    }
}

void afficher_missiles(t_objet* objets)
{
    int i;
    for(i=0; i<20; i++)
    {
        if(objets->j1->elements[i]!=NULL)
        {
            if(objets->j1->elements[i]->posx+objets->j1->elements[i]->depx <= screen->w)
            {
                switch(objets->j1->elements[i]->taillex)
                {
                case 10:// pour les missiles normaux
                    blit(objets->j1->powerup->miss_norm->hitbox,objets->niv->hitbox,0,0,
                         objets->j1->elements[i]->posx+=objets->j1->elements[i]->depx,
                         objets->j1->elements[i]->posy+=objets->j1->elements[i]->depy,
                         objets->j1->powerup->miss_norm->hitbox->w,
                         objets->j1->powerup->miss_norm->hitbox->h);
                    masked_blit(objets->img->miss_norm,objets->niv->buffer,0,0,
                                objets->j1->elements[i]->posx,
                                objets->j1->elements[i]->posy,
                                objets->img->miss_norm->w,
                                objets->img->miss_norm->h);
                    break;
                case 15 :// Pour les missiles rapides
                    blit(objets->j1->powerup->missile_rapide->hitbox,objets->niv->hitbox,0,0,
                         objets->j1->elements[i]->posx+=objets->j1->elements[i]->depx,
                         objets->j1->elements[i]->posy+=objets->j1->elements[i]->depy,
                         objets->j1->powerup->missile_rapide->hitbox->w,
                         objets->j1->powerup->missile_rapide->hitbox->h);
                    masked_blit(objets->img->miss_rapi,objets->niv->buffer,0,0,
                                objets->j1->elements[i]->posx,
                                objets->j1->elements[i]->posy,
                                objets->img->miss_rapi->w,
                                objets->img->miss_rapi->h);
                    break;
                case 17 :// Pour les missiles teleguides
                    if( objets->j1->elements[i]->cible!=1000)//Si le missile a une cible
                    {
                        if(objets->niv->tab[objets->j1->elements[i]->cible]->vie > 0)
                        {
                            if ( objets->j1->elements[i]->posx  >  objets->niv->tab[objets->j1->elements[i]->cible]->posx )
                                objets->j1->elements[i]->posx-=objets->j1->elements[i]->depx;
                            else if( objets->j1->elements[i]->posx  <  objets->niv->tab[objets->j1->elements[i]->cible]->posx)
                                objets->j1->elements[i]->posx+=objets->j1->elements[i]->depx;

                            if ( objets->j1->elements[i]->posy  >  objets->niv->tab[objets->j1->elements[i]->cible]->posy)
                                objets->j1->elements[i]->posy-=objets->j1->elements[i]->depy;
                            else if ( objets->j1->elements[i]->posy  <  objets->niv->tab[objets->j1->elements[i]->cible]->posy)
                                objets->j1->elements[i]->posy+=objets->j1->elements[i]->depy;
                        }
                        else
                            objets->j1->elements[i]->cible=visee(objets,objets->j1->posx,objets->j1->posy);

                        blit(objets->j1->powerup->missile_tele->hitbox,objets->niv->hitbox,0,0,
                             objets->j1->elements[i]->posx,
                             objets->j1->elements[i]->posy,
                             objets->j1->powerup->missile_rapide->hitbox->w,
                             objets->j1->powerup->missile_rapide->hitbox->h);
                        masked_blit(objets->img->miss_tele,objets->niv->buffer,0,0,
                                    objets->j1->elements[i]->posx,
                                    objets->j1->elements[i]->posy,
                                    objets->img->miss_tele->w,
                                    objets->img->miss_tele->h);
                    }
                    else
                    {
                        objets->j1->elements[i]->cible=visee(objets,objets->j2->posx,objets->j2->posy);
                        blit(objets->j1->powerup->missile_tele->hitbox,objets->niv->hitbox,0,0,
                             objets->j1->elements[i]->posx+=objets->j1->elements[i]->depx,
                             objets->j1->elements[i]->posy,
                             objets->j1->powerup->missile_rapide->hitbox->w,
                             objets->j1->powerup->missile_rapide->hitbox->h);
                        masked_blit(objets->img->miss_tele,objets->niv->buffer,0,0,
                                    objets->j1->elements[i]->posx,
                                    objets->j1->elements[i]->posy,
                                    objets->img->miss_tele->w,
                                    objets->img->miss_tele->h);
                    }
                    break;
                }
            }

            else
                objets->j1->elements[i]=NULL;//Si le missile dépasse l'écran il est supprimé
        }
    }
    for(i=0; i<20; i++)
    {
        if(objets->j2->elements[i]!=NULL)
        {
            if(objets->j2->elements[i]->posx+objets->j2->elements[i]->depx <= screen->w)
            {
                switch(objets->j2->elements[i]->taillex)
                {
                case 10 :
                    blit(objets->j2->powerup->miss_norm->hitbox,objets->niv->hitbox,0,0,
                         objets->j2->elements[i]->posx+=objets->j2->elements[i]->depx,
                         objets->j2->elements[i]->posy+=objets->j2->elements[i]->depy,
                         objets->j2->powerup->miss_norm->hitbox->w,
                         objets->j2->powerup->miss_norm->hitbox->h);
                    masked_blit(objets->img->miss_norm,objets->niv->buffer,0,0,
                                objets->j2->elements[i]->posx,
                                objets->j2->elements[i]->posy,
                                objets->img->miss_norm->w,
                                objets->img->miss_norm->h);
                    break;
                case 15 :
                    blit(objets->j2->powerup->missile_rapide->hitbox,objets->niv->hitbox,0,0,
                         objets->j2->elements[i]->posx+=objets->j2->elements[i]->depx,
                         objets->j2->elements[i]->posy+=objets->j2->elements[i]->depy,
                         objets->j2->powerup->missile_rapide->hitbox->w,
                         objets->j2->powerup->missile_rapide->hitbox->h);
                    masked_blit(objets->img->miss_rapi,objets->niv->buffer,0,0,
                                objets->j2->elements[i]->posx,
                                objets->j2->elements[i]->posy,
                                objets->img->miss_rapi->w,
                                objets->img->miss_rapi->h);
                    break;
                case 17 :// Pour les missiles teleguides
                    if( objets->j2->elements[i]->cible!=1000)//Si le missile a une cible
                    {
                        if(objets->niv->tab[objets->j2->elements[i]->cible]->vie > 0)
                        {
                            if ( objets->j2->elements[i]->posx  >  objets->niv->tab[objets->j2->elements[i]->cible]->posx )
                                objets->j2->elements[i]->posx-=objets->j2->elements[i]->depx;
                            else if( objets->j2->elements[i]->posx  <  objets->niv->tab[objets->j2->elements[i]->cible]->posx)
                                objets->j2->elements[i]->posx+=objets->j2->elements[i]->depx;

                            if ( objets->j2->elements[i]->posy  >  objets->niv->tab[objets->j2->elements[i]->cible]->posy)
                                objets->j2->elements[i]->posy-=objets->j2->elements[i]->depy;
                            else if ( objets->j2->elements[i]->posy  <  objets->niv->tab[objets->j2->elements[i]->cible]->posy)
                                objets->j2->elements[i]->posy+=objets->j2->elements[i]->depy;
                        }
                        else
                            objets->j2->elements[i]->cible=visee(objets,objets->j2->posx,objets->j2->posy);

                        blit(objets->j2->powerup->missile_tele->hitbox,objets->niv->hitbox,0,0,
                             objets->j2->elements[i]->posx,
                             objets->j2->elements[i]->posy,
                             objets->j2->powerup->missile_rapide->hitbox->w,
                             objets->j2->powerup->missile_rapide->hitbox->h);
                        masked_blit(objets->img->miss_tele,objets->niv->buffer,0,0,
                                    objets->j2->elements[i]->posx,
                                    objets->j2->elements[i]->posy,
                                    objets->img->miss_tele->w,
                                    objets->img->miss_tele->h);
                    }
                    else
                    {
                        objets->j2->elements[i]->cible=visee(objets,objets->j2->posx,objets->j2->posy);
                        blit(objets->j2->powerup->missile_tele->hitbox,objets->niv->hitbox,0,0,
                             objets->j2->elements[i]->posx+=objets->j2->elements[i]->depx,
                             objets->j2->elements[i]->posy,
                             objets->j2->powerup->missile_rapide->hitbox->w,
                             objets->j2->powerup->missile_rapide->hitbox->h);
                        masked_blit(objets->img->miss_rapi,objets->niv->buffer,0,0,
                                    objets->j2->elements[i]->posx,
                                    objets->j2->elements[i]->posy,
                                    objets->img->miss_rapi->w,
                                    objets->img->miss_rapi->h);
                    }
                    break;
                }
            }
            else
                objets->j2->elements[i]=NULL;//Si le missile dépasse l'écran il est supprimé
        }
    }
    if(!key[KEY_H])
    {
        if(objets->j2->powerup->laser->cooldown > 0 && objets->j2->powerup->laser->cooldown <100)
        {
            blit(objets->j2->powerup->laser->hitbox,
                 objets->niv->hitbox,0,0,
                 objets->j2->posx+objets->j2->taille_x,
                 objets->j2->posy+objets->j2->taille_y/2-objets->j2->powerup->laser->hitbox->h/8,
                 objets->j2->powerup->laser->hitbox->w,
                 (objets->j2->powerup->laser->hitbox->h)/4);
            masked_blit(objets->img->plaser,objets->niv->buffer,0,0,objets->j2->posx+objets->img->j2->w,objets->j2->posy+objets->img->j2->h/2-objets->j2->powerup->laser->hitbox->h/8,objets->img->plaser->w,objets->img->plaser->h);
        }
        else if(objets->j2->powerup->laser->cooldown >= 100 && objets->j2->powerup->laser->cooldown <250)
        {
            blit(objets->j2->powerup->laser->hitbox,
                 objets->niv->hitbox,0,0,
                 objets->j2->posx+objets->j2->taille_x,
                 objets->j2->posy+objets->j2->taille_y/2-objets->j2->powerup->laser->hitbox->h/4,
                 objets->j2->powerup->laser->hitbox->w,
                 objets->j2->powerup->laser->hitbox->h/2);
            masked_blit(objets->img->mlaser,objets->niv->buffer,0,0,objets->j2->posx+objets->img->j2->w,objets->j2->posy+objets->img->j2->h/2-objets->j2->powerup->laser->hitbox->h/4,objets->img->mlaser->w,objets->img->mlaser->h);
        }
        else if(objets->j2->powerup->laser->cooldown >= 250)
        {
            blit(objets->j2->powerup->laser->hitbox,
                 objets->niv->hitbox,0,0,
                 objets->j2->posx+objets->j2->taille_x,
                 objets->j2->posy+objets->j2->taille_y/2-(objets->j2->powerup->laser->hitbox->h/2),
                 objets->j2->powerup->laser->hitbox->w,
                 objets->j2->powerup->laser->hitbox->h);
            masked_blit(objets->img->glaser,objets->niv->buffer,0,0,objets->j2->posx+objets->img->j2->w,objets->j2->posy+objets->img->j2->h/2-objets->img->glaser->h/2,objets->img->glaser->w,objets->img->glaser->h);
        }
    }
    if(!key[KEY_L])
    {
        if(objets->j1->powerup->laser->cooldown > 0 && objets->j1->powerup->laser->cooldown <100)
        {
            blit(objets->j1->powerup->laser->hitbox,
                 objets->niv->hitbox,0,0,
                 objets->j1->posx+objets->j1->taille_x,
                 objets->j1->posy+objets->j1->taille_y/2-objets->j1->powerup->laser->hitbox->h/8,
                 objets->j1->powerup->laser->hitbox->w,
                 (objets->j1->powerup->laser->hitbox->h)/4);
            masked_blit(objets->img->plaser,objets->niv->buffer,0,0,objets->j1->posx+objets->img->j1->w,objets->j1->posy+objets->img->j1->h/2-objets->j2->powerup->laser->hitbox->h/8,objets->img->plaser->w,objets->img->plaser->h);
        }
        else if(objets->j1->powerup->laser->cooldown >= 100 && objets->j1->powerup->laser->cooldown <250)
        {
            blit(objets->j1->powerup->laser->hitbox,
                 objets->niv->hitbox,0,0,
                 objets->j1->posx+objets->j1->taille_x,
                 objets->j1->posy+objets->j1->taille_y/2-objets->j1->powerup->laser->hitbox->h/4,
                 objets->j1->powerup->laser->hitbox->w,
                 objets->j1->powerup->laser->hitbox->h/2);
            masked_blit(objets->img->mlaser,objets->niv->buffer,0,0,objets->j1->posx+objets->img->j1->w,objets->j1->posy+objets->img->j1->h/2-objets->j2->powerup->laser->hitbox->h/4,objets->img->mlaser->w,objets->img->mlaser->h);
        }
        else if(objets->j1->powerup->laser->cooldown >= 250)
        {
            blit(objets->j1->powerup->laser->hitbox,
                 objets->niv->hitbox,0,0,
                 objets->j1->posx+objets->j1->taille_x,
                 objets->j1->posy+objets->j1->taille_y/2-(objets->j1->powerup->laser->hitbox->h/2),
                 objets->j1->powerup->laser->hitbox->w,
                 objets->j1->powerup->laser->hitbox->h);
            masked_blit(objets->img->glaser,objets->niv->buffer,0,0,objets->j1->posx+objets->img->j1->w,objets->j1->posy+objets->img->j1->h/2-objets->img->glaser->h/2,objets->img->glaser->w,objets->img->glaser->h);
        }
    }
}

void afficher_ennemis(t_objet* objets)
{
    int i=0;
    double distancej1=0,distancej2=0;//Utilisé pour connaitre la cibles des ennemis suiveurs
    while(objets->niv->tab[i]!=NULL)
    {
        switch(objets->niv->tab[i]->type)
        {
        case nuee://Une nuée d'ennemis

            if(objets->niv->tab[i]->vie>0)
            {
                blit(objets->niv->tab[i]->hitbox,objets->niv->hitbox,0,0,objets->niv->tab[i]->posx-=objets->niv->tab[i]->depx,objets->niv->tab[i]->posy,objets->niv->tab[i]->hitbox->w,objets->niv->tab[i]->hitbox->h);
                masked_blit(objets->img->ennue,objets->niv->buffer,0,0,objets->niv->tab[i]->posx,objets->niv->tab[i]->posy,objets->img->ennue->w,objets->img->ennue->h);
            }
            break;

        case lambda://Un ennemi banal

            if(objets->niv->tab[i]->vie>0)
            {
                blit(objets->niv->tab[i]->hitbox,objets->niv->hitbox,0,0,objets->niv->tab[i]->posx-=objets->niv->tab[i]->depx,objets->niv->tab[i]->posy+(int)(60*sin((double)(objets->niv->x)/20)),objets->niv->tab[i]->hitbox->w,objets->niv->tab[i]->hitbox->h);
                masked_blit(objets->img->enlamb,objets->niv->buffer,0,0,objets->niv->tab[i]->posx,objets->niv->tab[i]->posy+(int)(60*sin((double)(objets->niv->x)/20)),objets->img->enlamb->w,objets->img->enlamb->h);
            }
            break;

        case gros://Les gros ennemis tirs des petits vaisseaux

            if(objets->niv->tab[i]->vie>0)
            {
                objets->niv->tab[i]->tir-=1;//On diminue le cooldown de 10 ms
                if(objets->niv->tab[i]->tir<=0)
                {
                    objets->niv->tab[i]->tir=600;
                    creer_vaisseaux(objets,i);
                }
                blit(objets->niv->tab[i]->hitbox,objets->niv->hitbox,0,0,objets->niv->tab[i]->posx-=objets->niv->tab[i]->depx,objets->niv->tab[i]->posy,objets->niv->tab[i]->hitbox->w,objets->niv->tab[i]->hitbox->h);
                masked_blit(objets->img->engros,objets->niv->buffer,0,0,objets->niv->tab[i]->posx,objets->niv->tab[i]->posy,objets->img->engros->w,objets->img->engros->h);
            }
            break;

        case suiveur://Un ennemie qui vous colle

            distancej1=sqrt( (objets->niv->tab[i]->posx - objets->j1->posx)*(objets->niv->tab[i]->posx - objets->j1->posx) + (objets->niv->tab[i]->posy - objets->j1->posy)*(objets->niv->tab[i]->posy - objets->j1->posy));
            distancej2=sqrt( (objets->niv->tab[i]->posx - objets->j2->posx)*(objets->niv->tab[i]->posx - objets->j2->posx) + (objets->niv->tab[i]->posy - objets->j2->posy)*(objets->niv->tab[i]->posy - objets->j2->posy));
            if(objets->j1->vie<=0 && objets->j2->vie<=0)
                objets->niv->tab[i]->posx-=objets->niv->tab[i]->depx;
            else if( (distancej1<distancej2 && objets->j1->vie>0) || objets->j2->vie<=0)
            {
                if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posy > objets->j1->posy)
                    objets->niv->tab[i]->posy-=objets->niv->tab[i]->depy;
                if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posy < objets->j1->posy)
                    objets->niv->tab[i]->posy+=objets->niv->tab[i]->depy;
                if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posx > objets->j1->posx)
                    objets->niv->tab[i]->posx-=objets->niv->tab[i]->depx;
                if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posx < objets->j1->posx)
                    objets->niv->tab[i]->posx+=objets->niv->tab[i]->depx;
            }
            else if( (distancej1>distancej2 && objets->j2->vie>0) || objets->j1->vie<=0)
            {
                if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posy > objets->j2->posy)
                    objets->niv->tab[i]->posy-=objets->niv->tab[i]->depy;
                if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posy < objets->j2->posy)
                    objets->niv->tab[i]->posy+=objets->niv->tab[i]->depy;
                if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posx > objets->j2->posx)
                    objets->niv->tab[i]->posx-=objets->niv->tab[i]->depx;
                if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posx < objets->j2->posx)
                    objets->niv->tab[i]->posx+=objets->niv->tab[i]->depx;
            }
            if(objets->niv->tab[i]->vie>0)
            {
                blit(objets->niv->tab[i]->hitbox,objets->niv->hitbox,0,0,objets->niv->tab[i]->posx,objets->niv->tab[i]->posy,objets->niv->tab[i]->hitbox->w,objets->niv->tab[i]->hitbox->h);
                masked_blit(objets->img->ensuiv,objets->niv->buffer,0,0,objets->niv->tab[i]->posx,objets->niv->tab[i]->posy,objets->img->ensuiv->w,objets->img->ensuiv->h);
            }
            break;

        case rapide:

            if(objets->niv->tab[i]->vie>0)
            {
                blit(objets->niv->tab[i]->hitbox,objets->niv->hitbox,0,0,objets->niv->tab[i]->posx-=objets->niv->tab[i]->depx,objets->niv->tab[i]->posy,objets->niv->tab[i]->hitbox->w,objets->niv->tab[i]->hitbox->h);
                masked_blit(objets->img->enrapi,objets->niv->buffer,0,0,objets->niv->tab[i]->posx,objets->niv->tab[i]->posy,objets->img->enrapi->w,objets->img->enrapi->h);
            }
            break;

        case ciel :

            if(objets->niv->tab[i]->vie>0)
            {
                blit(objets->niv->tab[i]->hitbox,objets->niv->hitbox,0,0,objets->niv->tab[i]->posx-=objets->niv->tab[i]->depx,objets->niv->tab[i]->posy-=objets->niv->tab[i]->depy,objets->niv->tab[i]->hitbox->w,objets->niv->tab[i]->hitbox->h);
                masked_blit(objets->img->enciel,objets->niv->buffer,0,0,objets->niv->tab[i]->posx,objets->niv->tab[i]->posy,objets->img->enciel->w,objets->img->enciel->h);
            }
            break;
        }
        i++;
    }
    if(objets->niv->niveau_actuel==2)
    {
        laser_geants(objets);
    }
    if(objets->niv->niveau_actuel==3)
    {
        laser_geants2(objets);
    }
    if(objets->niv->niveau_actuel==3 && objets->niv->boss->active==1 && objets->niv->boss->vie>0)
    {
        blit(objets->niv->boss->hitbox,objets->niv->hitbox,0,0,objets->niv->boss->posx,objets->niv->boss->posy,objets->niv->boss->hitbox->w,objets->niv->boss->hitbox->h);
        masked_blit(objets->img->enboss,objets->niv->buffer,0,0,objets->niv->boss->posx,objets->niv->boss->posy,objets->img->enboss->w,objets->img->enboss->h);
    }
}

void afficher_bonus(t_objet* objets)
{
    afficher_bonus_bouclier(objets);
    afficher_bonus_tourelle(objets);
    afficher_bonus_vie_sup(objets);
    afficher_bonus_dep_sup(objets);
    afficher_bonus_tir_sup(objets);
    afficher_bonus_missile_tele(objets);
    afficher_bonus_missile_rapide(objets);
    afficher_bonus_laser(objets);
}

void afficher_bonus_bouclier(t_objet* objets)
{
    if(objets->j1->powerup->bouclier->afficher==1)
    {
        blit(objets->j1->powerup->bouclier->bulle,objets->niv->hitbox,0,0,
             objets->j1->powerup->bouclier->posx-=objets->j1->powerup->bouclier->depx,
             objets->j1->powerup->bouclier->posy,
             objets->j1->powerup->bouclier->bulle->w,
             objets->j1->powerup->bouclier->bulle->h);
        masked_blit(objets->img->bou,objets->niv->buffer,0,0,
                    objets->j1->powerup->bouclier->posx,objets->j1->powerup->bouclier->posy,
                    objets->img->bou->w,objets->img->bou->h);
    }

}

void afficher_bonus_vie_sup(t_objet* objets)
{
    if(objets->j1->powerup->vie_sup->afficher==1)
    {
        blit(objets->j1->powerup->vie_sup->bulle,objets->niv->hitbox,0,0,
             objets->j1->powerup->vie_sup->posx-=objets->j1->powerup->vie_sup->depx,
             objets->j1->powerup->vie_sup->posy,
             objets->j1->powerup->vie_sup->bulle->w,
             objets->j1->powerup->vie_sup->bulle->h);
        masked_blit(objets->img->vie,objets->niv->buffer,0,0,
                    objets->j1->powerup->vie_sup->posx,objets->j1->powerup->vie_sup->posy,
                    objets->img->vie->w,objets->img->vie->h);
    }

}

void afficher_bonus_dep_sup(t_objet* objets)
{
    if(objets->j1->powerup->dep_sup->afficher==1)
    {
        blit(objets->j1->powerup->dep_sup->bulle,objets->niv->hitbox,0,0,
             objets->j1->powerup->dep_sup->posx-=objets->j1->powerup->dep_sup->depx,
             objets->j1->powerup->dep_sup->posy,
             objets->j1->powerup->dep_sup->bulle->w,
             objets->j1->powerup->dep_sup->bulle->h);
        masked_blit(objets->img->dep,objets->niv->buffer,0,0,
                    objets->j1->powerup->dep_sup->posx,objets->j1->powerup->dep_sup->posy,
                    objets->img->dep->w,objets->img->dep->h);
    }

}

void afficher_bonus_tir_sup(t_objet* objets)
{
    if(objets->j1->powerup->tir_sup->afficher==1)
    {
        blit(objets->j1->powerup->tir_sup->bulle,objets->niv->hitbox,0,0,
             objets->j1->powerup->tir_sup->posx-=objets->j1->powerup->tir_sup->depx,
             objets->j1->powerup->tir_sup->posy,
             objets->j1->powerup->tir_sup->bulle->w,
             objets->j1->powerup->tir_sup->bulle->h);
        masked_blit(objets->img->tir,objets->niv->buffer,0,0,
                    objets->j1->powerup->tir_sup->posx,objets->j1->powerup->tir_sup->posy,
                    objets->img->tir->w,objets->img->tir->h);
    }

}

void afficher_bonus_tourelle(t_objet *objets)
{
    if(objets->j1->powerup->tourelle->afficher==1)
    {
        blit(objets->j1->powerup->tourelle->bulle,objets->niv->hitbox,0,0,
             objets->j1->powerup->tourelle->posx-=objets->j1->powerup->tourelle->depx,
             objets->j1->powerup->tourelle->posy,
             objets->j1->powerup->tourelle->bulle->w,
             objets->j1->powerup->tourelle->bulle->h);
        masked_blit(objets->img->miss_tour,objets->niv->buffer,0,0,
                    objets->j1->powerup->tourelle->posx,objets->j1->powerup->tourelle->posy,
                    objets->img->miss_tour->w,objets->img->miss_tour->h);
    }
    if(objets->j1->powerup->tourelle->afficher_tourelle==1 && objets->j1->powerup->tourelle->cooldown>0)
    {
        if(objets->j1->powerup->tourelle->cooldown%100==0)
        {
            missile_teleguide_tourelle(objets->j1,objets);
        }
        objets->j1->powerup->tourelle->cooldown-=1;
        blit(objets->j1->powerup->tourelle->hitbox,objets->niv->hitbox,0,0,
             objets->j1->powerup->tourelle->posx,
             objets->j1->powerup->tourelle->posy,
             objets->j1->powerup->tourelle->bulle->w,
             objets->j1->powerup->tourelle->bulle->h);
        masked_blit(objets->img->miss_tour,objets->niv->buffer,0,0,
                    objets->j1->powerup->tourelle->posx,objets->j1->powerup->tourelle->posy,
                    objets->img->miss_tour->w,objets->img->miss_tour->h);

    }
    if(objets->j2->powerup->tourelle->afficher_tourelle==1 && objets->j2->powerup->tourelle->cooldown>0)
    {
        if(objets->j2->powerup->tourelle->cooldown%100==0)
        {
            missile_teleguide_tourelle(objets->j2,objets);
        }
        objets->j2->powerup->tourelle->cooldown-=1;
        blit(objets->j2->powerup->tourelle->hitbox,objets->niv->hitbox,0,0,
             objets->j2->powerup->tourelle->posx,
             objets->j2->powerup->tourelle->posy,
             objets->j2->powerup->tourelle->bulle->w,
             objets->j2->powerup->tourelle->bulle->h);
        masked_blit(objets->img->miss_tour,objets->niv->buffer,0,0,
                    objets->j2->powerup->tourelle->posx,objets->j2->powerup->tourelle->posy,
                    objets->img->miss_tour->w,objets->img->miss_tour->h);
    }
}

void afficher_bonus_missile_tele(t_objet* objets)
{
    if(objets->j1->powerup->missile_tele->bulle->afficher==1)
    {
        blit(objets->j1->powerup->missile_tele->bulle->bulle,objets->niv->hitbox,0,0,
             objets->j1->powerup->missile_tele->bulle->posx-=objets->j1->powerup->missile_tele->bulle->depx,
             objets->j1->powerup->missile_tele->bulle->posy,
             objets->j1->powerup->missile_tele->bulle->bulle->w,
             objets->j1->powerup->missile_tele->bulle->bulle->h);
        masked_blit(objets->img->miss_tele,objets->niv->buffer,0,0,
                    objets->j1->powerup->missile_tele->bulle->posx,objets->j1->powerup->missile_tele->bulle->posy,
                    objets->img->miss_tele->w,objets->img->miss_tele->h);
    }

}

void afficher_bonus_missile_rapide(t_objet* objets)
{
    if(objets->j1->powerup->missile_rapide->bulle->afficher==1)
    {
        blit(objets->j1->powerup->missile_rapide->bulle->bulle,objets->niv->hitbox,0,0,
             objets->j1->powerup->missile_rapide->bulle->posx-=objets->j1->powerup->missile_rapide->bulle->depx,
             objets->j1->powerup->missile_rapide->bulle->posy,
             objets->j1->powerup->missile_rapide->bulle->bulle->w,
             objets->j1->powerup->missile_rapide->bulle->bulle->h);
        masked_blit(objets->img->miss_rapi,objets->niv->buffer,0,0,
                    objets->j1->powerup->missile_rapide->bulle->posx,objets->j1->powerup->missile_rapide->bulle->posy,
                    objets->img->miss_rapi->w,objets->img->miss_rapi->h);
    }

}

void afficher_bonus_laser(t_objet* objets)
{
    if(objets->j1->powerup->laser->bulle->afficher==1)
    {
        blit(objets->j1->powerup->laser->bulle->bulle,objets->niv->hitbox,0,0,
             objets->j1->powerup->laser->bulle->posx-=objets->j1->powerup->laser->bulle->depx,
             objets->j1->powerup->laser->bulle->posy,
             objets->j1->powerup->laser->bulle->bulle->w,
             objets->j1->powerup->laser->bulle->bulle->h);
        masked_blit(objets->img->tir,objets->niv->buffer,0,0,
                    objets->j1->powerup->laser->bulle->posx,objets->j1->powerup->laser->bulle->posy,
                    objets->img->tir->w,objets->img->tir->h);
    }

}

void rayon_laser_geant_hoz(t_objet* objets,int y)//Créé un laser geant horizontal
{
    blit(objets->niv->laser,objets->niv->hitbox,0,0,0,y-objets->niv->laser->h/2,objets->niv->laser->w,objets->niv->laser->h);
    masked_stretch_blit(objets->img->glaser,objets->niv->buffer,0,0,objets->img->glaser->w,objets->img->glaser->h,-500,y-objets->niv->laser->h-objets->niv->laser->h,screen->w+500,4*objets->niv->laser->h);
}

void rayon_laser_geant_ver(t_objet* objets,int x)//Créé un laser geant vertical
{
    blit(objets->niv->laser_ver,objets->niv->hitbox,0,0,x-objets->niv->laser_ver->w/2,0,objets->niv->laser_ver->w,objets->niv->laser_ver->h);
    masked_stretch_blit(objets->img->laser_ver,objets->niv->buffer,0,0,objets->img->laser_ver->w,objets->img->laser_ver->h,x-objets->niv->laser_ver->w/2,0,objets->niv->laser_ver->w,screen->h);
}
void niveau(t_objet* objets,int *x)
{
//    clear(objets->niv->buffer);
//    scrolling(objets->niv->fond,objets->niv->buffer,x);
    objets->niv->x++;
    if(objets->niv->GameOver==1)
    {
        while(!key[KEY_ESC])
        {
            clear_to_color(objets->niv->buffer,makecol(255,255,255));
            BITMAP* partie_terminee=load_bitmap("Partie_terminee.bmp",NULL);
            //BITMAP* echap=load_bitmap("Echap.bmp",NULL);
            blit(partie_terminee,objets->niv->buffer,0,0,screen->w/2-partie_terminee->w/2,screen->h/3,partie_terminee->w,partie_terminee->h);
           // blit(echap,objets->niv->buffer,0,0,screen->w/2-echap->w/2,2*(screen->h/3),echap->w,echap->h);
            blit(objets->niv->buffer,screen,0,0,0,0,screen->w,screen->h);
            rest(3000);
            QuitterJeu();
        }
        objets->niv->GameOver=1;
    }
}

void scrolling(BITMAP* fond,BITMAP* buffer,int* x)
{
    blit(fond,buffer,(*x),0,0,0,screen->w,screen->h);
    if( (*x) +screen->w>fond->w)
        blit(fond,buffer,0,0,screen->w-(screen->w-(fond->w- (*x) )),0,screen->w,screen->h);
    if( (*x) >fond->w)
        (*x)=0;
    (*x) +=2;
//    blit(buffer,screen,0,0,0,0,screen->w,screen->h);
}

