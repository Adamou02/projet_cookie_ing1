  #include "ManageFiles.h"

int ExistFile(char char_NameFile[])
{
    FILE* File = fopen(char_NameFile, "r+");  
    if (File == NULL){// Le fichier n'existe pas
        return 0;
    }else{// Le fichier existe  
        fclose(File);
        return 1;
    }
}

void createFile(char char_NameFile[])
{
    FILE* File = fopen(char_NameFile, "w+");  
        fclose(File);
}

int SupprFile(char char_NameFile[])
{
    int int_A = ExistFile(char_NameFile);
    if (int_A == 0){// Le fichier n'existe pas, on ne peut donc pas le supprimer
        return 0;
    }else{// Le fichier existe, on le supprime
        remove(char_NameFile);
        return 1;
    }
}

//*******************************************************************
//******FONTIONS DE SAUVEGARDE/RECUPERATION PARTIE*******************
//*******************************************************************

void GetPlayerInfo(int int_mapSize, PlayerInfo * s_playerInfo_player)
{
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "r");
    char* CSV_String = (char *)malloc(int_mapSize*int_mapSize*64+11);
    //Recuperation de toutes les donnees
    fgets(CSV_String, int_mapSize*int_mapSize*64+11 ,Current_Game_CSV);

    //Separation et implementation des donnees aux variables de jeu
    s_playerInfo_player->coordonnees.x = atoi(strtok(CSV_String, ",;"));
    s_playerInfo_player->coordonnees.y = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->energy = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->distance = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->gain_energy = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->lost_energy = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->backward = atoi(strtok(NULL, ",;"));
    
    fclose(Current_Game_CSV);
    free(CSV_String);
    return;
}

char* GetMapString(char* MapString, int int_mapSize)
{
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "r");
    char* CSV_String = (char *)malloc(int_mapSize*int_mapSize*64+11);
    //Recuperation de toutes les donnees
    fgets(CSV_String, int_mapSize*int_mapSize*64+11 ,Current_Game_CSV);

    //Separation et implementation des donnees aux variables de jeu
    strtok(CSV_String, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strcpy(MapString,strtok(NULL, ",;"));
    
    fclose(Current_Game_CSV);
    free(CSV_String);
    return(MapString);
}

char* GetDistanceString(char* DistanceString, int int_mapSize)
{
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "r");
    char* CSV_String = (char *)malloc(int_mapSize*int_mapSize*64+11);
    //Recuperation de toutes les donnees
    fgets(CSV_String, int_mapSize*int_mapSize*64+11 ,Current_Game_CSV);

    //Separation et implementation des donnees aux variables de jeu
    strtok(CSV_String, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strcpy(DistanceString,strtok(NULL, ",;"));
    
    fclose(Current_Game_CSV);
    free(CSV_String);
    return(DistanceString);
}

char* AllocMapString(int int_mapSize){
    char* MapString = malloc((2*int_mapSize*int_mapSize+1)*sizeof(*MapString));
    return(MapString);
}

char* AllocDistanceString(int int_mapSize){
    char* DistanceString = malloc((16*int_mapSize*int_mapSize+1)*sizeof(*DistanceString));
    return(DistanceString);
}

char* MatriceMapToString(int** matrice_Map, int int_mapSize, char* MapString)
{
    int int_nbchar = 0;
    int int_curseur = 0;
    char Current_Char;
    char c_sep1 = '.';
    char c_sep2 = '*';

    for(int int_curseurBis = 0; int_curseurBis < int_mapSize; int_curseurBis++)
    {
        while ( (int_curseur+1)%(int_mapSize+1) != 0 )
        {
            //Recuperation du char correspondant a chaque case
            Current_Char = matrice_Map[int_curseurBis][int_curseur];
            //Ajout du char au string
            *(MapString + int_nbchar) = Current_Char;
            int_nbchar++;
            
            if(( (int_curseur+2)%(int_mapSize+1) != 0) ){
                //Ajout d'un separateur entre chaque char, sauf a la fin d'une ligne
                *(MapString + int_nbchar) = c_sep1;
                int_nbchar++;
            }
            int_curseur++;
            printf("%d\n", int_nbchar);
        }
        //Ajout d'un separateur different en fin de ligne
        *(MapString + int_nbchar) = c_sep2;
        int_nbchar++;
        int_curseur = 0;
        printf("%d\n", int_nbchar);
        
    }
    *(MapString + int_nbchar) = '\0';
    return(MapString);
}

char* MatriceDistanceToString(int*** matrice_Distance, int int_mapSize, char* DistanceString){
    char Current_Str[2];
    int int_nbchar = 0;
    strcpy(DistanceString, "");
    for (int i = 0; i < int_mapSize; i++)
    {
        for (int j = 0; j < int_mapSize; j++)
        {   
            for (int k = 0; k < 8; k++){
                //Recuperation de la distance
                sprintf(Current_Str, "%d", matrice_Distance[i][j][k]);
                //Ajout de la valeur recuperee au string
                *(DistanceString + int_nbchar) = Current_Str[0];
                int_nbchar++;
                if(k != 7){
                    //Ajout d'un separateur entre chaque distance, sauf pour la derniere de chaque case
                    *(DistanceString + int_nbchar) = '.';
                    int_nbchar++;
                }
            }
            if(j != int_mapSize-1){
                //Ajout d'un separateur different entre chaque case, sauf pour la derniere de chaque ligne
                *(DistanceString + int_nbchar) = '*';
                int_nbchar++;
            }
        }
        if(i != int_mapSize-1){
            //Ajout d'un separateur entre chaque ligne, sauf en fin de string
            *(DistanceString + int_nbchar) = '/';
            int_nbchar++;
        }
    }
    *(DistanceString + int_nbchar) = '\0';
    return(DistanceString);
}

