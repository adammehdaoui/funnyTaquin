#ifndef __DISPLAY__
#define __DISPLAY__

#include <MLV/MLV_all.h>

#include "taquin.h"

int display_win(Plateau *P);
void display_black_rectangle(int startX, int startY, int height, int width);
void display_game(Plateau *P, MLV_Image* image);
void display_grid(Plateau *P);

#endif