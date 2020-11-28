#include "ennemie.h"


void ennemis_niveau_1(t_objet* objets)
{

    int i;
    if(objets->niv->x==1800)
        objets->j1->powerup->vie_sup->afficher=1;
    if(objets->niv->x==2300)
    {
        objets->j1->powerup->missile_tele->bulle->afficher=1;
        objets->j1->powerup->tourelle->afficher=1;
    }
    if(objets->niv->x==2000)
        objets->j1->powerup->bouclier->afficher=1;
    for(i=0; i<100; i++)
    {
        if(objets->niv->tab[i]!=NULL)
        {
            if(objets->niv->tab[i]->posx==objets->niv->x+screen->w && objets->niv->tab[i]->vie<=0)
            {
                switch(objets->niv->tab[i]->type)
                {
                case nuee:
                case lambda:
                case rapide:
                case ciel:
                    objets->niv->tab[i]->vie=1;
                    break;
                case suiveur:
                    objets->niv->tab[i]->vie=2;
                    break;
                case gros:
                    objets->niv->tab[i]->vie=4;
                    break;
                }
                objets->niv->tab[i]->posx=screen->w;
            }
        }
    }
    if(objets->niv->x>=4000) // WIN !!! :D
    {
        while(!key[KEY_ESC])
        {
            clear_to_color(objets->niv->buffer,makecol(255,255,255));
            BITMAP* partie_terminee=load_bitmap("Partie_terminee.bmp",NULL);
            BITMAP* echap=load_bitmap("Echap.bmp",NULL);
            blit(partie_terminee,objets->niv->buffer,0,0,screen->w/2-partie_terminee->w/2,screen->h/3,partie_terminee->w,partie_terminee->h);
            blit(echap,objets->niv->buffer,0,0,screen->w/2-echap->w/2,2*(screen->h/3),echap->w,echap->h);
            blit(objets->niv->buffer,screen,0,0,0,0,screen->w,screen->h);
        }
        objets->niv->GameOver=1;
    }
}

void ennemis_niveau_2(t_objet* objets)
{
    int i;
    if(objets->niv->x<screen->w+objets->niv->niveau2->w)
        masked_blit(objets->niv->niveau2,objets->niv->buffer,0,0,screen->w+objets->niv->niveau2->w-3*objets->niv->x,screen->h/2,objets->niv->niveau2->w,objets->niv->niveau2->h);
    if(objets->niv->x==2100)
        objets->j1->powerup->dep_sup->afficher=1;

//        //Cette partie régis les lasers géants
//    laser_geants(objets);

    for(i=0; i<100; i++)
    {
        if(objets->niv->tab[i]!=NULL)
        {
            if(objets->niv->tab[i]->posx==objets->niv->x+screen->w && objets->niv->tab[i]->vie<=0)
            {
                switch(objets->niv->tab[i]->type)
                {
                case nuee:
                case lambda:
                case rapide:
                case ciel:
                    objets->niv->tab[i]->vie=1;
                    break;
                case suiveur:
                    objets->niv->tab[i]->vie=2;
                    break;
                case gros:
                    objets->niv->tab[i]->vie=4;
                    break;
                }
                objets->niv->tab[i]->posx=screen->w;
            }
        }
    }
    if(objets->niv->x>=6500)
    {
        while(!key[KEY_ESC])
        {
            clear_to_color(objets->niv->buffer,makecol(255,255,255));
            BITMAP* partie_terminee=load_bitmap("Partie_terminee.bmp",NULL);
            BITMAP* echap=load_bitmap("Echap.bmp",NULL);
            blit(partie_terminee,objets->niv->buffer,0,0,screen->w/2-partie_terminee->w/2,screen->h/3,partie_terminee->w,partie_terminee->h);
            blit(echap,objets->niv->buffer,0,0,screen->w/2-echap->w/2,2*(screen->h/3),echap->w,echap->h);
            blit(objets->niv->buffer,screen,0,0,0,0,screen->w,screen->h);
        }
        objets->niv->GameOver=1;
    }
}

