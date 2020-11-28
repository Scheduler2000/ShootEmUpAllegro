#include "usine.h"
#include <stdio.h>

t_objet* creer_objets()
{
    t_objet* objets=(t_objet*)malloc(sizeof(t_objet));

    objets->j1=creer_joueur();
    objets->j2=creer_joueur();
    objets->niv=creer_niveau();

    clear_to_color(objets->j2->hitbox,makecol(255,0,128));///La couleur de la hitbox de j2 est différentre pour différencier les joueurs

    //objets->j2->active=0;
    charger_images(objets);
    init_music(objets);
    init_tab_ennemi(objets);
    initialiser_tab_missile(objets);
    return  objets;
}

t_joueur* creer_joueur()
{
    t_joueur* j=(t_joueur*)malloc(sizeof(t_joueur));
    j->active=1;
    j->reapparition=200;
    j->depx=5;
    j->depy=5;
    j->hitbox=create_bitmap(30,30);
    clear_to_color(j->hitbox,makecol(255,0,255));
    j->posx=0;
    j->posy=screen->h/2;
    j->powerup=creer_bonus();
    j->taille_x=j->hitbox->w;///Le en haut à gauche du vaisseau est pris comme référence dans le reste du code
    j->taille_y=j->hitbox->h;
    j->vie=1;
    j->vie_restante=3;
    return j;
}

t_niveau* creer_niveau()
{
    t_niveau* niv=(t_niveau*)malloc(sizeof(t_niveau));

    niv->fond=creer_fond_n1();
    niv->buffer=create_bitmap(screen->w,screen->h);
    niv->hitbox=create_bitmap(screen->w,screen->h);
    niv->boss=(t_boss*)malloc(sizeof(t_boss));
    niv->laser=create_bitmap(screen->w,150);
    clear_to_color(niv->laser,makecol(27,253,27));
    niv->laser_ver=create_bitmap(400,screen->h);
    clear_to_color(niv->laser_ver,makecol(27,253,27));

    niv->x=0;//Met l'avancement du niveau à 0
    niv->couleur_ennemi=0;
    niv->couleur_missile=0;
    niv->GameOver=0;
    niv->compteur_laser=0;
    niv->niveau1=load_bitmap("niveau1.bmp",NULL);
    niv->niveau2=load_bitmap("niveau2.bmp",NULL);
    niv->niveau3=load_bitmap("niveau3.bmp",NULL);

    clear(niv->buffer);
    clear(niv->hitbox);
    return niv;
}

