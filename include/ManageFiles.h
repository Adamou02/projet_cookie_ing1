#ifndef MANAGEFILE_H
#define MANAGEFILE_H 
    #include <stdio.h>
    #include <stdlib.h>
    #include "Constant.h"
    #include "InitGame.h"

    int ExistFile(char char_NameFile[]);

    void createFile(char char_NameFile[]);
   
    int SupprFile(char char_NameFile[]);

    void GetPlayerInfo(int int_mapSize, PlayerInfo * s_playerInfo_player);

    char* GetMapString(char* MapString, int int_mapSize);

    char* GetDistanceString(char* DistanceString, int int_mapSize);

    char* AllocMapString(int int_mapSize);

    char* AllocDistanceString(int int_mapSize);

    char* MatriceMapToString(int** matrice_Map, int int_mapSize, char* MapString);

    char* MatriceMapToString2(int** matrice_Map, int int_mapSize, char* MapString);

    char* MatriceDistanceToString(int*** matrice_Distance, int int_mapSize, char* DistanceString);
    
    int** StringToMatriceMap(char* MapString, int int_mapSize, int** matrice_Map);

    int*** StringToMatriceDistance(char* DistanceString, int int_mapSize, int*** matrice_Distance);

    char* SaveMap(int** matrice_Map, int int_mapSize);

    int** RestoreMap(int** matrice_Map, int int_mapSize);

    int*** RestoreDistance(int*** matrice_Distance, int int_mapSize);

    void GetAllInfo(char* MapString, char* DistanceString, PlayerInfo * s_playerInfo_player, int int_mapSize);

    void StockCurrentTurn(int** matrice_Map, int*** matrice_Distance, int int_mapSize, PlayerInfo * s_playerInfo_player);

#endif
