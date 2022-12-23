#ifndef INITGAME_H
#define INITGAME_H
    #include <stdlib.h>
    #include <math.h>
    #include <stdio.h>
    #include <time.h>
    #include "Constant.h"
    #include "Miscellanous.h"
    #include "Display.h"
    #include "Movements.h"
    
    PlayerInfo SetupPlayer();

    float ChooseDifficulty();

    int ChooseMapSize();

    void InitEnergy(PlayerInfo* p_playerInfo, int int_mapSize); // Initialise l'énergie de base du joueur en fonction de la taille de la carte

    void UnallocMatriceMap(int** matrice_Map, int int_mapSize);

    int** AllocMatriceMap(int int_mapSize);

    void UnallocMatriceDistance(int*** matrice_Distance, int int_mapSize);

    int*** AllocMatriceDistance(int int_mapSize);

    int** InitMatriceMap(int** matrice_Map, int int_mapSize);

    int** PlaceObstacle(int** matrice_Map, int int_row, int int_col, int int_mapSize, float float_diffRate, int int_distBase, int constant_rep); // place un obstacle et en fonction du difficulty rate, de la taille de la map et de la RNG crée une "fillon" d'obstacles

    int** GenerateMap(int** matrice_Map, int int_mapSize, float float_diffRate, PlayerInfo *p_playerInfo); //Work In Progress

    int*** GenerateMatriceDistance(int int_mapSize, int*** matrice_Distance);

    int CheckEachDirection(int** matrice_Map, coordonnees coord_curr, int int_maxCoord, int int_Start, int int_Energy);

    int CheckPath(int** matrice_Map, coordonnees coord_curr, int int_maxCoord, int int_Start, int int_Energy); //verifie si la matrice map generer possede un chemin faisable recursivement; 

    int** InitMap(int int_mapSize, float float_diffRate, PlayerInfo* p_playerInfo); //Alloue, init et genere la map

    int*** InitDistance(int int_mapSize); //Alloue, et genere la matrice Distance

    int affiche(Node_d *node);

    Node_d* recurseDijkstra(List_d* p_list, Node_d* firstnode, int** matrice_Map, int*** matrice_Distance, int int_mapSize , coordonnees coordEnd,int int_mode);

    List* AlgoDijkstra(int** matrice_Map,int*** matrice_Distance, PlayerInfo* p_playerInfo, int int_mapSize, int int_mode);
  

#endif

