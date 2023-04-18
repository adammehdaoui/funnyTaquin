#ifndef __TAQUIN__
#define __TAQUIN__

#include <MLV/MLV_all.h>

#define GAME "Taquin"
#define IMG_DIR "ressources/images/"
#define FONT_PATH "ressources/fonts/Montserrat.ttf"
#define SIZE_PATH 20
#define FONT_SIZE 15
#define NB_LIG 4
#define NB_COL 4

/**
 * @brief Image utilisée par défaut lorsque l'utilisateur ne spécifie pas d'image ou que l'image spécifiée n'existe pas.
 * 
 */
#define DEFAULT "hugo.jpg"

/**
 * @brief Taille de la fenêtre de jeu (résolution).
 * 
 */
#define RES 512

/**
 * @brief Taille d'une cellule dans la grille.
 * 
 */
#define CELL (int)RES/((NB_COL+NB_LIG)/2)

/**
 * @brief Nombre défini de manière statistique pour mélanger complètement le plateau de jeu
 * 
 */
#define MIX 120

/**
 * @brief Structure de données pour les cases du plateau.
 * 
 */
typedef struct Carre{
    int lig;
    int col;
} Carre ;

/**
 * @brief Structure de données pour le plateau (composé de cases qui sont des struct Carre).
 * 
 */
typedef struct Plateau {
    Carre bloc[NB_COL][NB_LIG];
} Plateau ;

/**
 * @brief Initalise le plateau de jeu. La fonction donne une valeur à la ligne/colonne de chaque case du plateau.
 * On notera également que la case n'étant pas censée être affichée prendra la valeur -1 en ligne et en colonne.
 * 
 * @param P 
 */
void initialisationPlateau(Plateau *P);

/**
 * @brief Mélange le plateau avec 120 déplacements aléatoires mais autorisés. On échange ainsi les valeur des lignes/colonnes
 * de la case noire avec une case voisine.
 * 
 * @param P 
 */
void mixPlateau(Plateau *P);

/**
 * @brief Fonction de raffraichissemnt du jeu. Elle affiche l'image de fond, la grille et les cases du plateau.
 * 
 * @param P 
 * @param img 
 */
void gameLoop(Plateau *P, MLV_Image *img);

/**
 * @brief Fonction permettant de composer les différents éléments du jeu. La fonction gère le jeu de bout en bout.
 * Elle sera donc la seule fonction appelée dans le main.
 * 
 * @param P 
 * @param img 
 */
void gameComp();

#endif