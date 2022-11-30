#include "Miscellanous.h"

int RNG(int min, int max)
{
    return ( ( rand() % (max - min + 1) ) + min );
}

int CoordCompare(int** matrice_map, int int_x, int int_y, char constant_rep)
{
    return (matrice_map[int_x][int_y] == constant_rep);
}

int CoordCompare2(int** matrice_map, coordonnees coord, char constant_rep)
{
    return(CoordCompare(matrice_map, coord.x, coord.y, constant_rep));
}

int IsBetween(int int_Comp, int int_min, int int_max){
    return (int_Comp >= int_min && int_Comp <= int_max);
}

void printf_center(const char* str)
{
    unsigned int n;
    for (n = 0; n < (204-strlen(str)) / 2; n++)
    {
        putchar(' ');
    }
    printf("%s", str);
}

void InitRNG()
{
    srand(time(NULL)); //init RNG
}

coordonnees ModifCoord(coordonnees coord, int int_x, int int_y)
{
    coord.x= int_x;
    coord.y= int_y;
    return coord;  
}

int DefineStartPlayer(PlayerInfo* p_playerInfo, int int_mapSize) //fonction retournant un int entre 1  et 4 copris en fonction du placement de depart du personnage
{
    int int_maxCoord = int_mapSize - 1;
    if(p_playerInfo->coordonnees.x == 0){
        if(p_playerInfo->coordonnees.y == 0){
            return (1);
        } else if(p_playerInfo->coordonnees.y == int_maxCoord){
            return(3);
        } else {
            return (-1);
        }

    } else if(p_playerInfo->coordonnees.x == int_maxCoord){
        if(p_playerInfo->coordonnees.y == 0){
            return (2);
        } else if(p_playerInfo->coordonnees.y == int_maxCoord){
            return(4);
        } else {
            return (-1);
        }

    } else {
        return (-1);
    }    
}


////////////////////////////////////////
// FONCTIONS POUR LES LISTES CHAINEES //
////////////////////////////////////////

Node* CreateNode(coordonnees coord) // Créer une nouvelle node à ajouter dans la liste
{
    Node *node = malloc(sizeof(*node));
    if(!node){
        free(node);
        exit(EXIT_FAILURE);
    }
    node->coordonnees = coord;
    node->next = NULL;
    return node;
}

List* InitList(coordonnees coord) //initialise une liste chaine de coord avec des coord en param
{
    List *list_new = malloc(sizeof(*list_new));
    Node *node_new = malloc(sizeof(*node_new));
    if(list_new == NULL || node_new == NULL){
        free(list_new);
        free(node_new);
        puts("Error in InitList");
        exit(EXIT_FAILURE);
    }
    node_new->next = NULL;
    node_new->coordonnees.x=coord.x;
    node_new->coordonnees.y=coord.y;
    list_new->firstnode = node_new;
    return(list_new);
}


void AddNode(List* p_list, coordonnees coord) // Ajoute une node en début de liste 
{       
    /*creation de la nouvel node*/
    if(p_list == NULL){
        p_list = InitList(coord);
    } else {
        Node *node_new = CreateNode(coord);
        if(p_list == NULL){
            puts("Error in AddNode");
            exit(EXIT_FAILURE);
        }
        /*insert new node in the list*/
        node_new->next = p_list->firstnode;
        p_list->firstnode = node_new;
    }
}


void RemoveNode(List* p_list) // retire la dernière node de la liste
{
    if(p_list == NULL){
        puts("Error in RemoveNode");
        exit(EXIT_FAILURE);
    }
    if(p_list->firstnode != NULL){
        Node* node_toRemove =  p_list->firstnode;
        p_list->firstnode = p_list->firstnode->next;
        free(node_toRemove);
    }
}

long LengthList(List *p_list) // Permet d'obtenir la taille de la liste
{
    long long_taille = 0;
    Node* node_current = p_list->firstnode;
    while(node_current != NULL)
    {
        long_taille = long_taille + 1;
        node_current = node_current->next;
    }
    return long_taille;
}

void GetfirstNode(List* p_list, int* p_last_x, int* p_last_y) // renvoit les coordonnées de la dernière node ajoutée
{   
    if(p_list == NULL){
        exit(EXIT_FAILURE);
    }
    Node* node_current = p_list->firstnode;
    *p_last_x = node_current->coordonnees.x;
    *p_last_y = node_current->coordonnees.y;
}

void FreeList(List* p_list)// Libère la mémoire alloué à la liste
{
    if(p_list == NULL){
        free(p_list);
        return;
    }
    Node* node_current = p_list->firstnode;
    Node** node_tmp;
    while(node_current != NULL){
        node_tmp = &node_current;
        node_current = node_current->next;
        free(*node_tmp);
    }
    free(node_current);
}

int IsInList(List* p_list, coordonnees coord) //verifie si des coordonnees appartienne à une liste passer en parametre
{
    if(p_list == NULL ){
        return 0;
    } else if(p_list->firstnode == NULL){
        return 0;
    } else {
         Node* node_current = p_list->firstnode;
        int bool_isIn = 0;
        while(node_current != NULL && !bool_isIn ){
            bool_isIn = (node_current->coordonnees.x == coord.x) && (node_current->coordonnees.y == coord.y);
            node_current = node_current->next;
        }   
        return (bool_isIn);
    }
}



