#ifndef MANAGEFILE_H
#define MANAGEFILE_H 
    #include <stdio.h>
    #include <stdlib.h>
    #include "Constant.h"
    #include "InitGame.h"

    int ExistFile(char str_NameFile[]);

    void createFile(char str_NameFile[]);
   
    int SupprFile(char str_NameFile[]);

    /// @brief Permet de savoir si un fichier est vide ou non
    /// @return Renvoie 1 si fichier vide ou n'existe pas, renvoie 0 si le fichier n'est pas vide
    int IsEmptyFile(char str_NameFile[]);

    int SavedTurnsCount(int int_mapSize, char str_NameFile[]);

    void GetPlayerInfo(int int_mapSize, PlayerInfo * s_playerInfo_player, int num_turn, char str_NameFile[]);

    char* GetMapString(char* MapString, int int_mapSize, int num_turn, char str_NameFile[]);

    char* GetDistanceString(char* DistanceString, int int_mapSize, int num_turn, char str_NameFile[]);

    char* GetListString(char* ListString, int int_mapSize, int num_turn);

    char* AllocMapString(int int_mapSize);

    char* AllocDistanceString(int int_mapSize);

    char* AllocListString(int int_mapSize);

    char* MatriceMapToString(int** matrice_Map, int int_mapSize, char* MapString);

    char* MatriceDistanceToString(int*** matrice_Distance, int int_mapSize, char* DistanceString);

    char* ListToString(List* p_list, char* ListString);
    
    int** StringToMatriceMap(char* MapString, int int_mapSize, int** matrice_Map);

    int*** StringToMatriceDistance(char* DistanceString, int int_mapSize, int*** matrice_Distance);

    int ListElementsCount(char* ListString);

    List* StringToList(List* p_list, char* ListString);

    char* SaveMap(int** matrice_Map, int int_mapSize);

    int** RestoreMap(int** matrice_Map, int int_mapSize, int num_turn, char str_NameFile[]);

    char* SaveDistance(int*** matrice_Distance, int int_mapSize);

    int*** RestoreDistance(int*** matrice_Distance, int int_mapSize, int num_turn, char str_NameFile[]);

    char* SaveList(List* p_list, int int_mapSize);

    List* RestoreList(int int_mapSize, int num_turn);

    void StockCurrentTurn(int** matrice_Map, int*** matrice_Distance, List* p_list, int int_mapSize, PlayerInfo * s_playerInfo_player);

    void RestoreTurn(int num_turn, int*** matrice_Map, int**** matrice_Distance, PlayerInfo* p_playerInfo, int int_mapSize, char str_NameFile[]);

    int RestoreMapSize(char str_NameFile[]);

    void Save(int int_mapSize);

    void SaveToCurrentGame();

    void History(int int_mapSize);

    void ReadHistory(int num_game, int*** matrice_Map);

    int CountHistory();

    void ClearHistory();

#endif
