#include <string.h>
#include <unistd.h>
#include <time.h>

#include "../include/display.h"
#include "../include/taquin.h"
#include "../include/utils.h"

void initialisationPlateau(Plateau *P) {
    int i,j;
    for(i=0; i<NB_LIG; i++){
        for (j=0; j<NB_COL; j++){
            ((P->bloc)[i][j]).lig = i;
            ((P->bloc)[i][j]).col = j;
        }
    }

    ((P->bloc)[NB_LIG-1][NB_LIG-1]).lig = -1;
    ((P->bloc)[NB_LIG-1][NB_LIG-1]).col = -1;
}

void mixPlateau(Plateau *P) {
    int rx, ry, i, j, n;
    
    n=0;

    while(n < MIX){
        rx = MLV_get_random_integer(0, RES);
        ry = MLV_get_random_integer(0, RES);

        i = rx/(CELL);
        j = ry/(CELL);

        if(i>0 && P->bloc[i-1][j].lig == -1){
            ((P->bloc)[i-1][j]).lig = P->bloc[i][j].lig;
            ((P->bloc)[i-1][j]).col = P->bloc[i][j].col;
            ((P->bloc)[i][j]).lig = -1;
            ((P->bloc)[i][j]).col = -1;
            n++;
        }
        else if(i<NB_LIG-1 && P->bloc[i+1][j].lig == -1){
            ((P->bloc)[i+1][j]).lig = P->bloc[i][j].lig;
            ((P->bloc)[i+1][j]).col = P->bloc[i][j].col;
            ((P->bloc)[i][j]).lig = -1;
            ((P->bloc)[i][j]).col = -1;
            n++;
        }
        else if(j>0 && P->bloc[i][j-1].lig == -1){
            ((P->bloc)[i][j-1]).lig = P->bloc[i][j].lig;
            ((P->bloc)[i][j-1]).col = P->bloc[i][j].col;
            ((P->bloc)[i][j]).lig = -1;
            ((P->bloc)[i][j]).col = -1;
            n++;
        }
        else if(j<NB_COL-1 && P->bloc[i][j+1].lig == -1){
            ((P->bloc)[i][j+1]).lig = P->bloc[i][j].lig;
            ((P->bloc)[i][j+1]).col = P->bloc[i][j].col;
            ((P->bloc)[i][j]).lig = -1;
            ((P->bloc)[i][j]).col = -1;
            n++;
        }
    }
}

int gameWin(Plateau *P){
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

void gameLoop(Plateau *P, MLV_Image *img) {
    int i, j, x, y;
    time_t start_t;

    start_t = time(NULL);

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

        if (gameWin(P) == 0){
            display_win(start_t);
            MLV_actualise_window();
            sleep(10);
            return;
        }
    }

}

void gameComp(int argc, char *argv[]){
    char *accPaths[] = {
        "hugo.jpg",
        "spirale.gif",
        "briques.png"
    };
    int size = sizeof(accPaths)/sizeof(accPaths[0]);
    char *path;
    char fullPath[SIZE_PATH] = "";
    Plateau board;
    MLV_Image* image;

    initialisationPlateau(&board);

    MLV_create_window(GAME, NULL, RES, RES);

    if(argc >= 2 && isPathAcc(argv[1], accPaths, size)){
        path = (char *) malloc((strlen(argv[1]) + 1) * sizeof(char));
        strcpy(path, argv[1]);
        printf("NON DEFAULT\n");
    }
    else{
        path = (char *) malloc((strlen(DEFAULT) + 1) * sizeof(char));
        strcpy(path, DEFAULT);
        printf("DEFAULT\n");
    }

    strcat(fullPath, IMG_DIR);
    strcat(fullPath, path);

    image = MLV_load_image(fullPath); 
    if (!image) {
        fprintf(stderr, "Impossible de charger l'image.\n");
        return;
    }

    free(path);

    mixPlateau(&board);

    display_game(&board, image);
    display_grid(&board);

    gameLoop(&board, image);

    MLV_free_image(image);
    MLV_free_window();
}