#include "acteur.h"

void actions(t_objet* objets)
{
    int acceleration;
    if( key[KEY_UP] || key[KEY_DOWN] || key[KEY_LEFT] || key[KEY_RIGHT] || key[KEY_W] || key[KEY_A] || key[KEY_S] || key[KEY_D] )
        deplacer_joueur(objets);
    if( key[KEY_F] || key[KEY_G] || key[KEY_H] || key[KEY_J] || key[KEY_K] || key[KEY_M] || key[KEY_C] || key[KEY_N] || key[KEY_B] || key[KEY_V])
        actions_joueur(objets);
    if (objets->j2->powerup->laser->tirs_restants>0)
        laser(objets->j2,objets);
    if (objets->j1->powerup->laser->tirs_restants>0)
        laser(objets->j1,objets);
//Ici on gère tous les cooldowns des différentes attaques
    for(acceleration=0; acceleration<=objets->j1->powerup->tir_sup->possession; acceleration++)//Si on a le bonus d'accélération des tirs
    {
        if(objets->j1->powerup->miss_norm->cooldown>0)
            objets->j1->powerup->miss_norm->cooldown-=1;
        if(objets->j1->powerup->missile_rapide->cooldown>0)
            objets->j1->powerup->missile_rapide->cooldown-=1;
        if(objets->j1->powerup->missile_tele->cooldown>0)
            objets->j1->powerup->missile_tele->cooldown-=1;
        if(objets->j1->powerup->bouclier->cooldown>0)
            objets->j1->powerup->bouclier->cooldown-=1;
    }
    for(acceleration=0; acceleration<=objets->j2->powerup->tir_sup->possession; acceleration++)
    {
        if(objets->j2->powerup->miss_norm->cooldown>0)
            objets->j2->powerup->miss_norm->cooldown-=1;
        if(objets->j2->powerup->missile_rapide->cooldown>0)
            objets->j2->powerup->missile_rapide->cooldown-=1;

        if(objets->j2->powerup->missile_tele->cooldown>0)
            objets->j2->powerup->missile_tele->cooldown-=1;
        if(objets->j2->powerup->bouclier->cooldown>0)
            objets->j2->powerup->bouclier->cooldown-=1;
    }

    if(objets->j1->powerup->laser->cooldown>0)//Les cooldown des lasers ne rentrent pas dans les conditions car ils sont indépendants
        objets->j1->powerup->laser->cooldown-=1;
    if(objets->j2->powerup->laser->cooldown>0)
        objets->j2->powerup->laser->cooldown-=1;

    if(objets->j1->vie<=0 && objets->j1->vie_restante>0)//Si j1 est mort
    {
        objets->j1->reapparition--;
        if(objets->j1->reapparition==0)
        {
            objets->j1->reapparition=200;
            objets->j1->vie_restante--;
            objets->j1->vie=1;
            objets->j1->posx=0;
            objets->j1->posy=screen->h/2;
            objets->j1->powerup->bouclier->cooldown=300;
        }
    }
    if(objets->j2->vie<=0 && objets->j2->vie_restante>0)//Si j1 est mort
    {
        objets->j2->reapparition--;
        if(objets->j2->reapparition==0)
        {
            objets->j2->reapparition=200;
            objets->j2->vie_restante--;
            objets->j2->vie=1;
            objets->j2->posx=0;
            objets->j2->posy=screen->h/2;
            objets->j2->powerup->bouclier->cooldown=300;
        }
    }
    if(objets->j1->vie<=0 && objets->j1->vie_restante<=0 && objets->j2->active==0)
    {
        objets->niv->GameOver=1;
    }
    if(objets->j1->vie<=0 && objets->j1->vie_restante<=0 && objets->j2->vie<=0 && objets->j2->vie_restante<=0)
    {
        objets->niv->GameOver=1;
    }
    if(objets->niv->niveau_actuel==3 && objets->niv->boss->active==1)
    {
        deplacer_boss(objets);
    }


    collision(objets);

    afficher_tout(objets);
}

