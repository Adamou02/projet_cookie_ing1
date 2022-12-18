#ifndef GAME_H
#define GAME_H
    #include <stdio.h>
    #include <stdlib.h>
    #include "Constant.h"
    #include "Miscellanous.h"
    #include "InitGame.h"
    #include "ManageFiles.h"
    #include "Display.h"

    extern GameInformation GameInfo;

    /// @brief Prepare une session de jeu
    void SetupGame();

    /// @brief Affiche les informations (carte, energy, touches ...) au joueur avant sont prochain tour
    void BeforeTurn(int** matrice_Map, int*** matrice_Distance, int int_mapSize, PlayerInfo* p_playerInfo, List* p_list);

    void ErrorStepBack(int int_error);

    int BeforeStepBack(PlayerInfo* p_playerInfo, List* p_list);
    
    /// @brief boucle de jeu principal 
    /// @return retourne un booleen en fonction de la victoire ou la defaite
    void Game();

    /// @brief libere les variables du jeu allouées
    void FreeGame();

    /// @brief Quitte la partie et l'executable proprement
    void Quit();

    /// @brief Sauvegarde la partie en cours puis appel la fct Quit()
    void SaveAndQuit();

    /// @brief Quitte la partie apres avoir afficher un message d'echec
    /// @param str_errMsg message d'echec/d'erreur 
    void QuitFail(const char* str_errMsg);

    ///@brief Crrer une nouvel partie 
    void NewGame();

    void ReloadSave(int*** matrice_Map, int**** matrice_Distance, PlayerInfo* s_playerInfo, int int_mapSize);

    ///@brief Reprend la Game Sauvegarder
    void ResumeGame();

    ///@brief Apres Jeu
    void EndGame();

    ///@brief Initialisation du jeu
    void InitGame();
    
#endif
