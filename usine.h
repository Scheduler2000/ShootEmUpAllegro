#ifndef __USINE__
#define __USINE__
#include <allegro.h>

typedef enum type
{
    suiveur,nuee,gros,lambda,rapide,ciel
} t_type;

typedef struct ennemi
{
    BITMAP* hitbox;
    int depx;
    int depy;
    int vie;
    int tir;
    int posx;
    int posy;
    int taille_x;
    int taille_y;
    int type;
} t_ennemi;

typedef struct missile
{
    int posx;
    int posy;
    int depx;
    int depy;
    int taillex;
    int tailley;
    int degats_restants;
    int cible;//Utilisé seulement pour les missiles téléguidés
} t_missile;

typedef struct bulle
{
    int posx,posy,depx;
    int afficher;
    BITMAP* bulle;
} t_bulle;

typedef struct missile_normal
{
    int possession;
    int vitesse;
    int cooldown;
    BITMAP* hitbox;
    t_bulle* bulle;
} t_missile_normal;

typedef struct laser
{
    int possession;
    int tirs_restants;
    int cooldown;
    BITMAP* hitbox;
    t_bulle* bulle;
} t_laser;

typedef struct missile_tele
{
    int possession,cooldown;
    int vitesse;
    int degats_restants;
    BITMAP* hitbox;
    t_bulle* bulle;
} t_missile_tele;

typedef struct bouclier
{
    BITMAP* hitbox;
    BITMAP* bulle;//bulle represente le bonus avant d'être attrapé
    int afficher;
    int cooldown;
    int posx,posy;
    int depx;
} t_bouclier;

typedef struct tourelle
{
    int posx,posy,depx;
    int tir_restants,cooldown,afficher,possession,afficher_tourelle;
    BITMAP*bulle,*hitbox;
} t_tourelle;

typedef struct sup//Utilisé pour tous les bonus splémentairs
{
    int posx,posy,depx,possession;
    int afficher;
    BITMAP* bulle;
} t_sup;

typedef struct bonus
{
    t_sup* vie_sup;//Accorde une vie supplémentaire
    t_sup* dep_sup;//Augmente la vitesse de déplacement
    t_sup* tir_sup;//Augmente la cadence de tir
    t_bouclier* bouclier;
    t_missile_normal* miss_norm;
    t_missile_tele* missile_tele;
    t_missile_normal* missile_rapide;
    t_laser* laser;
    t_tourelle* tourelle;
} t_bonus;

typedef struct boss
{
    int depx,depy,posx,posy;
    int vie,phase,active;
    BITMAP* hitbox;
} t_boss;

typedef struct niveau
{
    t_ennemi* tab[101];
    int diff;
    BITMAP* hitbox;
    BITMAP* buffer;
    BITMAP* fond;
    t_boss* boss;
    int niveau_actuel;
    int x;
    int couleur_ennemi;//Change de couleur pour chaque ennemi pour les différenciers
    int couleur_missile;//change de couleur pour différencier les différents tirs
    int GameOver;//Indique si la partie est finie ( pas forcement si on a perdu )
    int compteur_laser;//Ce compteur sert à faire un décompte pour afficher le rayon laser géant
    SAMPLE* musique;
    BITMAP* niveau1,*niveau2,*niveau3,*laser,*laser_ver;
    int avancement_fond;
} t_niveau;

typedef struct joueur
{
    int active;
    int vie;
    int vie_restante;
    int reapparition;
    int posx;
    int posy;
    int depx;
    int depy;
    int taille_x;
    int taille_y;
    t_missile* elements[20];
    t_bonus* powerup;
    BITMAP* hitbox;
} t_joueur;

typedef struct images
{
    BITMAP* j1,*j2,*jbou;
    BITMAP* ensuiv,*ennue,*engros,*enlamb,*enrapi,*enciel;
    BITMAP* enboss,*vie,*dep,*tir,*bou,*miss_tele,*miss_rapi,*miss_laser,*miss_norm,*miss_tour,*plaser,*mlaser,*glaser,*pre_laser,*pre_laser_ver,*laser_ver;
} t_images;

typedef struct objet
{
    t_joueur* j1;
    t_joueur* j2;
    t_niveau* niv;
    t_images* img;
} t_objet;



t_objet* creer_objets();
t_joueur* creer_joueur();
t_niveau* creer_niveau();
t_bonus* creer_bonus();
BITMAP* creer_fond_n1();

void creer_nuee(t_objet* objets);
void creer_suiveur(t_objet* objets);
void creer_gros(t_objet* objets);
void creer_rapide(t_objet* objets);
void creer_lambda(t_objet* objets);
void creer_ciel(t_objet* objets);

void creer_ennemis_niveau_1(t_objet* objets);
void creer_ennemis_niveau_2(t_objet* objets);
void creer_ennemis_niveau_3(t_objet* objets);
void creer_boss_final(t_objet* objets);

#endif // __USINE__
