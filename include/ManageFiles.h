#ifndef MANAGEFILE_H
#define MANAGEFILE_H 
    #include <stdio.h>
    #include <stdlib.h>
    #include "Constant.h"
    #include "InitGame.h"

    int ExistFile(char char_NameFile[]);

    void createFile(char char_NameFile[]);
   
    int SupprFile(char char_NameFile[]);

    int SavedTurnsCount(int int_mapSize);

    void GetPlayerInfo(int int_mapSize, PlayerInfo * s_playerInfo_player, int num_turn);

    char* GetMapString(char* MapString, int int_mapSize, int num_turn);

    char* GetDistanceString(char* DistanceString, int int_mapSize, int num_turn);

    char* AllocMapString(int int_mapSize);

    char* AllocDistanceString(int int_mapSize);

    char* AllocListString(int int_mapSize);

    char* MatriceMapToString(int** matrice_Map, int int_mapSize, char* MapString);

    char* MatriceDistanceToString(int*** matrice_Distance, int int_mapSize, char* DistanceString);

    char* ListToString(List* p_list, char* ListString);
    
    int** StringToMatriceMap(char* MapString, int int_mapSize, int** matrice_Map);

    int*** StringToMatriceDistance(char* DistanceString, int int_mapSize, int*** matrice_Distance);

    char* SaveMap(int** matrice_Map, int int_mapSize);

    int** RestoreMap(int** matrice_Map, int int_mapSize, int num_turn);

    char* SaveDistance(int*** matrice_Distance, int int_mapSize);

    int*** RestoreDistance(int*** matrice_Distance, int int_mapSize, int num_turn);

    char* SaveList(List* p_list, int int_mapSize);

    void StockCurrentTurn(int** matrice_Map, int*** matrice_Distance, List* p_list, int int_mapSize, PlayerInfo * s_playerInfo_player);

    void RestoreTurn(int num_turn, int*** matrice_Map, int**** matrice_Distance, PlayerInfo* s_playerInfo, int int_mapSize);

#endif
