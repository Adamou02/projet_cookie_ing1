#include "InitGame.h"


PlayerInfo SetupPlayer() //Initialise des valeurs par défaut pour le joueur
{
    PlayerInfo playerInfo;
    playerInfo.coordonnees.x = 0;
    playerInfo.coordonnees.y = 0;
    playerInfo.energy=BASE_ENERGY;
    playerInfo.distance=0;
    playerInfo.gain_energy=0;
    playerInfo.lost_energy=0;
    playerInfo.backward=6;
    return playerInfo;
}

int MenuDifficulty()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nChoose a Difficulty :\n>1: Easy\n 2: Normal\n 3: Hard\n\n\n %s : z\t\t%s : x\t\t%s : Enter", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if (input == UP && position!=1)
        { 
            position--;
        }
        else if (input == DOWN && position !=3)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nChoose a Difficulty :\n>1: Easy\n 2: Normal\n 3: Hard\n\n\n %s : z\t\t%s : x\t\t%s : Enter", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\nChoose a Difficulty :\n 1: Easy\n>2: Normal\n 3: Hard\n\n\n %s : z\t\t%s : x\t\t%s : Enter", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 3) {
            ClearTerm();
            printf("\nChoose a Difficulty :\n 1: Easy\n 2: Normal\n>3: Hard\n\n\n %s : z\t\t%s : x\t\t%s : Enter", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

float ChooseDifficulty()
{
    int int_scanDiff = MenuDifficulty();
    switch (int_scanDiff) 
    {
    case 1:
        return (TAUX_DIFF_EZ);
        break;
    case 2:
        return (TAUX_DIFF_NORMAL);
        break;
    case 3:
        return (TAUX_DIFF_HARD);
        break;
    default:
        puts("Erreur selection difficulte");
        exit(EXIT_FAILURE);
    }
    
}

int MenuMapSize()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nChoose the map size :\n>1: Little\n 2: Average\n 3: Big\n\n\n %s : z\t\t%s : x\t\t%s : Enter", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if (input == UP && position!=1)
        { 
            position--;
        }
        else if (input == DOWN && position !=3)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nChoose the map size :\n>1: Little\n 2: Average\n 3: Big\n\n\n %s : z\t\t%s : x\t\t%s : Enter", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\nChoose the map size :\n 1: Little\n>2: Average\n 3: Big\n\n\n %s : z\t\t%s : x\t\t%s : Enter", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 3) {
            ClearTerm();
            printf("\nChoose the map size :\n 1: Little\n 2: Average\n>3: Big\n\n\n %s : z\t\t%s : x\t\t%s : Enter", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

int ChooseMapSize()
{
    int int_scanMapS = MenuMapSize();
    switch (int_scanMapS)
    {
    case 1:  
        return (TAILLE_LIL_MAP);
        break;
    case 2:
        return (TAILLE_AVE_MAP);
        break;
    case 3:
        return (TAILLE_BIG_MAP);
        break;
    default:
        puts("Erreur selection taille map");
        exit(EXIT_FAILURE);
    }
}

void InitEnergy(PlayerInfo *p_playerInfo, int int_mapSize) // Initialise l'énergie de base du joueur en fonction de la taille de la carte
{
    p_playerInfo->energy = BASE_ENERGY * int_mapSize;
}

void UnallocMatriceMap(int** matrice_Map, int int_mapSize)
{
    for(int i = 0; i<int_mapSize ; i++){
        free(matrice_Map[i]);
    }
    free(matrice_Map);
    return;
}   

int** AllocMatriceMap(int int_mapSize)
{
    int** matrice_Map = malloc(int_mapSize * sizeof(*matrice_Map));   
    if(matrice_Map == NULL){
        exit(EXIT_FAILURE);
    }

    for(int i=0 ; i < int_mapSize ; i++){
        matrice_Map[i] = malloc(int_mapSize * sizeof(**matrice_Map) );
        if(matrice_Map[i] == NULL){  
            for(i = i-1 ; i >= 0 ; i--) {   
              free(matrice_Map[i]);
            }                                 
            free(matrice_Map);
            exit(EXIT_FAILURE);
        }
    }
    return (matrice_Map);
}

void UnallocMatriceDistance(int*** matrice_Distance, int int_mapSize)
{
    for(int i = 0; i<int_mapSize ; i++){
        for(int j = 0; j< int_mapSize; j++)
        {
            free(matrice_Distance[i][j]);
        }
        free(matrice_Distance[i]);
    }
    free(matrice_Distance);
    return;
}  

int*** AllocMatriceDistance(int int_mapSize) 
{
    int*** matrice_Distance = malloc(8 * int_mapSize * int_mapSize *  sizeof(*matrice_Distance));       //allocation mémoire a la matrice
    if(matrice_Distance == NULL){
        exit(EXIT_FAILURE);
    } 
    for(int i=0 ; i < int_mapSize ; i++)
    {
        matrice_Distance[i] = malloc(8 * int_mapSize * sizeof(**matrice_Distance) );         //allocation mémoire a la matrice (chaques lignes)
        if(matrice_Distance[i] == NULL){  
            for(i = i-1 ; i >= 0 ; i--) {   
              free(matrice_Distance[i]);
            }                                 
            free(matrice_Distance);
            exit(EXIT_FAILURE);
        }       
        for(int j = 0 ; j < int_mapSize; j++)
        { 
            matrice_Distance[i][j] = malloc(8 * sizeof(***matrice_Distance) );       //allocation mémoire a la matrice (chaques cases)
            if(matrice_Distance[i][j] == NULL) 
            {
                for(i = i-1 ; i >= 0 ; i--) 
                {
                    for(j=j-1;j>=0;j--)
                    {
                        free(matrice_Distance[i][j]);
                    }
                    free(matrice_Distance[i]);
                 }
                free(matrice_Distance);
                exit(EXIT_FAILURE);
            }else{
                 for(int int_compteur = 0 ; int_compteur< 8; int_compteur++)      //Boucles initialisation matrices a 0 partout
                {
                matrice_Distance[i][j][int_compteur] = 0;
                }
            }
        }
    }
    return (matrice_Distance);
}

int** InitMatriceMap(int** matrice_Map, int int_mapSize)
{
    for(int i=0; i<int_mapSize ; i++){
        for(int j=0; j<int_mapSize ; j++){
            matrice_Map[i][j] = REP_DEFAULT;
        }
    }
    return (matrice_Map);
}

int ** PlaceObstacle(int** matrice_Map, int int_row, int int_col, int int_mapSize, float float_diffRate, int int_distBase, int constant_rep) // place un obstacle et en fonction du difficulty rate, de la taille de la map et de la RNG crée une "fillon" d'obstacles
{   
    matrice_Map[int_row][int_col] = constant_rep ;

    if( (RNG(0, ( ( 80  * int_distBase  * (RNG(10, 15) / 10) ) / ( float_diffRate * (int_mapSize / 10) ) ) ) < 50) || int_distBase - 1 > (int_mapSize / 10 ) * float_diffRate  ){
        switch (RNG(1,4))
        {
            case 1:
                if( int_col + 1 < int_mapSize && CoordCompare(matrice_Map, int_row, int_col + 1, REP_DEFAULT) ) {
                    matrice_Map = PlaceObstacle(matrice_Map, int_row, int_col + 1, int_mapSize, float_diffRate, int_distBase + 1, constant_rep);
                } else {
                    return matrice_Map;
                }
                break;
            case 2:
                if( int_row + 1 < int_mapSize && CoordCompare(matrice_Map, int_row + 1, int_col, REP_DEFAULT) ) {
                    matrice_Map = PlaceObstacle(matrice_Map, int_row + 1, int_col, int_mapSize, float_diffRate, int_distBase + 1, constant_rep);
                } else {
                    return matrice_Map;
                }
                break;
            case 3:
                if( int_row - 1 >= 0 && CoordCompare(matrice_Map, int_row - 1, int_col, REP_DEFAULT) ) {
                    matrice_Map = PlaceObstacle(matrice_Map, int_row - 1, int_col, int_mapSize, float_diffRate, int_distBase + 1, constant_rep);
                } else {
                    return matrice_Map;
                }
                break;
            case 4:
                if( int_col - 1 >= 0 && CoordCompare(matrice_Map, int_row, int_col - 1, REP_DEFAULT) ) {
                    matrice_Map = PlaceObstacle(matrice_Map, int_row, int_col - 1, int_mapSize, float_diffRate, int_distBase + 1, constant_rep);
                } else {
                    return matrice_Map;
                }
                break;
        }
    }
    return (matrice_Map);
}

int** GenerateMap(int** matrice_Map, int int_mapSize, float float_diffRate, PlayerInfo *p_playerInfo) //Work In Progress
{
    float int_nbObstacles = int_mapSize * float_diffRate * TAUX_OBSTACLE;
    float int_nbBonus = int_mapSize/5 * (1/float_diffRate) * TAUX_BONUS;

    int int_maxCoord = int_mapSize - 1 ;
    int int_qrtCoord = int_mapSize/ 4 ;
    int int_rdmRow;
    int int_rdmCol = int_mapSize;
    p_playerInfo->coordonnees.x = 0;
    p_playerInfo->coordonnees.y = 0;
         
    switch ( RNG(1,4) ) //Placement du personnages aleatoirement dans un des 4 coins de la map, et placement du drapeau en consequence semi-aléatoirement
    {
    case 2:
        matrice_Map[int_maxCoord][0]= REP_CHARACTER;
        p_playerInfo->coordonnees.x = int_maxCoord;//on donne les informations du placement du personnage dans le récapitulatif des informations du joueur
        int_rdmRow = RNG( 0, int_qrtCoord );
        int_rdmCol = RNG( int_maxCoord - int_qrtCoord + int_rdmRow - int_qrtCoord, int_maxCoord);
        break;
    case 3:
        matrice_Map[0][int_maxCoord]= REP_CHARACTER;
        p_playerInfo->coordonnees.y = int_maxCoord;
        int_rdmRow = RNG( int_maxCoord - int_qrtCoord, int_maxCoord );
        int_rdmCol = RNG( 0, int_rdmRow - int_maxCoord + int_qrtCoord );
        break;
    case 4:
        matrice_Map[int_maxCoord][int_maxCoord]= REP_CHARACTER;
        p_playerInfo->coordonnees.x = int_maxCoord;
        p_playerInfo->coordonnees.y = int_maxCoord;
        int_rdmRow = RNG( 0, int_qrtCoord );
        int_rdmCol = RNG( 0, int_qrtCoord - int_rdmRow );
        break;
    default:
        matrice_Map[0][0]= REP_CHARACTER;
        int_rdmRow = RNG( int_maxCoord - int_qrtCoord, int_maxCoord );
        int_rdmCol = RNG( int_maxCoord - int_rdmRow + int_qrtCoord, int_maxCoord );
        break;
    } 
    matrice_Map[int_rdmRow][int_rdmCol] = REP_END ;
    
    while( int_nbObstacles > 0 ) { //Placement des Obstacles
        int_rdmRow = RNG(0,int_maxCoord);
        int_rdmCol = RNG(0,int_maxCoord);
        if( CoordCompare(matrice_Map, int_rdmRow, int_rdmCol, REP_DEFAULT) ) {
            switch (RNG(1,10) < 2)
            {
                case 0:
                    matrice_Map = PlaceObstacle(matrice_Map, int_rdmRow, int_rdmCol, int_mapSize, float_diffRate, 1, REP_OBSTACLE1);
                    break;
                case 1:
                    matrice_Map = PlaceObstacle(matrice_Map, int_rdmRow, int_rdmCol, int_mapSize, float_diffRate, 1, REP_OBSTACLE2);
                    break;
            }
            int_nbObstacles-- ;
        }
    }
    while( int_nbBonus > 0 ) { //Placement des Bonus
        int_rdmRow = RNG(0,int_maxCoord);
        int_rdmCol = RNG(0,int_maxCoord);
        //printf("%d,%d\n", int_rdmRow, int_rdmCol);
        if( CoordCompare(matrice_Map, int_rdmRow, int_rdmCol, REP_DEFAULT) ) {
            int_nbBonus--;
            switch (RNG(1,2))
            {
                case 1:
                    matrice_Map[int_rdmRow][int_rdmCol] = REP_BONUS1;
                    break;
                case 2:
                    matrice_Map[int_rdmRow][int_rdmCol] = REP_BONUS2;
                    break;
            }
        }
    }

    for( int i = 0 ; i<int_mapSize; i++) { //fill the left empty space 
       for( int j = 0 ; j<int_mapSize ; j++){
            if( CoordCompare(matrice_Map, i, j, REP_DEFAULT) ){
                matrice_Map[i][j] = REP_VOID;
            }
        }
    }
    return (matrice_Map);
}

int*** GenerateMatriceDistance(int int_mapSize, int*** matrice_Distance)
{
    for ( int i = 0; i < int_mapSize; i++)  // boucle vérification des lignes 
    {
        for(int j = 0;j<int_mapSize;j++)    // Boucle vérification des colonnes 
        {   
        if (i == 0){
            matrice_Distance[i][j][1] = 0;
            matrice_Distance[i][j][0] = 0;
            matrice_Distance[i][j][2] = 0;
        }else{
            if (matrice_Distance[i-1][j][5] == 0){
                matrice_Distance[i][j][1] = RNG(1,MAX_DISTANCE);
            }else{
                matrice_Distance[i][j][1] = matrice_Distance[i-1][j][5];
            } 
            if (j == 0)
            {
                matrice_Distance[i][j][0] = 0;
                matrice_Distance[i][j][6] = 0;
            }else{
                if (matrice_Distance[i-1][j-1][4] == 0)
                {
                    matrice_Distance[i][j][0] = RNG(1,MAX_DISTANCE);
                }else{
                    matrice_Distance[i][j][0] = matrice_Distance[i-1][j-1][4];
                }
            }        
            if(j == int_mapSize-1)
            {
                matrice_Distance[i][j][2] = 0;
                matrice_Distance[i][j][4] = 0;
            }else{
                if (matrice_Distance[i-1][j+1][6] ==0)
                {
                    matrice_Distance[i][j][2] = RNG(1,MAX_DISTANCE);
                }else{
                    matrice_Distance[i][j][2] = matrice_Distance[i-1][j+1][6];
                }
            }
        }
        if (i == (int_mapSize-1)){
            matrice_Distance[i][j][5] = 0;
            matrice_Distance[i][j][4] = 0;
            matrice_Distance[i][j][6] = 0;
        }else{       
            if (matrice_Distance[i+1][j][1] == 0){
               matrice_Distance[i][j][5] = RNG(1,MAX_DISTANCE);
            }else{
                matrice_Distance[i][j][5] = matrice_Distance[i+1][j][1];
            }
            if (j == 0)
            {
                matrice_Distance[i][j][6] = 0;
            }else{
                if (matrice_Distance[i+1][j-1][2] == 0)
                {
                    matrice_Distance[i][j][6] = RNG(1,MAX_DISTANCE);
                }else{
                    matrice_Distance[i][j][6] = matrice_Distance[i+1][j-1][2];
                }
            }
            if(j == int_mapSize-1)
            {
                matrice_Distance[i][j][4] = 0;
            }else{
                if (matrice_Distance[i+1][j+1][0] == 0)
                {
                    matrice_Distance[i][j][4] = RNG(1,MAX_DISTANCE);
                }else{
                    matrice_Distance[i][j][4] = matrice_Distance[i+1][j+1][0];
                }
            }
        }    
        if (j == 0){
            matrice_Distance[i][j][7] = 0;
        }else{
            if (matrice_Distance[i][j-1][3] == 0){
                matrice_Distance[i][j][7] = RNG(1,MAX_DISTANCE);
            }else{
               matrice_Distance[i][j][7] = matrice_Distance[i][j-1][3];
            }
        }
        if (j == (int_mapSize-1)){
            matrice_Distance[i][j][3] = 0;
        }else{
            if (matrice_Distance[i][j+1][3] == 0){
                matrice_Distance[i][j][3] = RNG(1,MAX_DISTANCE);
            }else{
                matrice_Distance[i][j][3] = matrice_Distance[i][j+1][7];
            }
            }
        }
    }
   return (matrice_Distance);
}

int CheckEachDirection(int** matrice_Map, coordonnees coord_curr, int int_maxCoord, List* pl_CurrentPath, int int_Start, int* pi_totalChecked)
{
     if(*pi_totalChecked >= MAX_ITERATION_CHMAP ){ // kill la recherche si la map a necessiter plus de n check
        free(pl_CurrentPath->firstnode);
        free(pl_CurrentPath);
        return 0;
    }
    *pi_totalChecked = *pi_totalChecked + 1;
    int bool_PathFound = 0;
    int TabModifCoordCheck[16];
    switch(int_Start){ //tableau pour guider la verification en fonction du pt de depart du joueur pour accelerer la verif (ça accelere pas mal)
        case 1: ;// 0:0
            int Tab1[16] = { 1, 1, 0, 1, 1, 0, -1, 1, 1, -1, -1, 0, 0, -1, -1, -1 };
            for(int i=0; i<16; i++){
                TabModifCoordCheck[i] = Tab1[i];
            } break;
        case 2: ;//0:MAXCOORD
            int Tab2[16] = { 1, -1, 1, 0, 0, -1, 1, 1, -1, -1, 0, 1, -1, 0, -1, 1 };
            for(int i=0; i<16; i++){
                TabModifCoordCheck[i] = Tab2[i];
            } break;
        case 3: ;//MAXCOORD:0
            int Tab3[16] = { -1, 1, -1, 0, 0, 1, 1, 1, 1, 0, -1, -1, -1, 0, 1, -1 };
            for(int i=0; i<16; i++){
                TabModifCoordCheck[i] = Tab3[i];
            } break;
        case 4: ;//MAXCOORD:MAXCOORD
            int Tab4[16] = { -1, -1, -1, 0 ,0 ,-1 ,-1 ,1 ,1 ,-1 ,0 ,1 ,1 ,0 ,1 ,1 };
            for(int i=0; i<16; i++){
                TabModifCoordCheck[i] = Tab4[i];
            } break;
        default:
            exit(EXIT_FAILURE);
            break;
    }
    for(int i=0; i<16; i=i+2){
        bool_PathFound = CheckPath(
                                    matrice_Map,
                                    ModifCoord(coord_curr, coord_curr.x + TabModifCoordCheck[i], coord_curr.y + TabModifCoordCheck[i+1]),
                                    int_maxCoord,
                                    pl_CurrentPath,
                                    int_Start,
                                    pi_totalChecked
                                  );
        if(bool_PathFound){
            free(pl_CurrentPath->firstnode);
            free(pl_CurrentPath);
            return 1;
        }
    }
    if(!bool_PathFound){
        free(pl_CurrentPath->firstnode);
        free(pl_CurrentPath);
        return 0;
    }
    return 0;
}

int CheckPath(int** matrice_Map, coordonnees coord_curr, int int_maxCoord, List* pl_CheckedPath, int int_Start, int* pi_totalChecked) //verifie si la matrice map generer possede un chemin faisable recursivement;
{
    int bool_PathFound;
    if( !IsBetween(coord_curr.x, 0, int_maxCoord) || !IsBetween(coord_curr.y, 0, int_maxCoord)){ //si le chemin arrive a une bordure
        return 0;
    } else if(CoordCompare(matrice_Map, coord_curr.x, coord_curr.y, REP_END)){ //chemin trouvé
        return 1;
    } else if(CoordCompare(matrice_Map, coord_curr.x, coord_curr.y, REP_OBSTACLE1) || CoordCompare(matrice_Map, coord_curr.x, coord_curr.y, REP_OBSTACLE2)){ //la case actuelle du chemin est un obstacle
        return 0;
    } else  {
        if(IsInList(pl_CheckedPath, coord_curr))
        {
            return 0;
        } else {
            List* pl_CurrentPath = InitList(coord_curr);
            if(pl_CheckedPath != NULL && pl_CheckedPath->firstnode != NULL){
                pl_CurrentPath->firstnode->next=pl_CheckedPath->firstnode;
            }
            // DisplayPathInMap(matrice_Map,int_maxCoord+1, pl_CurrentPath);
            bool_PathFound = CheckEachDirection(matrice_Map, coord_curr, int_maxCoord, pl_CurrentPath, int_Start, pi_totalChecked);
            return(bool_PathFound);
        }

    }
}


int** InitMap(int int_mapSize, float float_diffRate, PlayerInfo* p_playerInfo) //fonction qui init la map (alloc, gener, check si faisable)
{
    DebugInfoPlayer(*p_playerInfo);
    int** matrice_Map = AllocMatriceMap(int_mapSize); // Allocation de la Matrice Map
    int int_totalChecked = -1;

    ClearTerm();
    printf("Generating a Doable Map...\n");
    int bool_mapDoable = 0;
    while(!bool_mapDoable)  //Generation d'une Map Faisable avec une difference d'energie pas trop grande par rapport à BASE ENRGIE x mapSize
    {

        matrice_Map = InitMatriceMap(matrice_Map, int_mapSize);
        matrice_Map = GenerateMap(matrice_Map, int_mapSize, float_diffRate, p_playerInfo);
    
        int_totalChecked = 0;
        bool_mapDoable = CheckPath(
                                    matrice_Map,
                                    p_playerInfo->coordonnees,
                                    int_mapSize - 1,
                                    NULL,
                                    DefineStartPlayer(p_playerInfo, int_mapSize),
                                    &int_totalChecked
                                  );

    }
    ClearTerm();
    return (matrice_Map);
}

int*** InitDistance(int int_mapSize)
{
    int*** matrice_Distance= AllocMatriceDistance(int_mapSize);
    matrice_Distance = GenerateMatriceDistance(int_mapSize, matrice_Distance);
    return (matrice_Distance);
}


void ExitWithoutSave() {
    ClearTerm();
    exit(EXIT_SUCCESS);
}
