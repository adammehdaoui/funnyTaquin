#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#define NB_COL 4
#define NB_LIG 4
#define RES 512

#define GAME "Taquin"

typedef struct Carre{
    int lig;
    int col;
} Carre ;

typedef struct Plateau {
    Carre bloc[NB_COL][NB_LIG];
} Plateau ;

void initialisationPlateau(Plateau* P) {
    int i,j;
    for(i=0; i<NB_LIG; i++){
        for (j=0; j<NB_COL; j++){
            ((P->bloc)[i][j]).lig = i ;
            ((P->bloc)[i][j]).col = j ;
        }
    }
}

int pxToInd(int px){
    return (int)px/((int)RES/NB_COL);
}

void display_game(Plateau *P, MLV_Image *image){
    int i, j;
    int r, g, b, a;

    for(i=0; i<NB_LIG; i++){
        for(j=0; j<NB_COL; j++){

            int startX, startY, endX, endY;

            startX = i*((int)RES/NB_COL);
            startY = j*((int)RES/NB_COL);
            endX = startX + ((int)RES/NB_COL);
            endY = startY + ((int)RES/NB_COL);

            for(int x=startX; x<endX; x++){
                for(int y=startY; y<endY; y++){
                    MLV_get_pixel_on_image(image, x, y, &r, &g, &b, &a);
                    MLV_draw_pixel(x, y, MLV_convert_rgba_to_color(r, g, b, a));
                }
            }
        }
    }
}

void display_grid(){
}

int main(int argc, char *argv[]){
    Plateau board;
    initialisationPlateau(&board); 

    MLV_create_window(GAME, NULL, RES, RES); 	
    MLV_Image* image = MLV_load_image("image.jpg"); 

    display_game(&board, image);
    MLV_actualise_window();
    MLV_wait_seconds(10);
    MLV_free_window();

    return 0;
}