void laser_geants(t_objet* objets)
{
    if(objets->niv->x>=1800 && objets->niv->x<=2100)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,100,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,100);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=2500 && objets->niv->x<=2800)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,100,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,100);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=3100 && objets->niv->x<=3400)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,425,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,425);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=3600 && objets->niv->x<=4000)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,425,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,425);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=4000 && objets->niv->x<=4300)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,100,objets->img->pre_laser->w,objets->img->pre_laser->h);
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,250,objets->img->pre_laser->w,objets->img->pre_laser->h);
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,400,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,100);
            rayon_laser_geant_hoz(objets,250);
            rayon_laser_geant_hoz(objets,400);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=4500 && objets->niv->x<=4800)
    {
        masked_blit(objets->img->pre_laser_ver,objets->niv->buffer,0,0,screen->w/2,0,objets->img->pre_laser_ver->w,objets->img->pre_laser_ver->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_ver(objets,screen->w/2);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=4700 && objets->niv->x<=5000)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,200,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,screen->h/2);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=5100 && objets->niv->x<=5400)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,100,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,100);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=5300 && objets->niv->x<=5600)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,200,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,200);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=5500 && objets->niv->x<=5800)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,300,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,300);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=5700 && objets->niv->x<=6000)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,200,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,400);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }

}

void ennemis_niveau_3(t_objet* objets)
{
    int i;
    if(objets->niv->x<screen->w+objets->niv->niveau3->w)
        masked_blit(objets->niv->niveau3,objets->niv->buffer,0,0,screen->w+objets->niv->niveau3->w-3*objets->niv->x,screen->h/2,objets->niv->niveau3->w,objets->niv->niveau3->h);
    if(objets->niv->x==1800)
    {
        objets->j1->powerup->dep_sup->afficher=1;
        objets->j1->powerup->laser->bulle->afficher=1;
        objets->j1->powerup->missile_rapide->bulle->afficher=1;
        objets->j1->powerup->missile_tele->bulle->afficher=1;
        objets->j1->powerup->tir_sup->afficher=1;
        objets->j1->powerup->tourelle->afficher=1;
    }


    for(i=0; i<100; i++)
    {
        if(objets->niv->tab[i]!=NULL)
        {
            if(objets->niv->tab[i]->posx==objets->niv->x+screen->w && objets->niv->tab[i]->vie<=0)
            {
                switch(objets->niv->tab[i]->type)
                {
                case nuee:
                case lambda:
                case rapide:
                case ciel:
                    objets->niv->tab[i]->vie=1;
                    break;
                case suiveur:
                    objets->niv->tab[i]->vie=2;
                    break;
                case gros:
                    objets->niv->tab[i]->vie=4;
                    break;
                }
                objets->niv->tab[i]->posx=screen->w;
            }
        }
    }
    if(objets->niv->x>=5000 && objets->niv->boss->active==0 )
    {
        objets->niv->boss->active=1;
        creer_boss_final(objets);
    }
    if(objets->niv->x>=5500 && objets->niv->boss->vie<=0)
    {
        while(!key[KEY_ESC])
        {
            clear_to_color(objets->niv->buffer,makecol(255,255,255));
            BITMAP* partie_terminee=load_bitmap("Partie_terminee.bmp",NULL);
            BITMAP* echap=load_bitmap("Echap.bmp",NULL);
            blit(partie_terminee,objets->niv->buffer,0,0,screen->w/2-partie_terminee->w/2,screen->h/3,partie_terminee->w,partie_terminee->h);
            blit(echap,objets->niv->buffer,0,0,screen->w/2-echap->w/2,2*(screen->h/3),echap->w,echap->h);
            blit(objets->niv->buffer,screen,0,0,0,0,screen->w,screen->h);
        }
        objets->niv->GameOver=1;
    }
}

void laser_geants2(t_objet* objets)
{
    if(objets->niv->x>=2300 && objets->niv->x<=2600)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,200,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,200);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=3300 && objets->niv->x<=3600)
    {
        masked_blit(objets->img->pre_laser_ver,objets->niv->buffer,0,0,screen->w/2,0,objets->img->pre_laser_ver->w,objets->img->pre_laser_ver->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_ver(objets,screen->w/2);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=3700 && objets->niv->x<=4000)
    {
        masked_blit(objets->img->pre_laser_ver,objets->niv->buffer,0,0,screen->w/2,0,objets->img->pre_laser_ver->w,objets->img->pre_laser_ver->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_ver(objets,screen->w/2);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
    if(objets->niv->x>=3600 && objets->niv->x<=3900)
    {
        masked_blit(objets->img->pre_laser,objets->niv->buffer,0,0,0,400,objets->img->pre_laser->w,objets->img->pre_laser->h);
        objets->niv->compteur_laser++;
        if(objets->niv->compteur_laser>200)//Au bout de 2 secondes
        {
            rayon_laser_geant_hoz(objets,400);
        }
        if(objets->niv->compteur_laser>300)
            objets->niv->compteur_laser=0;
    }
}
