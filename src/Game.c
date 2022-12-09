#include "Game.h"

void SetupGame()
{
    EditTerminal();
    InitRNG();
    SupprFile(CURRENT_GAME_CSV);
}

void BeforeTurn(int** matrice_Map, int*** matrice_Distance, int int_mapSize, PlayerInfo* p_playerInfo, List* p_list)
{
    if(p_list == NULL){
        DisplayMap(matrice_Map, int_mapSize);
    } else {
        DisplayPathInMap(matrice_Map, int_mapSize, p_list);
    }
    printf("Votre energie : %d\n",p_playerInfo->energy);
    ShowKeyAvailable(p_playerInfo, matrice_Distance);
}

void ErrorStepBack(int int_error)
{
    if(int_error == 1){
        printf("\nVous n'avez plus de retour en arrière possible.\n");
    } else if(int_error == 2){
        // PrintList(p_list);
        printf("\nVous ne pouvez pas revenir plus en arrière.\n");
    }
    return;
}

int BeforeStepBack(PlayerInfo* p_playerInfo, List* p_list)
{
    if(p_playerInfo->backward <= 0){
        return (1);
    } else if(LengthList(p_list) <= 1){
        return (2);
    } else {
        return (0);
    }
}

int Game(int int_mapSize, int** matrice_Map,int*** matrice_Distance, PlayerInfo *p_playerInfo, List* p_list)
{
    int key_pressed, int_wanted_x, int_wanted_y, int_error;
    int bool_victory = 0;
    int bool_stepback = 0;
    RemoveNode(p_list);
    AddNode(p_list,  p_playerInfo->coordonnees, 0);

    while( !bool_victory && p_playerInfo->energy > 0){
        StockCurrentTurn(matrice_Map, matrice_Distance, p_list, int_mapSize, p_playerInfo);
        bool_stepback = 0;
        key_pressed = ListenKeyboard();
        ChangePosition(key_pressed, &int_wanted_x, &int_wanted_y, p_playerInfo, &bool_stepback); 
        if(bool_stepback){
            int_error = BeforeStepBack(p_playerInfo, p_list);
            StepBack(p_list, matrice_Map, p_playerInfo);
            if(int_error != 0){
                ErrorStepBack(int_error);
            }
        } else {
            matrice_Map = AfterMovement(matrice_Map, int_wanted_x, int_wanted_y, p_playerInfo, int_mapSize, &bool_victory, p_list);
            printf("\n"); 
        }
        BeforeTurn(matrice_Map, matrice_Distance, int_mapSize, p_playerInfo, p_list);
    }
    return bool_victory;
}

void FreeGame(int** matrice_Map, int*** matrice_Distance, List* p_listpath, int int_mapSize)
{
    FreeList(p_listpath);
    UnallocMatriceMap(matrice_Map, int_mapSize);
    UnallocMatriceDistance(matrice_Distance, int_mapSize);
}


