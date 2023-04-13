#include <string.h>

#include "../include/utils.h"

int isPathAcc(char *pathTest, char *paths[], int size){
    int i;

    for(i=0; i<size; i++){
        if(strcmp(pathTest, paths[i]) == 0){
            return 1;
        }
    }
    
    return 0;
}