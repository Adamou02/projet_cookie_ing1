#ifndef MOVEMENTS_H
#define MOVEMENTS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <termios.h>
    #include "Constant.h"
    #include "Miscellanous.h"
    #include "Game.h"

    static struct termios old, current; //Structure qui permet de garder les deux états paramètres du terminal
    
    //Verifie la touche pressée
    int KeyAvailable(int key);

    //Change les valeur des variables dans UpdatePosition pour changer la position du personnage dans la matrice map
    void ChangePosition(int key, int* x, int* y, PlayerInfo *p_playerInfo);

    //Fait un retour à la ligne quand la fonction est appelée (permet de bien afficher les différentes touches disponibles sur plusieurs lignes)
    void SkipLine(int line_count, int* p_line_count);

    //Permet de lire la touche pressé. Le programme est en pause tant que utilisateur appuie touche
    int ListenKeyboard();

    int** UpdatePosition(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo); // Met à jour les informations de la map en fonction du déplacement

    int GetDirection(int x, int y, int going_x, int going_y, int direction);    

    void UpdatePlayerInfo(int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo,  int*** matrice_Distance);//Met à jour les infos du joueur en fonction du déplacement

    void PlayerOnBonus(PlayerInfo *p_playerInfo);//Donne de l'énergie à un joueur lorsqu'il marche sur un bonus

    void PlayerOnObstacle(PlayerInfo *p_playerInfo); //retire de l'énergie au joueur lorsqu'il rentre dans un obstacle
 
    void UpdatePathList(PlayerInfo *p_playerInfo, List* p_list, int is_bonus);

    int** WasABonus(int** matrice_map, int last_x, int last_y, PlayerInfo *p_playerInfo, char CST);
  
    void StepBack(List* p_list, int** matrice_map, PlayerInfo *p_playerInfo, int*** matrice_Distance);

    int AlreadyBeen(int int_wanted_x, int int_wanted_y, List* p_list);

    int** AfterMovement(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo, int int_mapSize, int *bool_victory, List* p_list,  int*** matrice_Distance, int *bool_isanObstacle);// Permet de déplacer ou non le joueur en fonction du déplacement demandé et de la carte

#endif
