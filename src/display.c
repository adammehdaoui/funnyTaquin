#include <MLV/MLV_all.h>
#include <time.h>

#include "../include/display.h"
#include "../include/taquin.h"

void display_black_rectangle(int startX, int startY, int height, int width){
    MLV_draw_filled_rectangle(startX, startY, CELL, CELL, MLV_COLOR_BLACK);
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

void display_win(time_t start_t){
    time_t end_t;
    double diff_t;
    int int_diff;
    char final_message[50] = "";
    char time_message[5] = "";

    MLV_Font* font = MLV_load_font((FONT_PATH), (FONT_SIZE));

    end_t = time(NULL);

    diff_t = difftime(end_t, start_t);

    int_diff = (int) diff_t;

    sprintf(time_message, "%d", int_diff);

    fprintf(stdout, time_message);

    strcpy(final_message, "Félicitations, vous avez gagné en : ");
    strcat(final_message, time_message);
    strcat(final_message, " secondes !");

    MLV_draw_text_with_font(CELL - (CELL/3), CELL + (CELL/2), 
    final_message, font, MLV_COLOR_WHITE);

    MLV_free_font(font);
}