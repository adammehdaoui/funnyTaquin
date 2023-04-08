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

void initialisationPlateau(Plateau *P) {
    int i,j;
    for(i=0; i<NB_LIG; i++){
        for (j=0; j<NB_COL; j++){
            ((P->bloc)[i][j]).lig = i;
            ((P->bloc)[i][j]).col = j;
        }
    }
}

void mixPlateau(Plateau *P){

}

int display_win(Plateau *P){
    int i, j, flag = 0;

    for(i=0; i<(NB_LIG); i++){
        for (j=0; j<(NB_COL); j++){
            if(i==3 && j==3){
                // on ne teste pas le dernier carreau
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
// c est bizarre d'utiliser les variables r g b a non init
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

int main(int argc, char *argv[]){
    Plateau board;
    initialisationPlateau(&board); 

    board.bloc[3][3].lig = -1;
    board.bloc[3][3].col = -1;

    int x, y, i, j;
    int rx, ry;

    MLV_create_window(GAME, NULL, RES, RES); 	
    MLV_Image* image = MLV_load_image("data/image.jpg"); 
    if (!image) {
        fprintf(stderr, "Impossible de charger l'image.\n");
        return 1;
    }

    display_game(&board, image);
    display_grid(&board);

    for(int n=0; n<20; n++){
        rx = MLV_get_random_integer(0, RES);
        ry = MLV_get_random_integer(0, RES);

        i = rx/(CELL);
        j = ry/(CELL);

        if(i>0 && board.bloc[i-1][j].lig == -1){
            board.bloc[i-1][j].lig = board.bloc[i][j].lig;
            board.bloc[i-1][j].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }
        else if(i<NB_LIG-1 && board.bloc[i+1][j].lig == -1){
            board.bloc[i+1][j].lig = board.bloc[i][j].lig;
            board.bloc[i+1][j].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }
        else if(j>0 && board.bloc[i][j-1].lig == -1){
            board.bloc[i][j-1].lig = board.bloc[i][j].lig;
            board.bloc[i][j-1].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }
        else if(j<NB_COL-1 && board.bloc[i][j+1].lig == -1){
            board.bloc[i][j+1].lig = board.bloc[i][j].lig;
            board.bloc[i][j+1].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }
    }

    display_game(&board, image);
    display_grid(&board);

    while(1){
        MLV_actualise_window();

        MLV_wait_mouse(&x,&y);

        i = x/(CELL);
        j = y/(CELL);

        if(i>0 && board.bloc[i-1][j].lig == -1){
            board.bloc[i-1][j].lig = board.bloc[i][j].lig;
            board.bloc[i-1][j].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }
        else if(i<NB_LIG-1 && board.bloc[i+1][j].lig == -1){
            board.bloc[i+1][j].lig = board.bloc[i][j].lig;
            board.bloc[i+1][j].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }
        else if(j>0 && board.bloc[i][j-1].lig == -1){
            board.bloc[i][j-1].lig = board.bloc[i][j].lig;
            board.bloc[i][j-1].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }
        else if(j<NB_COL-1 && board.bloc[i][j+1].lig == -1){
            board.bloc[i][j+1].lig = board.bloc[i][j].lig;
            board.bloc[i][j+1].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }

        display_game(&board, image);
        display_grid(&board);

        if (display_win(&board) == 0){
            MLV_draw_text(RES/2, RES/2, "Gagné!", MLV_rgba(255, 255, 255, 255));
        }
    }

    MLV_free_window();

    return EXIT_SUCCESS;
}