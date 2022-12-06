#ifndef GAME_H
#define GAME_H
    #include <stdio.h>
    #include <stdlib.h>
    #include "Constant.h"
    #include "Miscellanous.h"
    #include "Display.h"
    #include "Movements.h"
    #include "InitGame.h"
    #include "ManageFiles.h"

    void SetupGame();

    void BeforeTurn(int** matrice_Map, int*** matrice_Distance, int int_mapSize, PlayerInfo* p_playerInfo, List* p_list);

    void ErrorStepBack(int int_error);

    int BeforeStepBack(PlayerInfo* p_playerInfo, List* p_list);
    
    int Game(int int_mapSize, int** matrice_Map,int*** matrice_Distance, PlayerInfo *p_playerInfo, List* p_list);;

    void FreeGame(int** matrice_Map, int*** matrice_Distance, List* p_listpath, int int_mapSize);

    void FirstTurn();
    
#endif