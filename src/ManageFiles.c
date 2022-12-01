#ifndef MANAGEFILES_H
#define MANAGEFILES_H

#include "Constant.h"
#include "InitGame.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

char* AllocMapString(int int_mapSize){
    char* MapString = malloc((2*int_mapSize*int_mapSize+1)*sizeof(*MapString));
    return(MapString);
}

char* AllocDistanceString(int int_mapSize){
    char* DistanceString = malloc((16*int_mapSize*int_mapSize+1)*sizeof(*DistanceString));
    return(DistanceString);
}

char* MatriceMapToString(int** matrice_Map, int int_mapSize, char* MapString){
    int int_curseur = 0;
    char Current_Char;
    char Current_Str[2];
    for(int int_curseurBis = 0; int_curseurBis < int_mapSize; int_curseurBis++)
    {
        while ( (int_curseur+1)%(int_mapSize+1) != 0 )
        {
            //Recuperation du char correspondant a chaque case
            Current_Char = matrice_Map[int_curseurBis][int_curseur];
            Current_Str[0] = Current_Char;
            //Ajout du char au string
            strcat(MapString, Current_Str); //LERREUR EST LA
            if(( (int_curseur+2)%(int_mapSize+1) != 0 ) ){
                //Ajout d'un separateur entre chaque char, sauf a la fin d'une ligne
                strcat(MapString, ".");
            }
            int_curseur++;
        }
        //Ajout d'un separateur different en fin de ligne
        strcat(MapString, "*");
        int_curseur = 0;
    }
    return(MapString);
}

char* MatriceDistanceToString(int*** matrice_Distance, int int_mapSize, char* DistanceString){
    char Current_Str[2];
    for (int i = 0; i < int_mapSize; i++)
    {
        for (int j = 0; j < int_mapSize; j++)
        {   
            for (int k = 0; k < 8; k++){
                //Recuperation de la distance
                sprintf(Current_Str, "%d", matrice_Distance[i][j][k]);
                //Ajout de la valeur recuperee au string
                strcat(DistanceString, Current_Str);
                if(k != 7){
                    //Ajout d'un separateur entre chaque distance, sauf pour la derniere de chaque case
                    strcat(DistanceString, ".");
                }
            }
            if(j != int_mapSize-1){
                //Ajout d'un separateur different entre chaque case, sauf pour la derniere de chaque ligne
                strcat(DistanceString, "*");
            }
        }
        if(i != int_mapSize-1){
            //Ajout d'un separateur entre chaque ligne, sauf en fin de string
            strcat(DistanceString, "/");
        }
    }
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

void StockCurrentTurn(char* MapString, char* DistanceString, PlayerInfo * s_playerInfo_player){
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "a");
    //Verification de l'ouverture du fichier
    if(Current_Game_CSV == NULL){
        printf("\nErreur de chemin d'accès au fichier\n\n");
    }
    //Ajout de toutes les donnees au fichier
    fprintf(Current_Game_CSV, "%d,%d,%d,%d,%d,%d,%d,%s,%s\n", s_playerInfo_player->coordonnees.x, s_playerInfo_player->coordonnees.y, 
        s_playerInfo_player->energy, s_playerInfo_player->distance, s_playerInfo_player->gain_energy, 
        s_playerInfo_player->lost_energy, s_playerInfo_player->backward, MapString, DistanceString);
    fclose(Current_Game_CSV);
}

void GetAllInfo(char* MapString, char* DistanceString, PlayerInfo * s_playerInfo_player, int int_mapSize){
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
    strcpy(MapString,strtok(NULL, ",;"));
    strcpy(DistanceString,strtok(NULL, ",;"));
    
    fclose(Current_Game_CSV);
    free(CSV_String);
}

#endif