int** StringToMatriceMap(char* MapString, int int_mapSize, int** matrice_Map){
    char* current_Char = strtok(MapString, ".*");
    for(int i=0; i<int_mapSize ; i++){
        for(int j=0; j<int_mapSize ; j++){
            //Separation du string et ajout des valeurs recuperees dans la matrice
            matrice_Map[i][j] = (int)current_Char[0];
            current_Char = strtok(NULL, ".*");
        }
    }
    //Reinitialisation du string
    strcpy(MapString, "");
    return (matrice_Map);
}

int*** StringToMatriceDistance(char* DistanceString, int int_mapSize, int*** matrice_Distance){
    char* current_Char = strtok(DistanceString, ".*/");
    for(int i=0; i<int_mapSize ; i++){
        for(int j=0; j<int_mapSize ; j++){
            for(int k=0; k<8 ; k++){
                //Separation du string et ajout des valeurs recuperees dans la matrice
                matrice_Distance[i][j][k] = atoi(current_Char);
                current_Char = strtok(NULL, ".*/");
            }
        }
    }
    //Reinitialisation du string
    strcpy(DistanceString, "");
    return (matrice_Distance);
}

char* SaveMap(int** matrice_Map, int int_mapSize)
{
    char* MapString = AllocMapString(int_mapSize);
    MatriceMapToString(matrice_Map, int_mapSize, MapString);
    return(MapString);
}

int** RestoreMap(int** matrice_Map, int int_mapSize)
{
    char* MapString = AllocMapString(int_mapSize);
    MapString = GetMapString(MapString, int_mapSize);
    StringToMatriceMap(MapString, int_mapSize, matrice_Map);
    free(MapString);
    return(matrice_Map);
}

char* SaveDistance(int*** matrice_Distance, int int_mapSize)
{
    char* DistanceString = AllocDistanceString(int_mapSize);
    MatriceDistanceToString(matrice_Distance, int_mapSize, DistanceString);
    return(DistanceString);
}

int*** RestoreDistance(int*** matrice_Distance, int int_mapSize)
{
    char* DistanceString = AllocDistanceString(int_mapSize);
    DistanceString = GetDistanceString(DistanceString, int_mapSize);
    StringToMatriceDistance(DistanceString, int_mapSize, matrice_Distance);
    free(DistanceString);
    return(matrice_Distance);
}

// void GetAllInfo(char* MapString, char* DistanceString, PlayerInfo * s_playerInfo_player, int int_mapSize){
//     FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "r");
//     char* CSV_String = (char *)malloc(int_mapSize*int_mapSize*64+11);
//     //Recuperation de toutes les donnees
//     fgets(CSV_String, int_mapSize*int_mapSize*64+11 ,Current_Game_CSV);

//     //Separation et implementation des donnees aux variables de jeu
//     s_playerInfo_player->coordonnees.x = atoi(strtok(CSV_String, ",;"));
//     s_playerInfo_player->coordonnees.y = atoi(strtok(NULL, ",;"));
//     s_playerInfo_player->energy = atoi(strtok(NULL, ",;"));
//     s_playerInfo_player->distance = atoi(strtok(NULL, ",;"));
//     s_playerInfo_player->gain_energy = atoi(strtok(NULL, ",;"));
//     s_playerInfo_player->lost_energy = atoi(strtok(NULL, ",;"));
//     s_playerInfo_player->backward = atoi(strtok(NULL, ",;"));
//     strcpy(MapString,strtok(NULL, ",;"));
//     strcpy(DistanceString,strtok(NULL, ",;"));
    
//     fclose(Current_Game_CSV);
//     free(CSV_String);
// }

void StockCurrentTurn(int** matrice_Map, int*** matrice_Distance, int int_mapSize, PlayerInfo * s_playerInfo_player)
{
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "a");
    //Verification de l'ouverture du fichier
    if(Current_Game_CSV == NULL){
        printf("\nErreur de chemin d'accès au fichier\n\n");
    }
    char* MapString = SaveMap(matrice_Map, int_mapSize);
    char* DistanceString = SaveDistance(matrice_Distance, int_mapSize);
    //Ajout de toutes les donnees au fichier
    fprintf(Current_Game_CSV, "%d,%d,%d,%d,%d,%d,%d,%s,%s\n", s_playerInfo_player->coordonnees.x, s_playerInfo_player->coordonnees.y, 
        s_playerInfo_player->energy, s_playerInfo_player->distance, s_playerInfo_player->gain_energy, 
        s_playerInfo_player->lost_energy, s_playerInfo_player->backward, MapString, DistanceString);
    fclose(Current_Game_CSV);
    free(MapString);
    free(DistanceString);
    return;
}
