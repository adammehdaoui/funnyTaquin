#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#define GAME "Taquin"
#define NB_LIG 4
#define NB_COL 4
#define RES 512
#define CELL (int)RES/((NB_COL+NB_LIG)/2)

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
            ((P->bloc)[i][j]).lig = i;
            ((P->bloc)[i][j]).col = j;
        }
    }
}

void mixPlateau(Plateau* P){
}

void display_game(Plateau *P, MLV_Image *image){
    int i, j, r, g, b, a, startX, startY, endX, endY;

    for(i=0; i<NB_LIG; i++){
        for(j=0; j<NB_COL; j++){

            startX = i*CELL;
            startY = j*CELL;
            endX = startX+CELL;
            endY = startY+CELL;

            for(int x=startX; x<endX; x++){
                for(int y=startY; y<endY; y++){
                    MLV_get_pixel_on_image(image, x, y, &r, &g, &b, &a);
                    MLV_draw_pixel(x, y, MLV_rgba(r, g, b, a));
                }
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

void display_black_rectangle(int startX, int startY, int height, int width){
    MLV_draw_filled_rectangle(startX, startY, CELL, CELL, MLV_rgba(0, 0, 0, 255));
}

int main(int argc, char *argv[]){
    Plateau board;
    initialisationPlateau(&board); 

    board.bloc[3][3].lig = NULL;
    board.bloc[3][3].col = NULL;

    int x, y, i, j;

    MLV_create_window(GAME, NULL, RES, RES); 	
    MLV_Image* image = MLV_load_image("data/image.jpg"); 
    if (!image) {
        fprintf(stderr, "Impossible de charger l'image.\n");
        return 1;
    }

    display_game(&board, image);

    display_grid(&board);

    display_black_rectangle((NB_LIG-1)*CELL, (NB_COL-1)*CELL, CELL, CELL);

    while(1){
        MLV_wait_mouse(&x,&y);

        i = y/(CELL);
        j = x/(CELL);

        if(board.bloc[i][j].lig == NULL && board.bloc[i][j].col == NULL){
            /* On clique dans la case noire il ne se passe rien */
        }
        else if(board.bloc[i-1][j].lig == NULL){
            display_black_rectangle(i*CELL, j*CELL, CELL, CELL);
            
        }
        else if(board.bloc[i+1][j].lig == NULL){

        }
        else if(board.bloc[i][j-1].lig == NULL){

        }
        else if(board.bloc[i][j+1].lig == NULL){

        }
        else{
            /* On clique dans une case qui n'est pas voisine de la case noire il ne se passe rien */
        }

        fprintf(stdout, "cell : %d\n", CELL);
        fprintf(stdout, "x : %d\n", x);

        MLV_actualise_window();
    }

    MLV_free_window();

    return 0;
}