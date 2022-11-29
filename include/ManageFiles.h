#ifndef MANAGEFILE_H
#define MANAGEFILE_H 
    #include <stdio.h>
    #include <stdlib.h>
    #include "Constant.h"

    int ExistFile(char char_NameFile[]);

    void createFile(char char_NameFile[]);
   
    int SupprFile(char char_NameFile[]);

    char* AllocMapString(int int_mapSize);

    char* AllocDistanceString(int int_mapSize);

    char* MatriceMapToString(int** matrice_Map, int int_mapSize, char* MapString);

    char* MatriceDistanceToString(int*** matrice_Distance, int int_mapSize, char* DistanceString);
    
    int** StringToMatriceMap(char* MapString, int int_mapSize, int** matrice_Map);

    int*** StringToMatriceDistance(char* DistanceString, int int_mapSize, int*** matrice_Distance);

    void StockCurrentTurn(char* MapString, char* DistanceString, PlayerInfo * s_playerInfo_player);

    void GetAllInfo(char* MapString, char* DistanceString, PlayerInfo * s_playerInfo_player, int int_mapSize);

#endif
