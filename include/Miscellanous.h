#ifndef MISCELLANOUS_H
#define MISCELLANOUS_H
    #define square(a)  (a)*(a)
    #include <stdlib.h>
    #include <math.h>
    #include <stdio.h>
    #include <time.h>
    #include <string.h>
    #include <time.h>  
    #include "Constant.h" 

    typedef struct coordonnees{ // Structure contenant des coordonnées 
        int x;
        int y;
    } coordonnees;

    typedef struct Node{ // enregistre les coordonnées dans une list 
        coordonnees coordonnees;
        int is_bonus;
        struct Node *next;
    } Node;

    typedef struct List{
        Node* firstnode;
    } List;

    
    //List pour Dijkstra

    typedef struct DataD DataD;
    struct DataD{ // Structure contenant séquence du parcours, coordonnées actuelles, distance du point de départ
        int x;
        int y;
        int distance;
        int chemin[(2*(TAILLE_BIG_MAP * TAILLE_BIG_MAP))];
    };

    typedef struct Node_d{ // enregistre les  distance dans une liste
        DataD DataD;
        struct Node_d *next;
    } Node_d;

    typedef struct List_d{
        Node_d* firstnode;
    } List_d;
    


    typedef struct PlayerInfo{ // Structure contennant les informations du joueur
        coordonnees coordonnees;
        int energy;
        int distance;
        int gain_energy;
        int lost_energy;
        int backward;
    } PlayerInfo;

    typedef struct GameInformation{ // Structure contenant toute les infos necessaire pour pouvoir debuter une partie et pour liberer la memoire allouer a tout moment 
        int int_mapSize;
        float float_diffRate;
        int **matrice_Map;
        int ***matrice_Distance;
        List* p_listpath;
        PlayerInfo s_playerInfo;
    } GameInformation;

    int RNG(int min, int max);

    int CoordCompare(int** matrice_map, int int_x, int int_y, char constant_rep);

    int CoordCompare2(int** matrice_map, coordonnees coord, char constant_rep);

    int IsBetween(int int_Comp, int int_min, int int_max);

    void printf_center(const char* str);

    void InitRNG();

    int DefineStartPlayer(PlayerInfo* p_playerInfo, int int_mapSize);

    coordonnees ModifCoord(coordonnees coord, int int_x, int int_y);
    
    coordonnees DefineEndGame(int int_mapSize, int** matrice_map);
    
    Node* CreateNode(coordonnees coord, int bonus);

    List* InitList(coordonnees coord, int is_bonus);

    List_d* InitList_d(int int_x, int int_y);

    void AddNode(List* p_list, coordonnees coord, int bonus);

    coordonnees FindLastStep (Node_d* Node);

    Node_d* FindLowerWay(List_d* p_list, Node_d* Node, Node_d* GoodNode, int** matrice_map, int*** matrice_distance, int int_mapSize, int int_goodDistance, int *int_position, int *int_distance, coordonnees coordEnd);

    List* EndDijkstra(Node_d * Arrive);
    
    Node_d* CreateDNode( int int_x, int int_y, int distance, Node_d* NodeD, Node_d* Node_Suivante);

    int AddNode_d(List_d* p_list, Node_d* firstNode, int int_x, int int_y, int int_distance, Node_d* NodeD);

    void RemoveNode(List* p_list);

    void RemoveNode_d(List_d* p_list);

    long LengthList(List *p_list);

    void GetfirstNode(List* p_list, int* p_last_x, int* p_last_y, int* is_bonus);
    
    void FreeList(List* p_list);

    void FreeList_d(List_d* p_list);

    int IsInList(List* p_list, coordonnees coord);

    void CopyList(List* p_list, List* p_listCopy);

    void ClearTerm();

    void CopyMap(int** matrice_Map, int** matrice_MapCopy, int int_mapSize);

#endif
