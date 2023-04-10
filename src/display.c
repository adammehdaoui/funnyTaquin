#include "../include/display.h"
#include "../include/taquin.h"

#include <MLV/MLV_all.h>

int display_win(Plateau *P){
    int i, j, flag = 0;

    for(i=0; i<(NB_LIG); i++){
        for (j=0; j<(NB_COL); j++){
            if(i==3 && j==3){
                /* on ne teste pas le dernier carreau */
            }
            else {
                if(P->bloc[i][j].lig != i || P->bloc[i][j].col !=j){
                    flag = 1;
                }
            }
        }
    }
    return flag;
}

void display_black_rectangle(int startX, int startY, int height, int width){
    MLV_draw_filled_rectangle(startX, startY, CELL, CELL, MLV_rgba(0, 0, 0, 255));
}

void display_game(Plateau *P, MLV_Image *image){
    int i, j, x, y, r, g, b, a, startX, startY, endX, endY;
    for(i=0; i<NB_LIG; i++){
        for(j=0; j<NB_COL; j++){

            startX = P->bloc[i][j].lig*(CELL);
            startY = P->bloc[i][j].col*(CELL);
            endX = startX+(CELL);
            endY = startY+(CELL);

            if(P->bloc[i][j].lig != -1){
            
                for(x=startX; x<endX; x++){
                    for(y=startY; y<endY; y++){
                        MLV_get_pixel_on_image(image, x, y, &r, &g, &b, &a);
                        MLV_draw_pixel(i*(CELL)+(x%(CELL)), j*(CELL)+(y%(CELL)), MLV_rgba(r, g, b, a));
                    }
                }
            }
            else{

                display_black_rectangle(i*CELL, j*CELL, CELL, CELL);
            }    
        }
    }
}

void display_grid(Plateau *P){
    int i, j, startX, startY;

    for(i=0; i<NB_LIG; i++){
        for(j=0; j<NB_COL; j++){
            startX = i*CELL;
            startY = j*CELL;

            MLV_draw_rectangle(startX, startY, CELL, CELL, MLV_rgba(0,0,0,255));
        }
    }
}