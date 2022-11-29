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

    int ValidChoose(char myScan);

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

    int CheckPath(int** matrice_Map, int int_Coordx, int int_Coordy, int int_maxCoord, int int_Start, int int_ActEnergy ,int* p_intEnergyNeeded); //verifie si la matrice map generer possede un chemin faisable recursivement; 

    int CheckMapDoable(int** matrice_Map, int int_CoordPlayer_x,  int int_CoordPlayer_y, int int_mapSize, int* p_intEnergyNeeded); //cherche si un chemin est faisable en fonction du placement du player au debut

    int** InitMap(int int_mapSize, float float_diffRate, PlayerInfo* p_playerInfo); //Alloue, init et genere la map

    int*** InitDistance(int int_mapSize); //Alloue, et genere la matrice Distance

    void TurnPlayer(int int_mapSize, int** matrice_Map,int*** matrice_Distance, PlayerInfo *p_playerInfo, int bool_victory, int key_pressed, int int_wanted_x, int int_wanted_y, List *p_list);

    int Game(int int_mapSize, int** matrice_Map,int*** matrice_Distance, PlayerInfo *p_playerInfo_player, List *p_list);
    
    int MinDistance(int distance[], int sptSet[], int int_mapSize);

    void Dijkstra(int** matrice_Map, int int_mapSize, int src);
#endif

