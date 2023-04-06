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

void display_black_rectangle(int startX, int startY, int height, int width){
    MLV_draw_filled_rectangle(startX, startY, CELL, CELL, MLV_rgba(0, 0, 0, 255));
}

void display_game(Plateau *P, MLV_Image *image){
    int i, j, ii, jj, x, y, r, g, b, a, startX, startY, endX, endY;

    for(i=0; i<NB_LIG; i++){
        for(j=0; j<NB_COL; j++){

            startX = P->bloc[i][j].lig*CELL;
            startY = P->bloc[i][j].col*CELL;
            endX = startX+CELL;
            endY = startY+CELL;
            ii = i*CELL;
            jj = j*CELL;

            if(P->bloc[i][j].lig == -1 && P->bloc[i][j].col == -1){
                display_black_rectangle(startX, startY, CELL, CELL);
            }
            else{
                for(x=startX; x<endX; x++){
                    for(y=startY; y<endY; y++){
                        MLV_get_pixel_on_image(image, ii, jj, &r, &g, &b, &a);
                        MLV_draw_pixel(x, y, MLV_rgba(r, g, b, a));
                    }
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

int main(int argc, char *argv[]){
    Plateau board;
    initialisationPlateau(&board); 

    board.bloc[3][3].lig = -1;
    board.bloc[3][3].col = -1;

    int x, y, i, j;

    MLV_create_window(GAME, NULL, RES, RES); 	
    MLV_Image* image = MLV_load_image("data/image.jpg"); 
    if (!image) {
        fprintf(stderr, "Impossible de charger l'image.\n");
        return 1;
    }

    display_game(&board, image);
    display_grid(&board);

    while(1){
        MLV_actualise_window();

        MLV_wait_mouse(&x,&y);

        i = y/(CELL);
        j = x/(CELL);

        if(board.bloc[i][j].lig == -1 && board.bloc[i][j].col == -1){
            /* On clique dans la case noire il ne se passe rien */
        }
        else if(board.bloc[i-1][j].lig == -1){
            board.bloc[i-1][j].lig = board.bloc[i][j].lig;
            board.bloc[i-1][j].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;
        }
        else if(board.bloc[i+1][j].lig == -1){

        }
        else if(board.bloc[i][j-1].lig == -1){

        }
        else if(board.bloc[i][j+1].lig == -1){
            board.bloc[i][j+1].lig = board.bloc[i][j].lig;
            board.bloc[i][j+1].col = board.bloc[i][j].col;
            board.bloc[i][j].lig = -1;
            board.bloc[i][j].col = -1;

            printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
        }
        else{
            /* On clique dans une case qui n'est pas voisine de la case noire il ne se passe rien */
        }

        fprintf(stdout, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
        board.bloc[0][0].lig, board.bloc[0][0].col, board.bloc[0][1].lig, 
        board.bloc[0][1].col, board.bloc[0][2].lig, board.bloc[0][2].col, 
        board.bloc[0][3].lig, board.bloc[0][3].col,board.bloc[1][0].lig, 
        board.bloc[1][0].col, board.bloc[1][1].lig, board.bloc[1][1].col, 
        board.bloc[1][2].lig, board.bloc[1][2].col, board.bloc[1][3].lig, 
        board.bloc[1][3].col, board.bloc[2][0].lig, board.bloc[2][0].col, 
        board.bloc[2][1].lig, board.bloc[2][1].col, board.bloc[2][2].lig, 
        board.bloc[2][2].col, board.bloc[2][3].lig, board.bloc[2][3].col, 
        board.bloc[3][0].lig, board.bloc[3][0].col, board.bloc[3][1].lig, 
        board.bloc[3][1].col, board.bloc[3][2].lig, board.bloc[3][2].col, 
        board.bloc[3][3].lig, board.bloc[3][3].col); 


        display_game(&board, image);
        display_grid(&board);

        fprintf(stdout, "cell : %d\n", CELL);
        fprintf(stdout, "x : %d\n", x);
    }

    MLV_free_window();

    return 0;
}