t_bonus* creer_bonus()
{
    t_bonus* b=(t_bonus*)malloc(sizeof(t_bonus));

    b->miss_norm=(t_missile_normal*)malloc(sizeof(t_missile_normal));
    b->missile_rapide=(t_missile_normal*)malloc(sizeof(t_missile_normal));
    b->laser=(t_laser*)malloc(sizeof(t_laser));
    b->missile_tele=(t_missile_tele*)malloc(sizeof(t_missile_tele));
    b->bouclier=(t_bouclier*)malloc(sizeof(t_bouclier));
    b->tourelle=(t_tourelle*)malloc(sizeof(t_tourelle));
    b->vie_sup=(t_sup*)malloc(sizeof(t_sup));
    b->dep_sup=(t_sup*)malloc(sizeof(t_sup));
    b->tir_sup=(t_sup*)malloc(sizeof(t_sup));
    b->missile_rapide->bulle=(t_bulle*)malloc(sizeof(t_bulle));
    b->laser->bulle=(t_bulle*)malloc(sizeof(t_bulle));
    b->missile_tele->bulle=(t_bulle*)malloc(sizeof(t_bulle));

    b->miss_norm->cooldown=0;
    b->miss_norm->possession=1;
    b->miss_norm->vitesse=7;
    b->miss_norm->hitbox=create_bitmap(10,5);
    clear_to_color(b->miss_norm->hitbox,makecol(255,0,0));

    b->missile_rapide->bulle->posx=screen->w;
    b->missile_rapide->bulle->posy=rand()%(screen->h);
    b->missile_rapide->bulle->depx=2;
    b->missile_rapide->bulle->afficher=0;
    b->missile_rapide->bulle->bulle=create_bitmap(20,20);
    clear_to_color(b->missile_rapide->bulle->bulle,makecol(55,55,55));
    b->missile_rapide->cooldown=0;
    b->missile_rapide->possession=0;
    b->missile_rapide->vitesse=13;
    b->missile_rapide->hitbox=create_bitmap(15,5);;
    clear_to_color(b->missile_rapide->hitbox,makecol(200,200,0));

    b->laser->bulle->posx=screen->w;
    b->laser->bulle->posy=rand()%(screen->h);
    b->laser->bulle->depx=2;
    b->laser->bulle->afficher=0;
    b->laser->bulle->bulle=create_bitmap(20,20);
    clear_to_color(b->laser->bulle->bulle,makecol(66,66,66));
    b->laser->cooldown=0;
    b->laser->tirs_restants=1;
    b->laser->possession=0;
    b->laser->hitbox=create_bitmap(screen->w,80);
    clear_to_color(b->laser->hitbox,makecol(200,200,200));

    b->missile_tele->bulle->posx=screen->w;
    b->missile_tele->bulle->posy=rand()%(screen->h);
    b->missile_tele->bulle->depx=2;
    b->missile_tele->bulle->afficher=0;
    b->missile_tele->bulle->bulle=create_bitmap(20,20);
    clear_to_color(b->missile_tele->bulle->bulle,makecol(77,77,77));
    b->missile_tele->cooldown=0;
    b->missile_tele->degats_restants=3;
    b->missile_tele->possession=0;
    b->missile_tele->vitesse=13;
    b->missile_tele->hitbox=create_bitmap(17,10);
    clear_to_color(b->missile_tele->hitbox,makecol(100,100,200));

    b->bouclier->afficher=0;
    b->bouclier->cooldown=0;
    b->bouclier->posx=screen->w;
    b->bouclier->posy=rand()%(screen->h);
    b->bouclier->depx=2;
    b->bouclier->bulle=create_bitmap(20,20);
    clear_to_color(b->bouclier->bulle,makecol(42,69,42));
    b->bouclier->hitbox=create_bitmap(32,32);
    clear_to_color(b->bouclier->hitbox,makecol(200,200,200));

    b->tourelle->afficher=0;
    b->tourelle->cooldown=0;
    b->tourelle->tir_restants=10;
    b->tourelle->depx=2;
    b->tourelle->posx=screen->w;
    b->tourelle->posy=rand()%(screen->h);
    b->tourelle->bulle=create_bitmap(20,20);
    clear_to_color(b->tourelle->bulle,makecol(84,138,84));
    b->tourelle->hitbox=create_bitmap(20,20);
    clear_to_color(b->tourelle->hitbox,makecol(123,45,67));

    b->vie_sup->afficher=0;
    b->vie_sup->depx=2;
    b->vie_sup->posx=screen->w;
    b->vie_sup->posy=rand()%(screen->h);
    b->vie_sup->bulle=create_bitmap(20,20);
    clear_to_color(b->vie_sup->bulle,makecol(168,21,168));

    b->dep_sup->afficher=0;
    b->dep_sup->depx=2;
    b->dep_sup->posx=screen->w;
    b->dep_sup->posy=rand()%(screen->h);
    b->dep_sup->bulle=create_bitmap(20,20);
    clear_to_color(b->dep_sup->bulle,makecol(81,42,81));

    b->tir_sup->afficher=0;
    b->tir_sup->depx=2;
    b->tir_sup->posx=screen->w;
    b->tir_sup->posy=rand()%(screen->h);
    b->tir_sup->possession=0;
    b->tir_sup->bulle=create_bitmap(20,20);
    clear_to_color(b->tir_sup->bulle,makecol(162,84,162));
    return b;
}

BITMAP* creer_fond_n1()
{
    BITMAP* desert=load_bitmap("desert.bmp",NULL);

    BITMAP* fond=create_bitmap(screen->w*(1280/(150*(4/3))),screen->h);

    stretch_blit(desert,fond,0,0,desert->w,desert->h,0,0,fond->w,fond->h);

    return fond;
}


