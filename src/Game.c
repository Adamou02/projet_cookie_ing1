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
    int choice;
    RemoveNode(p_list);
    AddNode(p_list,  p_playerInfo->coordonnees, 0);

    while( !bool_victory && p_playerInfo->energy > 0){
        StockCurrentTurn(matrice_Map, matrice_Distance, p_list, int_mapSize, p_playerInfo);
        key_pressed = ListenKeyboard();
        ChangePosition(key_pressed, &int_wanted_x, &int_wanted_y, p_playerInfo); 
        if(key_pressed == STEP_BACK){
            int_error = BeforeStepBack(p_playerInfo, p_list);
            if(int_error != 0){
                ErrorStepBack(int_error);
            }else{
                StepBack(p_list, matrice_Map, p_playerInfo, int_mapSize, matrice_Distance);
                BeforeTurn(matrice_Map, matrice_Distance, int_mapSize, p_playerInfo, p_list);
            }
        } else if(key_pressed == LEAVE){
            choice = printSaveMenu();
            if (choice == 0) 
                Quit(); //l'utilisateur a choisi de partir sans sauvegarder.
            else if (choice == 1)
                SaveAndQuit();//*fonction Fabien sauvegarde*/; 
            else //choice ==2 l'utilisateur veut revenir jouer sur sa game
                BeforeTurn(matrice_Map, matrice_Distance, int_mapSize, p_playerInfo, p_list);
       } else {
            matrice_Map = AfterMovement(matrice_Map, int_wanted_x, int_wanted_y, p_playerInfo, int_mapSize, &bool_victory, p_list, matrice_Distance);
            printf("\n"); 
            BeforeTurn(matrice_Map, matrice_Distance, int_mapSize, p_playerInfo, p_list);
        }
    }
    return bool_victory;
}

void FreeGame()
{
    FreeList(GameInfo.p_listpath);
    UnallocMatriceMap(GameInfo.matrice_Map, GameInfo.int_mapSize);
    UnallocMatriceDistance(GameInfo.matrice_Distance, GameInfo.int_mapSize);
}


void Quit()
{
    FreeGame();
    exit(EXIT_SUCCESS);
}

void SaveAndQuit()
{
    Save(GameInfo.int_mapSize);
    Quit();
}

void QuitFail(const char* str_errMsg){
    puts(str_errMsg);
    FreeGame();
    exit(EXIT_FAILURE);
}

void NewGame()
{
     //Choix des parametre de la game
    GameInfo.float_diffRate = ChooseDifficulty();
    GameInfo.int_mapSize = ChooseMapSize();

    //Initialisation de la structure Joueur et du stockage du chemin
    GameInfo.s_playerInfo = SetupPlayer(); 
    InitEnergy(&GameInfo.s_playerInfo, GameInfo.int_mapSize);
    GameInfo.p_listpath = InitList(GameInfo.s_playerInfo.coordonnees);

    //Creation des structures contenant les infos de la carte
    GameInfo.matrice_Map = InitMap(GameInfo.int_mapSize, GameInfo.float_diffRate, &GameInfo.s_playerInfo);
    GameInfo.matrice_Distance = InitDistance(GameInfo.int_mapSize);
}

void ResumeGame()
{
    if(!ExistFile(SAVE_CSV)){ //Ajouter une verif si le fichier est vide
        puts("File Save.csv not found or empty");
        exit(EXIT_FAILURE);
    }   
    GameInfo.int_mapSize = RestoreMapSize();
    GameInfo.matrice_Map = AllocMatriceMap(GameInfo.int_mapSize);
    GameInfo.matrice_Distance = AllocMatriceDistance(GameInfo.int_mapSize);
    RestoreTurn(
                SavedTurnsCount(GameInfo.int_mapSize, SAVE_CSV),
                &GameInfo.matrice_Map,
                &GameInfo.matrice_Distance,
                &GameInfo.s_playerInfo,
                GameInfo.int_mapSize    
                );    
    GameInfo.p_listpath = InitList(GameInfo.s_playerInfo.coordonnees); //a remplacer par la restauration de la list
}
