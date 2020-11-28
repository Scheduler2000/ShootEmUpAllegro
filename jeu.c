#include "jeu.h"

void lancer_niveau(int numero)
{
    t_objet* objets=creer_objets();
    srand(time(NULL));
    int x=0;
    objets->niv->avancement_fond=0;//Donne l'avancement du fond

    switch(numero)
    {
    case 1:
        creer_ennemis_niveau_1(objets);
        objets->niv->niveau_actuel=1;
        while(!key[KEY_ESC])
        {
            niveau(objets,&x);//Gère tous les objets du niveau ( affichage ennemis et collisions )
            actions(objets);
            ennemis_niveau_1(objets);
            rest(10);
        }
        break;
    case 2:
        creer_ennemis_niveau_2(objets);
        objets->niv->niveau_actuel=2;
        while(!key[KEY_ESC])
        {
            niveau(objets,&x);//Gère tous les objets du niveau ( affichage ennemis et collisions )
            actions(objets);
            ennemis_niveau_2(objets);
            rest(10);
        }
        break;
    case 3:
        creer_ennemis_niveau_3(objets);
        objets->niv->niveau_actuel=3;
        while(!key[KEY_ESC])
        {
            niveau(objets,&x);//Gère tous les objets du niveau ( affichage ennemis et collisions )
            actions(objets);
            ennemis_niveau_3(objets);
            rest(10);
        }
        break;
    }
}


void charger_images(t_objet* objets)
{
    objets->img=(t_images*)malloc(sizeof(t_images));
    objets->img->j1=load_bitmap("j1.bmp",NULL);
    objets->img->j2=load_bitmap("j1.bmp",NULL);
    objets->img->enboss=load_bitmap("boss.bmp",NULL);
    objets->img->enciel=load_bitmap("ciel.bmp",NULL);
    objets->img->engros=load_bitmap("gros.bmp",NULL);
    objets->img->enlamb=load_bitmap("lambda.bmp",NULL);
    objets->img->ennue=load_bitmap("nuee.bmp",NULL);
    objets->img->enrapi=load_bitmap("rapide.bmp",NULL);
    objets->img->ensuiv=load_bitmap("suiveur.bmp",NULL);
    objets->img->miss_laser=load_bitmap("laser.bmp",NULL);
    objets->img->miss_rapi=load_bitmap("missile_rapide.bmp",NULL);
    objets->img->miss_tele=load_bitmap("missile_tele.bmp",NULL);
    objets->img->miss_tour=load_bitmap("tourelle.bmp",NULL);
    objets->img->tir=load_bitmap("tir.bmp",NULL);
    objets->img->vie=load_bitmap("coeur.bmp",NULL);
    objets->img->dep=load_bitmap("dep.bmp",NULL);
    objets->img->bou=load_bitmap("dep.bmp",NULL);
    objets->img->jbou=load_bitmap("bouclier.bmp",NULL);
    objets->img->miss_norm=load_bitmap("missile.bmp",NULL);
    objets->img->plaser=create_bitmap(objets->j1->powerup->laser->hitbox->w,objets->j2->powerup->laser->hitbox->h/4);
    objets->img->mlaser=create_bitmap(objets->j1->powerup->laser->hitbox->w,objets->j2->powerup->laser->hitbox->h/2);
    objets->img->glaser=create_bitmap(objets->j1->powerup->laser->hitbox->w,objets->j2->powerup->laser->hitbox->h);
    objets->img->pre_laser=load_bitmap("pre_laser.bmp",NULL);
    objets->img->pre_laser_ver=load_bitmap("pre_laser_ver.bmp",NULL);
    objets->img->laser_ver=load_bitmap("laser_ver.bmp",NULL);
    stretch_blit(objets->img->miss_laser,objets->img->plaser,0,0,objets->img->miss_laser->w,objets->img->miss_laser->h,0,0,objets->j1->powerup->laser->hitbox->w,objets->j2->powerup->laser->hitbox->h/4);
    stretch_blit(objets->img->miss_laser,objets->img->mlaser,0,0,objets->img->miss_laser->w,objets->img->miss_laser->h,0,0,objets->j1->powerup->laser->hitbox->w,objets->j2->powerup->laser->hitbox->h/2);
    stretch_blit(objets->img->miss_laser,objets->img->glaser,0,0,objets->img->miss_laser->w,objets->img->miss_laser->h,0,0,objets->j1->powerup->laser->hitbox->w,objets->j2->powerup->laser->hitbox->h);

}

void init_tab_ennemi(t_objet* objets)
{
    int i;
    for(i=0; i<100; i++)
    {
        objets->niv->tab[i]=NULL;
    }
}

void initialiser_tab_missile(t_objet* objets)
{
    int i;
    for(i=0; i<20; i++)
    {
        objets->j1->elements[i]=NULL;
    }
    for(i=0; i<20; i++)
    {
        objets->j2->elements[i]=NULL;
    }
    objets->niv->couleur_missile=0;
}
