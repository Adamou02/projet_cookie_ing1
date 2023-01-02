#include "Miscellanous.h"



int RNG(int min, int max)
{
    return ( ( rand() % (max - min + 1) ) + min );
}

int CoordCompare(int** matrice_map, int int_x, int int_y, char constant_rep)
{
    //puts("on compare\n");
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


coordonnees DefineEndGame(int int_mapSize, int** matrice_map)
{
    coordonnees coord;
    for(int i = 0; i<int_mapSize; i++)
    {
        for(int j = 0;j<int_mapSize; j++)
        {
            if (CoordCompare(matrice_map, i,j,REP_END))
            {
               
                coord.x = j;
                coord.y = i;
                return (coord);
            }
            
        }
    }
}


////////////////////////////////////////
// FONCTIONS POUR LES LISTES CHAINEES //
////////////////////////////////////////

Node* CreateNode(coordonnees coord, int is_bonus) // Créer une nouvelle node à ajouter dans la liste
{
    Node *node = malloc(sizeof(*node));
    if(!node){
        free(node);
        exit(EXIT_FAILURE);
    }
    node->coordonnees = coord;
    node->is_bonus = is_bonus;
    node->next = NULL;
    return node;
}

List* InitList(coordonnees coord, int is_bonus) //initialise une liste chaine de coord avec des coord en param
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
    node_new->is_bonus=is_bonus;
    list_new->firstnode = node_new;
    return(list_new);
}

List_d* InitList_d(int int_x, int int_y) //initialise une liste chaine de coord avec des coord en param
{
    List_d *list_new = malloc(sizeof(*list_new));
    Node_d *node_new = malloc(sizeof(*node_new));
    if(list_new == NULL || node_new == NULL){
        free(list_new);
        free(node_new);
        puts("Error in InitList_d");
        exit(EXIT_FAILURE);
    }
    node_new->next = NULL;
    node_new->DataD.x=int_x;
    node_new->DataD.y=int_y;
    node_new->DataD.distance=0;
    for(int i = 0 ; i < (2*(TAILLE_BIG_MAP * TAILLE_BIG_MAP)); i ++){ node_new->DataD.chemin[i] = 100;}
    node_new->DataD.chemin[0] = int_x;
    node_new->DataD.chemin[1] = int_y;
    list_new->firstnode = node_new;
    return(list_new);
}


void AddNode(List* p_list, coordonnees coord, int is_bonus) // Ajoute une node en début de liste 
{       
    /*creation de la nouvel node*/
    if(p_list == NULL){
        p_list = InitList(coord, 0);
    } else {
        Node *node_new = CreateNode(coord, is_bonus);
        if(p_list == NULL){
            puts("Error in AddNode");
            exit(EXIT_FAILURE);
        }
        node_new->next = p_list->firstnode;
        p_list->firstnode = node_new;
    }
}


coordonnees FindLastStep (Node_d* Node)
{
    int int_cpt = 0;
    while (Node->DataD.chemin[int_cpt] != 100)
    {
        int_cpt++;
        if(int_cpt == (2*(TAILLE_BIG_MAP * TAILLE_BIG_MAP))) break;
    }

    coordonnees coord; 
    
    if(int_cpt == 2 || int_cpt == 3)
    {
        coord.x = INF;
        coord.y = INF;
        return (coord);
    }
    coord.x = Node->DataD.chemin[int_cpt - 4];
    coord.y = Node->DataD.chemin[int_cpt - 3 ];
    return (coord);
}



int ReturnDiff(int** matrice_map, int*** matrice_distance, int int_mapSize, Node_d* Node,int int_diffX, int int_diffY,int int_position,int int_mode)
{

    if ( IsBetween((Node->DataD.y)+(int_diffY), 0, int_mapSize-1) && IsBetween((Node->DataD.x)+(int_diffX), 0, int_mapSize-1) && !(matrice_distance[Node->DataD.x][Node->DataD.y][int_position] == 0))
        {
            if( !CoordCompare(matrice_map, (Node->DataD.x)+(int_diffX), (Node->DataD.y)+(int_diffY), REP_OBSTACLE1) &&  !CoordCompare(matrice_map, (Node->DataD.x)+(int_diffX), (Node->DataD.y)+(int_diffY), REP_OBSTACLE2)){
                if (((FindLastStep(Node).x) != ((Node->DataD.x)+(int_diffX))) || ((FindLastStep(Node).y) != ((Node->DataD.y)+(int_diffY)) ))
                {
                    if(int_mode == 1) return (Node->DataD.distance + matrice_distance[(Node->DataD.x)][(Node->DataD.y)][int_position]);
                    if(int_mode == 2){
                        if( CoordCompare(matrice_map, (Node->DataD.x)+(int_diffX), (Node->DataD.y)+(int_diffY), REP_BONUS1) || CoordCompare(matrice_map, (Node->DataD.x)+(int_diffX), (Node->DataD.y)+(int_diffY), REP_BONUS2))
                        {
                            matrice_distance[Node->DataD.x][Node->DataD.y][int_position] = -4;
                            return((Node->DataD.distance)-4);
                        }
                    matrice_distance[Node->DataD.x][Node->DataD.y][int_position] = 1;
                    return((Node->DataD.distance) + 1);
                    } 
                }else{
                matrice_distance[Node->DataD.x][Node->DataD.y][int_position] = 0;
            }
            }else{
                matrice_distance[Node->DataD.x][Node->DataD.y][int_position] = 0;
            }
    }
}


