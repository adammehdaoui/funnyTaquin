#ifndef __UTILS__
#define __UTILS__

/**
 * @brief Fonction permettant de vérifier si un chemin est accessible. La variable paths contient les chemins autorisés prédéfinis.
 * 
 * @param pathTest 
 * @param paths 
 * @param size 
 * @return int 
 */
int isPathAcc(char *pathTest, char *paths[], int size);

#endif