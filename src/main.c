    #include "Miscellanous.h"
    #include "Display.h"
    #include "Movements.h"
    #include "InitGame.h"
    #include "ManageFiles.h"

    int main(void)
    {
        EditTerminal();
        InitRNG();
        float float_diffRate = ChooseDifficulty();
        int int_mapSize = ChooseMapSize();
        PlayerInfo s_playerInfo = SetupPlayer(); 
        InitEnergy(&s_playerInfo, int_mapSize);
        List* p_listpath = InitList();
        

        int** matrice_Map = InitMap(int_mapSize, 
                                    float_diffRate,
                                    &s_playerInfo);
        int*** matrice_Distance = InitDistance(int_mapSize);
        
        int bool_victory = 0;

        DisplayMap(matrice_Map, int_mapSize);
        //DebugDisplayMatriceDistance(int_mapSize, matrice_Distance);
        printf("Votre energie : %d\n",s_playerInfo.energy);
        ShowKeyAvailable(&s_playerInfo, matrice_Distance);

        
        bool_victory = game(int_mapSize, matrice_Map, matrice_Distance,&s_playerInfo);
        // DebugDisplayMap(matrice_Map, int_mapSize);  


        PrintList(p_listpath);
        FreeList(p_listpath);
        UnallocMatriceMap(matrice_Map, int_mapSize);
        UnallocMatriceDistance(matrice_Distance, int_mapSize);
        return 0;
    }