Node_d* FindLowerWay(List_d* p_list, Node_d* Node, Node_d* GoodNode, int** matrice_map, int*** matrice_distance, int int_mapSize, int int_goodDistance, int *int_position, int *int_distance, coordonnees coordEnd, int int_mode)
{

    if (Node->DataD.x == coordEnd.y && Node->DataD.y == coordEnd.x)
        { 
            return (Node);
        }
    
    int tab[8];
        
    for(int u = 0 ; u <8; u++){ tab[u] = INF;}

    tab[0] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,-1,-1,0,int_mode);
    tab[1] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,-1,0,1,int_mode);
    tab[2] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,-1,1,2,int_mode);
    tab[3] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,0,1,3,int_mode);
    tab[4] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,1,1,4,int_mode);
    tab[5] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,1,0,5,int_mode);
    tab[6] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,1,-1,6,int_mode);
    tab[7] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,0,-1,7,int_mode);

    int int_tmp = int_goodDistance;
    for(int test = 0 ; test < 8; test++)
    {
        if ((tab[test] < int_goodDistance) && tab[test] != 0)
        {
            int_goodDistance = tab[test];
            *int_position = test;
        }
    }

    if(int_goodDistance == INF){
        return(FindLowerWay(p_list, Node->next, GoodNode,matrice_map, matrice_distance, int_mapSize , int_goodDistance,int_position,int_distance,coordEnd,int_mode));
    }
    if (int_goodDistance != int_tmp)
    {
        *int_distance = matrice_distance[Node->DataD.x][Node->DataD.y][*int_position];   
    
        if (Node->next == NULL)
        {
            matrice_distance[Node->DataD.x][Node->DataD.y][*int_position] = 0;
            return (Node);
        }else{ 
            
            return (FindLowerWay(p_list, Node->next, Node, matrice_map, matrice_distance, int_mapSize, int_goodDistance,int_position,int_distance,coordEnd,int_mode));
        }
    }else{
        if (Node->next== NULL)
        {
            matrice_distance[GoodNode->DataD.x][GoodNode->DataD.y][*int_position] = 0;
            return (GoodNode);
        }else{ 
            
            return (FindLowerWay(p_list , Node->next, GoodNode,matrice_map, matrice_distance, int_mapSize , int_goodDistance,int_position,int_distance,coordEnd,int_mode));
        }
    }

}

int AddEnd(Node* NodeHere, Node* node){
    while(NodeHere->next != NULL){
        return(AddEnd(NodeHere->next,node));
    }
    NodeHere->next = node;
    return 0;
}



List* EndDijkstra(Node_d * Arrive)
{
    int i = 0;
    coordonnees FirstNode;
    FirstNode.x = Arrive->DataD.chemin[i];
    FirstNode.y = Arrive->DataD.chemin[i+1];
    int nothing = 1;
    //printf("%d - %d\n", FirstNode.x,FirstNode.y);
    List* BetterWay = InitList(FirstNode, 0);
    i = i + 2;
    while (Arrive->DataD.chemin[i] != 100)
    {
        coordonnees tmp;
        tmp.x = Arrive->DataD.chemin[i];
        tmp.y = Arrive->DataD.chemin[i+1];
        Node* tmp_Node = CreateNode(tmp,0);
        nothing = AddEnd(BetterWay->firstnode,tmp_Node);
        i = i + 2 ;
    }
    nothing = 1;

    return (BetterWay);
}



