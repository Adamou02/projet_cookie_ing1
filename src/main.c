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

    int bool_victory = 0;
    
    

    int** matrice_Map = InitMap(int_mapSize, 
                                float_diffRate,
                                &s_playerInfo);
    int*** matrice_Distance = InitDistance(int_mapSize);
    
    

    DisplayMap(matrice_Map, int_mapSize);
    //DebugDisplayMatriceDistance(int_mapSize, matrice_Distance);
    printf("Votre energie : %d\n",s_playerInfo.energy);
    ShowKeyAvailable(&s_playerInfo, matrice_Distance);

    


    
    int key_pressed;
    int int_wanted_x;
    int int_wanted_y;
    while(bool_victory == 0 && s_playerInfo.energy > 0){
        key_pressed = ListenKeyboard();
        ChangePosition(key_pressed, &int_wanted_x, &int_wanted_y, &s_playerInfo); 
        matrice_Map = AfterMovement(matrice_Map, int_wanted_x, int_wanted_y, &s_playerInfo, int_mapSize, &bool_victory);
        printf("\n"); 
        DisplayMap(matrice_Map, int_mapSize); 
        printf("Votre energie : %d\n",s_playerInfo.energy);
        ShowKeyAvailable(&s_playerInfo, matrice_Distance);
    }
    // DebugDisplayMap(matrice_Map, int_mapSize);  


    PrintList(p_listpath);
    FreeList(p_listpath);
    UnallocMatriceMap(matrice_Map, int_mapSize);
    UnallocMatriceDistance(matrice_Distance, int_mapSize);
    return 0;
}
