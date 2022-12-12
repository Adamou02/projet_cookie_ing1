#ifndef GAME_H
#define GAME_H
    #include <stdio.h>
    #include <stdlib.h>
    #include "Constant.h"
    #include "Miscellanous.h"
    #include "InitGame.h"
    #include "ManageFiles.h"

    extern FreeNeedsInfo GameInfo;

    void SetupGame();

    void BeforeTurn(int** matrice_Map, int*** matrice_Distance, int int_mapSize, PlayerInfo* p_playerInfo, List* p_list);

    void ErrorStepBack(int int_error);

    int BeforeStepBack(PlayerInfo* p_playerInfo, List* p_list);
    
    int Game(int int_mapSize, int** matrice_Map,int*** matrice_Distance, PlayerInfo *p_playerInfo, List* p_list);;

    void FreeGame();

    void FirstTurn();

    /// @brief Quitte la partie et l'executable proprement
    void Quit();

    /// @brief Sauvegarde la partie en cours puis appel la fct Quit()
    void SaveAndQuit();

    void QuitFail(const char* str_errMsg);
    
#endif