void deplacer_boss(t_objet* objets)
{
    int i=0,j,k;
    if(objets->niv->boss->posx<screen->w/2)
        objets->niv->boss->depx=-objets->niv->boss->depx;
    else if(objets->niv->boss->posx+objets->niv->boss->hitbox->w>screen->w)
        objets->niv->boss->depx=-objets->niv->boss->depx;
    if(objets->niv->boss->posy+objets->niv->boss->hitbox->h>screen->h)
        objets->niv->boss->depy=-objets->niv->boss->depy;
    else if(objets->niv->boss->posy<0)
        objets->niv->boss->depy=-objets->niv->boss->depy;
    objets->niv->boss->posx+=objets->niv->boss->depx;
    objets->niv->boss->posy+=objets->niv->boss->depy;

    if(objets->niv->boss->vie<30 && objets->niv->boss->phase==1)
    {
        objets->niv->boss->depx=3;
        objets->niv->boss->depy=3;
        objets->niv->boss->phase=2;
        while(objets->niv->tab[i]!=NULL)
        {
            i++;
        }
        if(i<84)
        {
            j=i+15;
            for(k=i; k<j; k++)
            {
                t_ennemi* e=(t_ennemi*)malloc(sizeof(t_ennemi));
                e->type=nuee;
                e->depx=3;
                e->depy=0;
                e->hitbox=create_bitmap(10,14);
                e->taille_x=e->hitbox->w;
                e->taille_y=e->hitbox->h;
                e->tir=0;
                e->vie=1;
                clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
                e->posy=rand()%(screen->h);
                e->posx=screen->w;
                objets->niv->tab[k]=e;
            }
        }
    }
    if(objets->niv->boss->vie<20 && objets->niv->boss->phase==2)
    {
        objets->niv->boss->depx=5;
        objets->niv->boss->depy=5;
        objets->niv->boss->phase=3;
        i=0;
        while(objets->niv->tab[i]!=NULL)
        {
            i++;
        }
        if(i<97)
        {
            t_ennemi* e=(t_ennemi*)malloc(sizeof(t_ennemi));
            e->type=suiveur;
            e->depx=3;
            e->depy=3;
            e->hitbox=create_bitmap(45,30);
            e->taille_x=e->hitbox->w;
            e->taille_y=e->hitbox->h;
            e->tir=0;
            e->vie=3;
            clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
            e->posy=rand()%(screen->h);
            e->posx=screen->w;
            objets->niv->tab[i]=e;

            i++;
            t_ennemi* a=(t_ennemi*)malloc(sizeof(t_ennemi));
            a->type=rapide;
            a->depx=3;
            a->depy=3;
            a->hitbox=create_bitmap(45,30);
            a->taille_x=a->hitbox->w;
            a->taille_y=a->hitbox->h;
            a->tir=0;
            a->vie=2;
            clear_to_color(a->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
            a->posy=rand()%(screen->h);
            a->posx=screen->w;
            objets->niv->tab[i]=a;

            i++;
            t_ennemi* b=(t_ennemi*)malloc(sizeof(t_ennemi));
            b->type=lambda;
            b->depx=3;
            b->depy=3;
            b->hitbox=create_bitmap(45,30);
            b->taille_x=b->hitbox->w;
            b->taille_y=b->hitbox->h;
            b->tir=0;
            b->vie=3;
            clear_to_color(b->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
            b->posy=rand()%(screen->h);
            b->posx=screen->w;
            objets->niv->tab[i]=b;
        }
    }
    if(objets->niv->boss->vie<=10 && objets->niv->boss->phase==3 && (objets->niv->x)%100==0)
    {
        objets->niv->boss->depx=rand()%6;
        objets->niv->boss->depy=rand()%6;
        i=0;
        while(objets->niv->tab[i]!=NULL)
        {
            i++;
        }
        if(i<97)
        {
            i++;
            t_ennemi* a=(t_ennemi*)malloc(sizeof(t_ennemi));
            a->type=rapide;
            a->depx=3;
            a->depy=3;
            a->hitbox=create_bitmap(45,30);
            a->taille_x=a->hitbox->w;
            a->taille_y=a->hitbox->h;
            a->tir=0;
            a->vie=2;
            clear_to_color(a->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
            a->posy=rand()%(screen->h);
            a->posx=screen->w;
            objets->niv->tab[i]=a;

            i++;
            t_ennemi* b=(t_ennemi*)malloc(sizeof(t_ennemi));
            b->type=lambda;
            b->depx=3;
            b->depy=3;
            b->hitbox=create_bitmap(45,30);
            b->taille_x=b->hitbox->w;
            b->taille_y=b->hitbox->h;
            b->tir=0;
            b->vie=3;
            clear_to_color(b->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
            b->posy=rand()%(screen->h);
            b->posx=screen->w;
            objets->niv->tab[i]=b;
        }
    }
}

void deplacer_joueur(t_objet* objets)
{
    if(objets->j1->vie>0)
    {
        if ( key[KEY_UP] && (!(objets->j1->posy-objets->j1->depy<0)) && (objets->j1->active==1) )
            objets->j1->posy-=objets->j1->depy;

        if ( key[KEY_DOWN] && (!(objets->j1->posy+objets->j1->taille_y+objets->j1->depx>screen->h)) && (objets->j1->active==1) )
            objets->j1->posy+=objets->j1->depy;

        if ( key[KEY_RIGHT] && (!(objets->j1->posx+objets->j1->taille_x+objets->j1->depx>screen->w)) && (objets->j1->active==1) )
            objets->j1->posx+=objets->j1->depx;

        if ( key[KEY_LEFT] && (!(objets->j1->posx-objets->j1->depx<0)) && (objets->j1->active==1) )
            objets->j1->posx-=objets->j1->depx;
    }
    if(objets->j2->vie>0)
    {
        if ( key[KEY_W] && (!(objets->j2->posy-objets->j2->depy<0)) && (objets->j2->active==1) )
            objets->j2->posy-=objets->j2->depy;

        if ( key[KEY_S] && (!(objets->j2->posy+objets->j2->taille_y+objets->j2->depx>screen->h)) && (objets->j2->active==1) )
            objets->j2->posy+=objets->j2->depy;

        if ( key[KEY_D] && (!(objets->j2->posx+objets->j2->taille_x+objets->j2->depx>screen->w)) && (objets->j2->active==1) )
            objets->j2->posx+=objets->j2->depx;

        if ( key[KEY_A] && (!(objets->j2->posx-objets->j2->depx<0)) && (objets->j2->active==1) )
            objets->j2->posx-=objets->j2->depx;
    }
}

void actions_joueur(t_objet* objets)
{
    if(objets->j2->vie>0)
    {
        if (key[KEY_F])
            tir_normal(objets->j2,objets);
        if (key[KEY_G])
            tir_rapide(objets->j2,objets);
        if (key[KEY_C])
            missile_teleguide(objets->j2,objets);
        if (key[KEY_V])
            tourelle(objets->j2,objets);
    }
    if(objets->j1->vie>0)
    {
        if (key[KEY_J])
            tir_normal(objets->j1,objets);
        if (key[KEY_K])
            tir_rapide(objets->j1,objets);
        if (key[KEY_N])
            missile_teleguide(objets->j1,objets);
        if (key[KEY_B])
            tourelle(objets->j2,objets);
    }
}

void tourelle(t_joueur* j,t_objet* objets)
{
    if(j->powerup->tourelle->possession>0 && j->vie>0)
    {
        j->powerup->tourelle->posx=j->posx;
        j->powerup->tourelle->posy=j->posy;
        j->powerup->tourelle->afficher_tourelle=1;//On affiche la tourelle et pas la bulle de la tourelle
    }
}

void tir_rapide(t_joueur* j,t_objet* objets)
{
    int i=0;
    if( j->powerup->missile_rapide->possession==1 && j->powerup->missile_rapide->cooldown<=0)
    {
        while(j->elements[i]!=NULL)
        {
            i++;
        }
        j->elements[i]=(t_missile*)malloc(sizeof(t_missile));
        j->elements[i]->depx=j->powerup->missile_rapide->vitesse;
        j->elements[i]->depy=0;
        j->elements[i]->posx=(j->posx+(j->taille_x));
        j->elements[i]->posy=(j->posy+j->taille_y/2);
        j->elements[i]->taillex=objets->j1->powerup->missile_rapide->hitbox->w;
        j->elements[i]->tailley=objets->j1->powerup->missile_rapide->hitbox->w;
        j->elements[i]->degats_restants=1;
        j->powerup->missile_rapide->cooldown=200;///Temps en millisecondes
    }
}

void tir_normal(t_joueur* j,t_objet* objets)
{
    int i=0;
    if( j->powerup->miss_norm->possession==1 && j->powerup->miss_norm->cooldown<=0)
    {
        while(j->elements[i]!=NULL)
        {
            i++;
        }
        j->elements[i]=(t_missile*)malloc(sizeof(t_missile));
        j->elements[i]->depx=j->powerup->miss_norm->vitesse;
        j->elements[i]->depy=0;
        j->elements[i]->posx=(j->posx+(j->taille_x));
        j->elements[i]->posy=(j->posy+(objets->img->j1->h/2));
        j->elements[i]->taillex=objets->j1->powerup->miss_norm->hitbox->w;
        j->elements[i]->tailley=objets->j1->powerup->miss_norm->hitbox->w;
        j->elements[i]->degats_restants=1;
        j->powerup->miss_norm->cooldown=50;///Temps en millisecondes
    }
}

void laser(t_joueur* j,t_objet* objets)//Le programme laser est un peu sécial car il gere l'affichage du laser mais aussi ses collisions
{
    if(j==objets->j2 && objets->j2->vie>0)
    {
        if(key[KEY_H])//Si on reste appuyé sur le bouton
            objets->j2->powerup->laser->cooldown+=2;
        else if(objets->j2->powerup->laser->cooldown >= 100 && objets->j2->powerup->laser->cooldown <250)
        {
            objets->j2->powerup->laser->tirs_restants--;
            objets->j2->powerup->laser->cooldown--;
        }
        else if(objets->j2->powerup->laser->cooldown >= 250)
        {
            if(objets->j2->powerup->laser->cooldown>1000)
                objets->j2->powerup->laser->cooldown=1000;
            objets->j2->powerup->laser->cooldown-=2;
        }
    }
    if(j==objets->j1 && objets->j1->vie>0)
    {
        if(key[KEY_L])//Si on reste appuyé sur le bouton
            objets->j1->powerup->laser->cooldown+=2;
        else if(objets->j1->powerup->laser->cooldown >= 100 && objets->j1->powerup->laser->cooldown <250)
        {
            objets->j1->powerup->laser->tirs_restants--;
            objets->j1->powerup->laser->cooldown--;
        }
        else if(objets->j1->powerup->laser->cooldown >= 250)
        {
            if(objets->j1->powerup->laser->cooldown>1000)
                objets->j1->powerup->laser->cooldown=1000;
            objets->j1->powerup->laser->cooldown-=2;
        }
    }
}

void missile_teleguide(t_joueur* j,t_objet* objets)
{
    int i=0;
    if( j->powerup->missile_tele->possession==1 && j->powerup->missile_tele->cooldown<=0)
    {
        while(j->elements[i]!=NULL)
        {
            i++;
        }
        j->elements[i]=(t_missile*)malloc(sizeof(t_missile));
        j->elements[i]->depx=j->powerup->missile_tele->vitesse;
        j->elements[i]->depy=j->powerup->missile_tele->vitesse;
        j->elements[i]->posx=(j->posx+(j->taille_x)/2);
        j->elements[i]->posy=j->posy;
        j->elements[i]->taillex=objets->j1->powerup->missile_tele->hitbox->w;
        j->elements[i]->tailley=objets->j1->powerup->missile_tele->hitbox->w;
        j->elements[i]->degats_restants=objets->j1->powerup->missile_tele->degats_restants;
        j->elements[i]->cible=visee(objets,j->posx,j->posy);
        j->powerup->missile_tele->cooldown=125;///Temps en millisecondes
    }
}

void missile_teleguide_tourelle(t_joueur* j,t_objet* objets)
{
    int i=0;
    while(j->elements[i]!=NULL)
    {
        i++;
    }
    j->elements[i]=(t_missile*)malloc(sizeof(t_missile));
    j->elements[i]->depx=j->powerup->missile_tele->vitesse;
    j->elements[i]->depy=j->powerup->missile_tele->vitesse;
    j->elements[i]->posx=j->powerup->tourelle->posx+j->powerup->tourelle->hitbox->w;
    j->elements[i]->posy=j->powerup->tourelle->posy+j->powerup->tourelle->hitbox->h/2;
    j->elements[i]->taillex=objets->j1->powerup->missile_tele->hitbox->w;
    j->elements[i]->tailley=objets->j1->powerup->missile_tele->hitbox->w;
    j->elements[i]->degats_restants=3;
    j->elements[i]->cible=visee(objets,j->powerup->tourelle->posx,j->powerup->tourelle->posy);
}

int visee(t_objet* objets,int x,int y)
{
    //Le but de ce sous programmes est de viser l'ennemi le plus proche
    int numero=1000,i;///Dans le reste du programme une numéro = 1000 indique que aucun ennemi n'est visé
    double distance_min=100000,distance_new;
    for(i=0; i<100; i++)
    {
        if(objets->niv->tab[i]!=NULL)
        {
            if(objets->niv->tab[i]->vie>0 && objets->niv->tab[i]->posx < screen->w)
            {
                distance_new=( sqrt( (objets->niv->tab[i]->posx+x) * (objets->niv->tab[i]->posx+x) + (objets->niv->tab[i]->posy+y) * (objets->niv->tab[i]->posy+y) ) );//On prend l'hypothénuse
                if(distance_new<distance_min)
                {
                    numero=i;
                    distance_min=distance_new;
                }
            }
        }
    }
    return numero;// on retourne le numero de l'ennemi dans le tableau
}

void collision(t_objet* objets)
{
    int x,y,i,couleur,posy_lambda=(int)(60*sin((double)(objets->niv->x)/20));
    for(i=0; i<20; i++)//collision des missiles rapides j1
    {
        if(objets->j1->elements[i]!=NULL)
        {
            for(x=objets->j1->elements[i]->posx; x<=objets->j1->elements[i]->posx+objets->j1->elements[i]->taillex; x++)
            {
                for(y=objets->j1->elements[i]->posy; y<=objets->j1->elements[i]->posy+objets->j1->elements[i]->tailley; y++)
                {
                    couleur=getpixel(objets->niv->hitbox,x,y);
                    if(getr(couleur)==0 && getb(couleur)==125)//Si c'est la couleur d'un ennemi
                    {
                        objets->niv->tab[getg(couleur)]->vie--;
                        objets->j1->elements[i]->degats_restants--;
                        if(objets->j1->elements[i]->taillex==15)//Si c'est un missile rapide
                            objets->niv->tab[getg(couleur)]->vie-=2;
                        while(objets->niv->tab[getg(couleur)]->vie>0 && objets->j1->elements[i]->degats_restants>0)//Si il rest des points de vie à l'ennemie et des points de dégats au missile
                        {
                            objets->niv->tab[getg(couleur)]->vie--;
                            objets->j1->elements[i]->degats_restants--;
                        }
                        if(objets->j1->elements[i]->degats_restants>0)
                            objets->j1->elements[i]->cible=visee(objets,objets->j1->posx,objets->j1->posy);//Si il rest des points de dégats au missile alors il se dirige vers une nouvelle cible

                        y=objets->j1->elements[i]->posy+objets->j1->elements[i]->tailley;//On ferme la boucle si un ennemi est touché
                        x=objets->j1->elements[i]->posx+objets->j1->elements[i]->taillex;
                    }
                    if(couleur == makecol(88,99,77))
                    {
                        objets->niv->boss->vie--;
                        objets->j1->elements[i]->degats_restants--;
                        y=objets->j1->elements[i]->posy+objets->j1->elements[i]->tailley;//On ferme la boucle si le boss est touché
                        x=objets->j1->elements[i]->posx+objets->j1->elements[i]->taillex;
                    }
                }
            }
            if(objets->j1->elements[i]->degats_restants<=0)
                objets->j1->elements[i]=NULL;
        }
    }
    for(i=0; i<20; i++)//collision des missiles rapides j2
    {
        if(objets->j2->elements[i]!=NULL)
        {
            for(x=objets->j2->elements[i]->posx; x<=objets->j2->elements[i]->posx+objets->j2->elements[i]->taillex; x++)
            {
                for(y=objets->j2->elements[i]->posy; y<=objets->j2->elements[i]->posy+objets->j2->elements[i]->tailley; y++)
                {
                    couleur=getpixel(objets->niv->hitbox,x,y);
                    if(getr(couleur)==0 && getb(couleur)==125)//Si c'est la couleur d'un ennemi
                    {
                        objets->niv->tab[getg(couleur)]->vie--;
                        objets->j2->elements[i]->degats_restants--;
                        if(objets->j2->elements[i]->taillex==15)//Si c'est un missile rapide
                            objets->niv->tab[getg(couleur)]->vie-=2;
                        while(objets->niv->tab[getg(couleur)]->vie>0 && objets->j2->elements[i]->degats_restants>0)//Si il rest des points de vie à l'ennemie et des points de dégats au missile
                        {
                            objets->niv->tab[getg(couleur)]->vie--;
                            objets->j2->elements[i]->degats_restants--;
                        }
                        if(objets->j2->elements[i]->degats_restants>0)
                            objets->j2->elements[i]->cible=visee(objets,objets->j2->posx,objets->j2->posy);//Si il rest des points de dégats au missile alors il se dirige vers une nouvelle cible

                        y=objets->j2->elements[i]->posy+objets->j2->elements[i]->tailley;//On ferme la boucle si un ennemi est touché
                        x=objets->j2->elements[i]->posx+objets->j2->elements[i]->taillex;
                    }
                    if(couleur == makecol(88,99,77))
                    {
                        objets->niv->boss->vie--;
                        objets->j2->elements[i]->degats_restants--;
                        y=objets->j2->elements[i]->posy+objets->j2->elements[i]->tailley;//On ferme la boucle si le boss est touché
                        x=objets->j2->elements[i]->posx+objets->j2->elements[i]->taillex;
                    }
                }
            }
            if(objets->j2->elements[i]->degats_restants<=0)
                objets->j2->elements[i]=NULL;
        }
    }
    for(i=0; i<100; i++)
    {
        if(objets->niv->tab[i]!=NULL)//Collsion des ennemis
        {
            if(objets->niv->tab[i]->vie>0)
            {
                for(x=objets->niv->tab[i]->posx; x<=objets->niv->tab[i]->posx+objets->niv->tab[i]->taille_x; x++)
                {
                    if(objets->niv->tab[i]->type==lambda)
                    {
                        for(y=objets->niv->tab[i]->posy+posy_lambda; y<=objets->niv->tab[i]->posy+posy_lambda+objets->niv->tab[i]->taille_y; y++)
                        {
                            if(getpixel(objets->niv->hitbox,x,y)==makecol(200,200,200) || objets->niv->tab[i]->posx+objets->niv->tab[i]->depx+objets->niv->tab[i]->taille_x<0)//SI l'ennemi est sur du presque blanc
                                objets->niv->tab[i]->vie--;
                        }
                    }

                    else
                        for(y=objets->niv->tab[i]->posy; y<=objets->niv->tab[i]->posy+objets->niv->tab[i]->taille_y; y++)
                        {
                            if(getpixel(objets->niv->hitbox,x,y)==makecol(200,200,200) || objets->niv->tab[i]->posx+objets->niv->tab[i]->depx+objets->niv->tab[i]->taille_x<0)//SI l'ennemi est sur du presque blanc
                            {
                                objets->niv->tab[i]->vie--;
                            }
                        }
                }
            }
        }
    }
    if(objets->j1->active==1)//Collision du j1
    {
        for(x=objets->j1->posx; x<=objets->j1->posx+objets->j1->hitbox->w; x++)
        {
            for(y=objets->j1->posy; y<=objets->j1->posy+objets->j1->hitbox->h; y++)
            {
                couleur=getpixel(objets->niv->hitbox,x,y);
                if( getr(couleur)==0 && getb(couleur)==125 && objets->j1->powerup->bouclier->cooldown<=0)// Si le joueur rentre en collision avec un ennemi
                    objets->j1->vie--;
                if( getr(couleur)==255 && getg(couleur)==254 && objets->j1->powerup->bouclier->cooldown<=0)//Si le joueur rentre en collision avec un tir ennemi
                    objets->j1->vie--;
                if( couleur==makecol(42,69,42) )
                {
                    objets->j1->powerup->bouclier->cooldown=500;
                    objets->j1->powerup->bouclier->afficher=0;
                }
                if( couleur==makecol(84,138,84) )
                {
                    objets->j1->powerup->tourelle->possession=1;
                    objets->j1->powerup->tourelle->cooldown=1000;
                    objets->j1->powerup->tourelle->afficher=0;
                }
                if( couleur==makecol(168,21,168) )
                {
                    objets->j1->powerup->vie_sup->afficher=0;
                    objets->j1->vie_restante=3;
                }
                if( couleur==makecol(81,42,81) )
                {
                    objets->j1->powerup->dep_sup->afficher=0;
                    objets->j1->depx=8;
                    objets->j1->depy=8;
                }
                if( couleur==makecol(162,84,162) )
                {
                    objets->j1->powerup->tir_sup->afficher=0;
                    objets->j1->powerup->tir_sup->possession=1;
                }
                if( couleur==makecol(55,55,55) )
                {
                    objets->j1->powerup->missile_rapide->bulle->afficher=0;
                    objets->j1->powerup->missile_rapide->possession=1;
                }
                if (couleur ==makecol(66,66,66))
                {
                    objets->j1->powerup->laser->bulle->afficher=0;
                    objets->j1->powerup->laser->possession=1;
                    objets->j1->powerup->laser->tirs_restants++;
                }
                if( couleur==makecol(77,77,77) )
                {
                    objets->j1->powerup->missile_tele->bulle->afficher=0;
                    objets->j1->powerup->missile_tele->possession=1;
                }
                if( couleur==makecol(27,253,27) || couleur==makecol(88,99,77))
                {
                    objets->j1->vie--;
                }
            }
        }
    }
    if(objets->j2->active==1)//Collision du j2
    {
        for(x=objets->j2->posx; x<=objets->j2->posx+objets->j2->hitbox->w; x++)
        {
            for(y=objets->j2->posy; y<=objets->j2->posy+objets->j2->hitbox->h; y++)
            {
                couleur=getpixel(objets->niv->hitbox,x,y);
                if( getr(couleur)==0 && getb(couleur)==125 && objets->j2->powerup->bouclier->cooldown<=0)// Si le joueur rentre en collision avec un ennemi
                    objets->j2->vie--;
                if( getr(couleur)==255 && getg(couleur)==254 && objets->j2->powerup->bouclier->cooldown<=0)//Si le joueur rentre en collision avec un tir ennemi
                    objets->j2->vie--;
                if( couleur==makecol(42,69,42) )
                {
                    objets->j2->powerup->bouclier->cooldown=500;
                    objets->j1->powerup->bouclier->afficher=0;
                }
                if( couleur==makecol(84,138,84) )
                {
                    objets->j2->powerup->tourelle->possession=1;
                    objets->j2->powerup->tourelle->cooldown=1000;
                    objets->j1->powerup->tourelle->afficher=0;
                }
                if( couleur==makecol(168,21,168) )
                {
                    objets->j1->powerup->vie_sup->afficher=0;
                    objets->j2->vie_restante++;
                }
                if( couleur==makecol(81,42,81) )
                {
                    objets->j1->powerup->dep_sup->afficher=0;
                    objets->j2->depx=8;
                    objets->j2->depy=8;
                }
                if( couleur==makecol(162,84,162) )
                {
                    objets->j1->powerup->tir_sup->afficher=0;
                    objets->j2->powerup->tir_sup->possession=1;
                }
                if( couleur==makecol(55,55,55) )
                {
                    objets->j1->powerup->missile_rapide->bulle->afficher=0;
                    objets->j2->powerup->missile_rapide->possession=1;
                }
                if (couleur ==makecol(66,66,66))
                {
                    objets->j1->powerup->laser->bulle->afficher=0;
                    objets->j2->powerup->laser->possession=1;
                    objets->j2->powerup->laser->tirs_restants++;
                }
                if( couleur==makecol(77,77,77) )
                {
                    objets->j1->powerup->missile_tele->bulle->afficher=0;
                    objets->j2->powerup->missile_tele->possession=1;
                }
                if( couleur==makecol(27,253,27) || couleur==makecol(88,99,77))
                {
                    objets->j2->vie--;
                }
            }
        }
    }
}