Node_d* CreateDNode(int int_x, int int_y, int distance, Node_d* NodeD, Node_d* Node_Suivante) // Créer une nouvelle node à ajouter dans la liste
{
    Node_d *node = malloc(sizeof(*node));
    if(!node){
        free(node);
        exit(EXIT_FAILURE);
    }
    node->DataD.x = int_x;
    node->DataD.y = int_y;
    node->DataD.distance = distance + NodeD->DataD.distance;

    int int_cpt = 0;

    for(int i = 0 ; i < (2*(TAILLE_BIG_MAP * TAILLE_BIG_MAP)); i++)
    {
        node->DataD.chemin[i] = 100; 
    }
    while((NodeD->DataD.chemin[int_cpt]) != 100) {
        node->DataD.chemin[int_cpt] = NodeD->DataD.chemin[int_cpt];
        int_cpt++;
    }
    node->DataD.chemin[int_cpt] = int_x;
    node->DataD.chemin[int_cpt+1] = int_y;
    node->next = Node_Suivante;

    return (node);
}


int AddNode_d(List_d* p_list, Node_d* firstNode, int int_x, int int_y, int int_distance, Node_d* NodeD)
{
    if (firstNode->next == NULL)
    {
        firstNode->next = CreateDNode(int_x, int_y, int_distance, NodeD, NULL);
        return (0);
    }else{
        if (firstNode->next->DataD.x == int_x && firstNode->next->DataD.y == int_y)
        {
            if (firstNode->next->DataD.distance > int_distance + NodeD->DataD.distance)
            {
                firstNode->next->DataD.distance = int_distance + NodeD->DataD.distance;
                firstNode->next->DataD.chemin[100] = NodeD->DataD.chemin[100];
                return (0);
            }else{
                return (0);                
            }
        }else{
            return(AddNode_d(p_list, firstNode->next, int_x, int_y, int_distance, NodeD));
        }
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

void RemoveNode_d(List_d* p_list) // retire la dernière node de la liste
{
    if(p_list == NULL){
        puts("Error in RemoveNode");
        exit(EXIT_FAILURE);
    }
    if(p_list->firstnode != NULL){
        Node_d* node_toRemove =  p_list->firstnode;
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

void GetfirstNode(List* p_list, int* p_last_x, int* p_last_y, int* is_bonus) // renvoit les coordonnées de la dernière node ajoutée
{   
    if(p_list == NULL){
        exit(EXIT_FAILURE);
    }
    Node* node_current = p_list->firstnode;
    printf("%d %d\n", node_current->coordonnees.x, node_current->coordonnees.y);
    *p_last_x = node_current->coordonnees.x;
    *p_last_y = node_current->coordonnees.y;
    *is_bonus = node_current->is_bonus;
}  

void FreeList(List* p_list)// Libère la mémoire alloué à la liste
{
    if(p_list == NULL){
        return;
    }
    while(p_list->firstnode != NULL){
        RemoveNode(p_list);
    }
    free(p_list);
}

void FreeList_d(List_d* p_list)// Libère la mémoire alloué à la liste
{
    if(p_list == NULL){
        return;
    }
    while(p_list->firstnode != NULL){
        RemoveNode_d(p_list);
    }
    free(p_list);
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

void CopyList(List* p_list, List* p_listCopy){
    if(p_list == NULL || p_list->firstnode == NULL){
        return;
    } else {
        Node * node_current = p_list->firstnode;
        while(node_current != NULL){
            AddNode(p_listCopy,node_current->coordonnees,node_current->is_bonus);
            node_current = node_current->next;
        }
        return;
    }
}


void ClearTerm()
{
    //printf("\033[H\033[2J");
    system("clear");
}

void CopyMap(int** matrice_Map, int** matrice_MapCopy, int int_mapSize)
{
    for(int i=0; i<int_mapSize; i++){
        for(int j=0; j<int_mapSize; j++){
            matrice_MapCopy[i][j] = matrice_Map[i][j];
        }
    }
}

void CopyMatriceDist(int*** matrice_Distance, int*** matrice_DistanceCopy, int int_mapSize)
{
    for(int i=0; i<int_mapSize; i++){
        for(int j=0; j<int_mapSize; j++){
            for(int k=0; k<8; k++){
                matrice_DistanceCopy[i][j][k] = matrice_Distance[i][j][k];
            }
            
        }
    }
}


List* InvertList(List* p_list)
{   
    int int_ListSize= LengthList(p_list);
    coordonnees TabList[int_ListSize];
    Node* node_current = p_list->firstnode;
    for( int j=int_ListSize-1; j>=0; j--){
        TabList[j]= node_current->coordonnees;
        node_current = node_current->next;
        RemoveNode(p_list);
    } 
    List* p_listinverted = InitList(TabList[0], 0);
    for(int i=1; i<int_ListSize; i++){
       AddNode(p_listinverted, TabList[i], 0);
    }
    CopyList(p_listinverted, p_list);
    FreeList(p_listinverted);
    return (p_list);
}

