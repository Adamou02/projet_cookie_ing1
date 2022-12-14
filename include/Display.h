#ifndef DISPLAY_H
#define DISPLAY_H
    #include <stdlib.h>
    #include <unistd.h>
    #include "InitGame.h"
    #include "Constant.h"
    #include "Miscellanous.h"
    
    /// @brief Modifie le terminal pour l'adapter au jeu 
    void EditTerminal(); //Agrandi le terminal ou le maximize si wmctrl est installer

    /// @brief Menu lorsqu'on lance le programme, permet de lancer une nouvelle game, charger la précedente, ou voir l'historique.
    int MenuStartGame();

    /// @brief Menu pour choisir la difficulté 
    int MenuDifficulty();

    /// @brief Menu pour choisir la taille de la carte
    int MenuMapSize();

    /// @brief Menu lors de la fermeture de la partie
    int printSaveMenu ();

    /// @brief Fonction d'affichage de la Map dans le terminal
    void DisplayMap(int** matrice_Map, int int_mapSize);

    /// @brief affiche la map avec le chemin suivis par une liste passer en parametre
    void DisplayPathInMap(int** matric_Map, int int_mapSize, List* p_list);

    /// @brief affiche la map avec le chemin suivis par une liste passer en parametre avec des fleches correspondant a la direction
    void DisplayPathInMapArrow(int** matric_Map, int int_mapSize, List* p_list, int bool_victory);

    void DisplayEndGame(int bool_victory);


    /////////////////////////////////////////////////////////////////////////////
    //Fonctions de DEBUG pour dev, ne serons pas utiliser dans le process final//
    /////////////////////////////////////////////////////////////////////////////

    void DebugDisplayMap(int** matrice_Map, int int_mapSize);

    void DebugDisplayMatriceDistance(int int_mapSize, int*** matrice_Distance);

    void DebugInfoPlayer(PlayerInfo s_playerInfo);

    void PrintList(List* p_list);

    void PrintFirstList(List* p_list);

#endif