void creer_ennemis_niveau_1(t_objet* objets)
{
    int i;
    objets->niv->niveau_actuel=1;
    for(i=0; i<10; i++)
        creer_lambda(objets);
    for(i=10; i<13; i++)
        creer_rapide(objets);
    for(i=13; i<15; i++)
        creer_nuee(objets);
    for(i=43; i<49; i++)
        creer_ciel(objets);
    for(i=49; i<53; i++)
        creer_rapide(objets);
    for(i=53; i<68; i++)
        creer_lambda(objets);
    for(i=68; i<72; i++)
        creer_suiveur(objets);
    char posx[6],posy[6];
    i=0;
    FILE* fp;
    fp=fopen("Positions_lvl1.txt","r");
    while(i<=71)
    {
        fgets(posx,6,fp);
        objets->niv->tab[i]->posx=atoi(posx);
        printf("%d\n",objets->niv->tab[i]->posx);
        i++;
    }
    i=0;
    while(i<=71)
    {
        fgets(posy,6,fp);
        objets->niv->tab[i]->posy=atoi(posy);
        printf("%d\n",objets->niv->tab[i]->posy);
        i++;
    }
    fclose(fp);
}

void creer_ennemis_niveau_2(t_objet* objets)
{
    int i;
    objets->niv->niveau_actuel=2;
    for(i=0; i<13; i++)
        creer_rapide(objets);
    for(i=13; i<18; i++)
        creer_lambda(objets);
    for(i=18; i<22; i++)
        creer_ciel(objets);
    creer_nuee(objets);
    for(i=37; i<40; i++)
        creer_suiveur(objets);
    i=0;
    char posx[6],posy[6];
    FILE* fp;
    fp=fopen("Positions_lvl2.txt","r");
    while(i<=39)
    {
        fgets(posx,6,fp);
        objets->niv->tab[i]->posx=atoi(posx);
        printf("%d\n",objets->niv->tab[i]->posx);
        i++;
    }
    i=0;
    while(i<=39)
    {
        fgets(posy,6,fp);
        objets->niv->tab[i]->posy=atoi(posy);
        printf("%d\n",objets->niv->tab[i]->posy);
        i++;
    }
    fclose(fp);
}

void creer_ennemis_niveau_3(t_objet* objets)
{
    int i;
    objets->niv->niveau_actuel=3;
    for(i=0; i<7; i++)
        creer_gros(objets);
    for(i=7; i<17; i++)
        creer_lambda(objets);
    for(i=17; i<23; i++)
        creer_ciel(objets);
    for(i=23; i<26; i++)
        creer_suiveur(objets);
    creer_nuee(objets);
    char posx[6],posy[6];
    FILE* fp;
    fp=fopen("Positions_lvl3.txt","r");
    i=0;
    while(i<=40)
    {
        fgets(posx,6,fp);
        objets->niv->tab[i]->posx=atoi(posx);
        printf("%d\n",objets->niv->tab[i]->posx);
        i++;
    }
    i=0;
    while(i<=40)
    {
        fgets(posy,6,fp);
        objets->niv->tab[i]->posy=atoi(posy);
        printf("%d\n",objets->niv->tab[i]->posy);
        i++;
    }
    fclose(fp);
}

void creer_nuee(t_objet* objets)
{
    int i=0,j,k;
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
            e->vie=0;
            clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
            e->posy=0;
            e->posx=0;
            objets->niv->tab[k]=e;
        }
    }
}

void creer_suiveur(t_objet* objets)
{
    int i=0;
    while(objets->niv->tab[i]!=NULL)
    {
        i++;
    }
    if(i<99)
    {
        t_ennemi* e=(t_ennemi*)malloc(sizeof(t_ennemi));
        e->type=suiveur;
        e->depx=3;
        e->depy=3;
        e->hitbox=create_bitmap(45,30);
        e->taille_x=e->hitbox->w;
        e->taille_y=e->hitbox->h;
        e->tir=0;
        e->vie=0;
        clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
        e->posy=0;
        e->posx=0;
        objets->niv->tab[i]=e;
    }
}

