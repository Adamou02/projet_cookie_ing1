#include "Game.h"

FreeNeedsInfo GameInfo;

int main(void)
{   
    SetupGame();

    //Choix des parametre de la game
    float float_diffRate = ChooseDifficulty();

    //Récupération de la sauvegarde (pas terminé mais un peu de patience, ça progresse)
    int recup_save = 0;
    if(recup_save){
        GameInfo.int_mapSize = RestoreMapSize();
    }
    else{
        GameInfo.int_mapSize = ChooseMapSize();
    }

    //Initialisation de la structure Joueur et du stockage du chemin
    PlayerInfo s_playerInfo = SetupPlayer(); 
    InitEnergy(&s_playerInfo, GameInfo.int_mapSize);
    GameInfo.p_listpath = InitList(s_playerInfo.coordonnees);

    //Creation des structures contenant les infos de la carte
    GameInfo.matrice_Map = InitMap(GameInfo.int_mapSize, float_diffRate, &s_playerInfo);
    GameInfo.matrice_Distance = InitDistance(GameInfo.int_mapSize);

    //Affichage pour le premier Tour
    BeforeTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.int_mapSize, &s_playerInfo, NULL);

    //Le joueur Joue
    int bool_victory = Game(GameInfo.int_mapSize, GameInfo.matrice_Map, GameInfo.matrice_Distance, &s_playerInfo, GameInfo.p_listpath);

    //Affichage de fin de jeu
    DisplayPathInMap(GameInfo.matrice_Map, GameInfo.int_mapSize, GameInfo.p_listpath);

    //liberation des donnée allouer
    FreeGame();
    
    return 0;
}
