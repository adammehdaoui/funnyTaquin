#include "../include/display.h"
#include "../include/taquin.h"

void initialisationPlateau(Plateau *P) {
    int i,j;
    for(i=0; i<NB_LIG; i++){
        for (j=0; j<NB_COL; j++){
            ((P->bloc)[i][j]).lig = i;
            ((P->bloc)[i][j]).col = j;
        }
    }
}

void mixPlateau(Plateau *P) {
    int rx, ry, i, j, n;
    
    for(n=0; n<20; n++){
        rx = MLV_get_random_integer(0, RES);
        ry = MLV_get_random_integer(0, RES);

        i = rx/(CELL);
        j = ry/(CELL);

        if(i>0 && P->bloc[i-1][j].lig == -1){
            ((P->bloc)[i-1][j]).lig = P->bloc[i][j].lig;
            ((P->bloc)[i-1][j]).col = P->bloc[i][j].col;
            ((P->bloc)[i][j]).lig = -1;
            ((P->bloc)[i][j]).col = -1;
        }
        else if(i<NB_LIG-1 && P->bloc[i+1][j].lig == -1){
            ((P->bloc)[i+1][j]).lig = P->bloc[i][j].lig;
            ((P->bloc)[i+1][j]).col = P->bloc[i][j].col;
            ((P->bloc)[i][j]).lig = -1;
            ((P->bloc)[i][j]).col = -1;
        }
        else if(j>0 && P->bloc[i][j-1].lig == -1){
            ((P->bloc)[i][j-1]).lig = P->bloc[i][j].lig;
            ((P->bloc)[i][j-1]).col = P->bloc[i][j].col;
            ((P->bloc)[i][j]).lig = -1;
            ((P->bloc)[i][j]).col = -1;
        }
        else if(j<NB_COL-1 && P->bloc[i][j+1].lig == -1){
            ((P->bloc)[i][j+1]).lig = P->bloc[i][j].lig;
            ((P->bloc)[i][j+1]).col = P->bloc[i][j].col;
            ((P->bloc)[i][j]).lig = -1;
            ((P->bloc)[i][j]).col = -1;
        }
    }
}

void gameLoop(Plateau *P, MLV_Image *img) {
    int i, j, x, y;

    while(1){
        MLV_actualise_window();

        MLV_wait_mouse(&x,&y);

        i = x/(CELL);
        j = y/(CELL);

        if(i>0 && P->bloc[i-1][j].lig == -1){
            P->bloc[i-1][j].lig = P->bloc[i][j].lig;
            P->bloc[i-1][j].col = P->bloc[i][j].col;
            P->bloc[i][j].lig = -1;
            P->bloc[i][j].col = -1;
        }
        else if(i<NB_LIG-1 && P->bloc[i+1][j].lig == -1){
            P->bloc[i+1][j].lig = P->bloc[i][j].lig;
            P->bloc[i+1][j].col = P->bloc[i][j].col;
            P->bloc[i][j].lig = -1;
            P->bloc[i][j].col = -1;
        }
        else if(j>0 && P->bloc[i][j-1].lig == -1){
            P->bloc[i][j-1].lig = P->bloc[i][j].lig;
            P->bloc[i][j-1].col = P->bloc[i][j].col;
            P->bloc[i][j].lig = -1;
            P->bloc[i][j].col = -1;
        }
        else if(j<NB_COL-1 && P->bloc[i][j+1].lig == -1){
            P->bloc[i][j+1].lig = P->bloc[i][j].lig;
            P->bloc[i][j+1].col = P->bloc[i][j].col;
            P->bloc[i][j].lig = -1;
            P->bloc[i][j].col = -1;
        }

        display_game(P, img);
        display_grid(P);

        if (display_win(P) == 0){
            MLV_draw_text(RES/2, RES/2, "Gagné!", MLV_rgba(255, 255, 255, 255));
        }
    }

}

void gameComp(){
    Plateau board;
    MLV_Image* image;

    initialisationPlateau(&board);

    board.bloc[NB_LIG-1][NB_LIG-1].lig = -1;
    board.bloc[NB_LIG-1][NB_LIG-1].col = -1;

    MLV_create_window(GAME, NULL, RES, RES); 	
    image = MLV_load_image("data/image.jpg"); 
    if (!image) {
        fprintf(stderr, "Impossible de charger l'image.\n");
        return;
    }

    mixPlateau(&board);

    display_game(&board, image);
    display_grid(&board);

    gameLoop(&board, image);

    MLV_free_window();
}