   #include "Game.h"

    int main(void)
    {
        SetupGame();
        //Choix des parametre de la game
        float float_diffRate = ChooseDifficulty();
        int int_mapSize = ChooseMapSize();

        //Initialisation de la structure Joueur et du stockage du chemin
        PlayerInfo s_playerInfo = SetupPlayer(); 
        InitEnergy(&s_playerInfo, int_mapSize);
        List* p_listpath = InitList(s_playerInfo.coordonnees);
        
        //Creation des structures contenant les infos de la carte
        int** matrice_Map = InitMap(int_mapSize, float_diffRate, &s_playerInfo);
        int*** matrice_Distance = InitDistance(int_mapSize);

        //Affichage pour le premier Tour
        BeforeTurn(matrice_Map, matrice_Distance, int_mapSize, &s_playerInfo, NULL);

        //Le joueur Joue
        int bool_victory = Game(int_mapSize, matrice_Map, matrice_Distance, &s_playerInfo, p_listpath);

        //Affichage de fin de jeu
        DisplayPathInMap(matrice_Map, int_mapSize, p_listpath);

        //liberation des donnée allouer
        FreeGame(matrice_Map, matrice_Distance, p_listpath, int_mapSize);
       
        return 0;
    }
