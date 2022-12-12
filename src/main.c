#include "Game.h"

GameInformation GameInfo;

int main(void)
{   
    SetupGame();
    switch(MenuStartGame()){
        case 1:
            ResumeGame();
            break;
        case 2:
            NewGame();
            break;
        case 3:
            break;
        case 4:
            exit(EXIT_SUCCESS);
            break;
        default:
            exit(EXIT_FAILURE);
            break;
    }
    //Affichage d'avant Tour
    BeforeTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.int_mapSize, &GameInfo.s_playerInfo, NULL);

    //Tours du joueur
    int bool_victory = Game(GameInfo.int_mapSize, GameInfo.matrice_Map, GameInfo.matrice_Distance, &GameInfo.s_playerInfo, GameInfo.p_listpath);

    //Affichage de fin de jeu
    DisplayPathInMap(GameInfo.matrice_Map, GameInfo.int_mapSize, GameInfo.p_listpath);

    //liberation des donnée allouer
    FreeGame();
    
    return 0;
}
