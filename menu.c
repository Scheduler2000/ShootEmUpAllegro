#include "menu.h"


BITMAP* LoadBitmap(char* fileName, int ratio) // Pour une resolution dynamique future ?
{
    BITMAP* image = load_bitmap(fileName,NULL);
    BITMAP* imageEnForme = create_bitmap(ratio == 1 ? image->w * 0.5 : SCREEN_W,
                                         ratio == 1 ? image->h * 0.5 : SCREEN_H);

    if(!image || !imageEnForme)
    {
        allegro_message("%s",allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    stretch_blit(image,imageEnForme,0,0,image->w,image->h,0,0,imageEnForme->w,imageEnForme->h);
    destroy_bitmap(image);
    return imageEnForme;
}

BITMAP* DessinerMenu(BITMAP* buffer)
{
    BITMAP* bmp = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* menuJeu = LoadBitmap("images/MenuBackground.bmp",0);
    BITMAP* titreJeu = LoadBitmap("images/TitreJeu.bmp",1);
    BITMAP* nouvellePart = LoadBitmap("images/NouvellePartie.bmp",1);
    BITMAP* chargerPart = LoadBitmap("images/ChargerPartie.bmp",1);
    BITMAP* reglagePart = LoadBitmap("images/Options.bmp",1);
    BITMAP* quitterPart = LoadBitmap("images/Quitter.bmp",1);
    int posX = 0, posY = 0;

    while(posX < SCREEN_W - (SCREEN_W / 4))
    {
        clear_bitmap(bmp);
        draw_sprite(bmp,menuJeu,0,0);
        draw_sprite(bmp,nouvellePart,SCREEN_W - posX,SCREEN_H * 0.2);
        draw_sprite(bmp,chargerPart,SCREEN_W - posX,SCREEN_H * 0.4);
        draw_sprite(bmp,reglagePart,SCREEN_W -posX,SCREEN_H * 0.6);
        draw_sprite(bmp,quitterPart,SCREEN_W - posX,SCREEN_H * 0.8);
        if(posY < 100 && posX > 420)
        {
            draw_sprite(bmp,titreJeu,screen->w/2 - (titreJeu->w/ 3),posY);
            posY += 1;
        }
        show_mouse(bmp);
        blit(bmp,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        posX += 10;
        rest(10);
    }
    destroy_bitmap(menuJeu);
    destroy_bitmap(titreJeu);
    destroy_bitmap(nouvellePart);
    destroy_bitmap(chargerPart);
    destroy_bitmap(reglagePart);
    destroy_bitmap(quitterPart);
    return bmp;
}

void AfficherMenu(BITMAP* buffer,t_choix* choixMenu)
{
    BITMAP* bmp = DessinerMenu(buffer);
    *choixMenu = None;
    do
    {
        clear(buffer);
        show_mouse(bmp);
        blit(bmp,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        *choixMenu = ChoixMenu(buffer);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    while(*choixMenu == None && !key[KEY_ESC]);
}

t_choix ChoixMenu(BITMAP* menu)
{
    t_choix choix = None;
    BITMAP* nouvellePart = LoadBitmap("images/NouvellePartie.bmp",1);
    BITMAP* chargerPart;
    BITMAP* reglagePart;
    BITMAP* quitterPart;
    int ratioX =  SCREEN_W / 3.85,largeur = 0,hauteur = 0,ratioY = 0;

    if(mouse_x > ratioX && mouse_x < ratioX + nouvellePart->w )
    {
        chargerPart = LoadBitmap("images/ChargerPartie.bmp",1);
        reglagePart = LoadBitmap("images/Options.bmp",1);
        quitterPart = LoadBitmap("images/Quitter.bmp",1);
        if(mouse_y > SCREEN_H / 4.8 && mouse_y < SCREEN_H / 4.8 + nouvellePart->h)
        {
            largeur = nouvellePart->w;
            hauteur = nouvellePart->h;
            ratioY = SCREEN_H / 4.8;
            if(mouse_b & 1)
                choix = NouvellePartie;
        }
        else if(mouse_y > SCREEN_H / 2.5 && mouse_y < SCREEN_H / 2.5  + chargerPart->h)
        {
            largeur = chargerPart->w;
            hauteur = chargerPart->h;
            ratioY = SCREEN_H / 2.5;
            if(mouse_b & 1)
                choix = ChargerPartie;
        }
        else if(mouse_y > SCREEN_H / 1.68 && mouse_y < SCREEN_H / 1.68  + reglagePart->h)
        {
            largeur = reglagePart->w;
            hauteur = reglagePart->h;
            ratioY = SCREEN_H / 1.68;
            if(mouse_b & 1)
                choix = Reglage;
        }
        else if(mouse_y > SCREEN_H / 1.25  && mouse_y < SCREEN_H / 1.25   + quitterPart->h)
        {
            largeur = quitterPart->w;
            hauteur = reglagePart->h;
            ratioY = SCREEN_H / 1.25;
            if(mouse_b & 1)
                choix = Quitter;
        }
        rect(menu,ratioX,ratioY,ratioX+largeur,ratioY+hauteur,makecol(255,0,0));
        destroy_bitmap(nouvellePart);
        destroy_bitmap(chargerPart);
        destroy_bitmap(reglagePart);
        destroy_bitmap(quitterPart);
    }
    return choix;
}

void AfficherReglage(BITMAP* buffer,t_reglalge* reglage)
{
    BITMAP* bmp = DessinerReglage(buffer);
    reglage->difficulte = None;
    reglage->volume = 0;
    do
    {
        clear(buffer);
        show_mouse(bmp);
        blit(bmp,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        ChoixReglage(buffer,reglage);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    while(reglage->difficulte == Nul || reglage->volume == 0);

}

void ChoixReglage(BITMAP* bmp,t_reglalge* reglage)
{
    int vol;
    if(mouse_x > 540)
    {
        if(mouse_x < 667 && mouse_y > 120 && mouse_y < 147) // 800x600
        {
            rect(bmp,540,120,667,147,makecol(0,255,0));
            if(mouse_b & 1)
            {
                reglage->difficulte = facile;
                allegro_message("Difficulte FACILE choisie !");
            }
        }
        if(mouse_x <730 && mouse_y > 180 && mouse_y < 220)
        {
            rect(bmp,540,180,730,220,makecol(223,109,20));
            if(mouse_b & 1)
            {
                reglage->difficulte = moyen;
                allegro_message("Difficulte MOYENNE choisie !");
            }
        }
        if(mouse_x <708 && mouse_y > 250 && mouse_y < 285)
        {
            rect(bmp,540,250,708,285,makecol(255,0,0));
            if(mouse_b & 1)
            {
                reglage->difficulte = difficile;
                allegro_message("Difficulte DIFFICILE choisie !");
            }
        }
        if(mouse_x <775 && mouse_y > 315 && mouse_y < 345)
        {
            rect(bmp,540,315,775,345,makecol(255,255,255));
            if(mouse_b & 1)
            {
                reglage->difficulte = adaptatif;
                allegro_message("Difficulte ADAPTATIVE choisie !");
            }
        }
    }
    if(mouse_y > 480 && mouse_y < 500 && mouse_x > 210 && mouse_x < 690) // progressBar
    {
        rectfill(bmp,210,480,mouse_x,500,makecol(0,255,0));
        if(mouse_b & 1)
        {
            vol = ( (mouse_x - 210) * 255 ) / 690; // Percentage mit sur 177 pq comme sa :)
            reglage->volume = vol * 100 / 177;
            allegro_message("Volume : %d pourcent",reglage->volume);
        }
    }
}
BITMAP* DessinerReglage(BITMAP* buffer)
{
    BITMAP* bmp = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* menuJeu = LoadBitmap("images/MenuBackground.bmp",0);
    BITMAP* titreOptions = LoadBitmap("images/Options.bmp",1);
    BITMAP* difficulte = LoadBitmap("images/Difficulte.bmp",1);
    BITMAP* volume = LoadBitmap("images/Volume.bmp",1);
    BITMAP* son = LoadBitmap("images/ProgressBarSon.bmp",1);
    int posX = 0, posY = 0;

    while(posX < SCREEN_W - (SCREEN_W / 4))
    {
        clear_bitmap(bmp);
        draw_sprite(bmp,menuJeu,0,0);
        draw_sprite(bmp,difficulte,SCREEN_W - (posX + SCREEN_W /4),SCREEN_H * 0.2);
        draw_sprite(bmp,volume,SCREEN_W -(posX + SCREEN_W /4),SCREEN_H * 0.8);
        draw_sprite(bmp,son,SCREEN_W - posX,SCREEN_H * 0.8);
        if(posY < 100 && posX > 420)
        {
            draw_sprite(bmp,titreOptions,screen->w/2 - (titreOptions->w/ 3),posY);
            posY += 1;
        }
        show_mouse(bmp);
        blit(bmp,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        posX += 10;
        rest(10);
    }
    destroy_bitmap(menuJeu);
    destroy_bitmap(titreOptions);
    destroy_bitmap(difficulte);
    destroy_bitmap(volume);
    destroy_bitmap(son);

    return bmp;
}

void QuitterJeu() // Save à ajouter du coup ?
{
    allegro_message("Fermeture du jeu en cours...");
    rest(500);
    allegro_exit();
    exit(EXIT_SUCCESS);
}

void InitialiserAllegro()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());

    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0) != 0)
    {
        allegro_message("Erreur initialisation mode graphique.");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}


BITMAP* DessinerChargerPartie(BITMAP* buffer)
{
    BITMAP* bmp = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* menuJeu = LoadBitmap("images/MenuBackground.bmp",0);
    BITMAP* chargerPartie = LoadBitmap("images/ChargerPartie.bmp",1);
    BITMAP* niveaux = LoadBitmap("images/ChoixNiveau.bmp",1);
    BITMAP* quitterPart = LoadBitmap("images/Quitter.bmp",1);
    int posX = 0, posY = 0;

    while(posX < SCREEN_W - (SCREEN_W / 4))
    {
        clear_bitmap(bmp);
        draw_sprite(bmp,menuJeu,0,0);
        draw_sprite(bmp,niveaux,SCREEN_W - (posX + SCREEN_W /4),SCREEN_H * 0.2);
        draw_sprite(bmp,quitterPart,SCREEN_W - (posX + SCREEN_W /4),SCREEN_H * 0.8);
        if(posY < 100 && posX > 420)
        {
            draw_sprite(bmp,chargerPartie,screen->w/2 - (chargerPartie->w/ 3),posY);
            posY += 1;
        }
        show_mouse(bmp);
        blit(bmp,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        posX += 10;
        rest(10);
    }
    destroy_bitmap(menuJeu);
    destroy_bitmap(chargerPartie);
    destroy_bitmap(niveaux);
    destroy_bitmap(quitterPart);
    return bmp;
}
void AfficherChargerPartie(BITMAP* buffer, int* niv)
{
    BITMAP* bmp = DessinerChargerPartie(buffer);
    while(*niv == 0)
    {

        clear(buffer);
        show_mouse(bmp);
        blit(bmp,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                ChoixChargerPartie(buffer, niv);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        if(mouse_b & 1)
            printf("(%d,%d)\n",mouse_x,mouse_y);
    }
}
void ChoixChargerPartie(BITMAP* buffer, int* niv)
{
  // 800x600
  if(mouse_x > 440)
  {
      if(mouse_x < 785 && mouse_y > 130 && mouse_y < 160)
         {
            rect(buffer,440,130,785,160,makecol(200,012,21));
            if(mouse_b & 1)
            *niv = 1;
         }
      if(mouse_x < 740 && mouse_y > 210 && mouse_y < 240)
        {
            rect(buffer,440,210,740,240,makecol(200,012,21));
             if(mouse_b & 1)
            *niv = 2;
        }
     if(mouse_x < 670 && mouse_y > 280 && mouse_y < 319)
     {
         rect(buffer,440,280,670,319,makecol(200,012,21));
        if(mouse_b & 1)
         *niv = 3;
     }
  }
  if(mouse_x >= 15 && mouse_x <= 212 && mouse_y > 480 && mouse_y < 510)
  {
      rect(buffer,15,480,212,510,makecol(0,255,0));
      if(mouse_b & 1)
        QuitterJeu();
  }
}
