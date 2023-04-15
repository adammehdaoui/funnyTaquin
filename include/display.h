#ifndef __DISPLAY__
#define __DISPLAY__

#include <MLV/MLV_all.h>

#include "taquin.h"

/**
 * @brief Affiche un rectangle noir à l'emplacement donné. Le rectangle noir signifie que la case est vide, il s'agit
 * donc d'un coup possible.
 * 
 * @param startX 
 * @param startY 
 * @param height 
 * @param width 
 */
void display_black_rectangle(int startX, int startY, int height, int width);

/**
 * @brief Affiche l'état actuel du jeu. Cela consiste à afficher l'image de fond, puis les cases du plateau.
 * Cette fonction sera donc appelée à chaque boucle de raffraichissement de l'écran.
 * 
 * @param P 
 * @param image 
 */
void display_game(Plateau *P, MLV_Image* image);

/**
 * @brief Affiche la grille du jeu. Cette fonction sera appelée à chaque boucle de raffraichissement de l'écran 
 * après display_game.
 * 
 * @param P 
 */
void display_grid(Plateau *P);

/**
 * @brief Affiche un message de victoire lorsque le joueur a gagné. Ce message contient le temps mis par le joueur
 * pour résoudre le Taquin (d'où le paramètre start_t qui permettra de calculer la différence entre le temps de début
 * de jeu et de fin de jeu).
 * 
 * @param start_t 
 */
void display_win(time_t start_t);

#endif