void creer_lambda(t_objet* objets)
{
    int i=0;
    while(objets->niv->tab[i]!=NULL)
    {
        i++;
    }
    if(i<99)
    {
        t_ennemi* e=(t_ennemi*)malloc(sizeof(t_ennemi));
        e->type=lambda;
        e->depx=3;
        e->depy=0;//Seulement pour cet annemi les deplacement en y nous donneront l'altitude initiale
        e->hitbox=create_bitmap(28,28);
        e->taille_x=e->hitbox->w;
        e->taille_y=e->hitbox->h;
        e->tir=0;
        e->vie=0;
        clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
        e->posy=0;
        e->posx=0;
        objets->niv->tab[i]=e;
    }
}

void creer_gros(t_objet* objets)
{
    int i=0;
    while(objets->niv->tab[i]!=NULL)
    {
        i++;
    }
    if(i<99)
    {
        t_ennemi* e=(t_ennemi*)malloc(sizeof(t_ennemi));
        e->type=gros;
        e->depx=1;
        e->depy=0;
        e->hitbox=create_bitmap(50,50);
        e->taille_x=e->hitbox->w;
        e->taille_y=e->hitbox->h;
        e->tir=200;
        e->vie=0;
        clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
        e->posy=0;
        e->posx=0;
        objets->niv->tab[i]=e;
    }
}

void creer_vaisseaux(t_objet* objets,int numero)
{
    int i=0,j,k;
    while(objets->niv->tab[i]!=NULL)
    {
        i++;
    }
    if(i<97)
    {
        j=i+3;
        for(k=i; k<j; k++)
        {
            t_ennemi* e=(t_ennemi*)malloc(sizeof(t_ennemi));
            e->type=nuee;
            e->depx=2;
            e->depy=0;
            e->hitbox=create_bitmap(10,14);
            e->taille_x=e->hitbox->w;
            e->taille_y=e->hitbox->h;
            e->tir=0;
            e->vie=1;
            clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
            e->posy=objets->niv->tab[numero]->posy-50+rand()%(objets->niv->tab[numero]->taille_y+100);
            e->posx=objets->niv->tab[numero]->posx-50+rand()%(objets->niv->tab[numero]->taille_x+100);//C'est une nuée d'ennemies donc ils n'apparaissent pas tous au meme endroit
            objets->niv->tab[k]=e;
        }
    }
}

void creer_rapide(t_objet* objets)
{
    int i=0;
    while(objets->niv->tab[i]!=NULL)
    {
        i++;
    }
    if(i<99)
    {
        t_ennemi* e=(t_ennemi*)malloc(sizeof(t_ennemi));
        e->type=rapide;
        e->depx=5;
        e->depy=0;
        e->hitbox=create_bitmap(25,21);
        e->taille_x=e->hitbox->w;
        e->taille_y=e->hitbox->h;
        e->tir=0;
        e->vie=0;
        clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
        e->posy=0;//Les coordonnées sont utiliés pour le boss final car pour tout le reste du jeu elles sont fixées dans un fichier
        e->posx=0;
        objets->niv->tab[i]=e;
    }
}

void creer_ciel(t_objet* objets)
{
    int i=0;
    while(objets->niv->tab[i]!=NULL)
    {
        i++;
    }
    if(i<99)
    {
        t_ennemi* e=(t_ennemi*)malloc(sizeof(t_ennemi));
        e->type=ciel;
        e->depx=5;
        e->depy=-5;
        e->hitbox=create_bitmap(20,10);
        e->taille_x=e->hitbox->w;
        e->taille_y=e->hitbox->h;
        e->tir=0;
        e->vie=0;
        clear_to_color(e->hitbox,makecol(0,objets->niv->couleur_ennemi++,125));
        e->posy=0;
        e->posx=0;
        objets->niv->tab[i]=e;
    }
}

void creer_boss_final(t_objet* objets)
{
    objets->niv->boss->depy=1;
    objets->niv->boss->depx=3;
    objets->niv->boss->hitbox=create_bitmap(288,288);//load_bitmap("boss_hit.bmp",NULL);
    clear_to_color(objets->niv->boss->hitbox,makecol(88,99,77));
    objets->niv->boss->posx=screen->w-310;
    objets->niv->boss->posy=screen->h/2-objets->niv->boss->hitbox->h/2;
    objets->niv->boss->vie=50;
    objets->niv->boss->phase=1;
}
