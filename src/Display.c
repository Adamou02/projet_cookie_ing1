#include "Display.h"



void DisplayMap(int** matrice_Map, int int_mapSize)
{
    int int_curseur = 0;
    char* constant_caseDisplay = ERROR;
    system("clear");
    printf(" ");
    for(int i=0; i<int_mapSize+1; i++)
    {
        printf("%s", DOWNBAR);
    }
    printf("\n");
    for(int int_curseurBis = 0; int_curseurBis < int_mapSize; int_curseurBis++)
    {
        printf(" %s", SIDEBAR);
        while ( (int_curseur+1)%(int_mapSize+1) != 0 )
        {
            switch (matrice_Map[int_curseurBis][int_curseur])
            {
                case REP_CHARACTER :
                    constant_caseDisplay = CHARACTERE;
                    break;                
                case REP_END :
                    constant_caseDisplay = END;
                    break;                
                case REP_BONUS1 :
                    constant_caseDisplay = BONUS_COOKIE;
                    break;                
                case REP_BONUS2 :
                    constant_caseDisplay = BONUS_APPLE;
                    break;                
                case REP_OBSTACLE1 :
                    constant_caseDisplay = OBSTACLE_TREE;
                    break;
                case REP_OBSTACLE2 :
                    constant_caseDisplay = OBSTACLE_BEE;
                    break;                
                case REP_VOID :
                    constant_caseDisplay = VOID;
                    break;
                case REP_DEFAULT :
                    constant_caseDisplay = ERROR;
                    break;           
                default :
                    constant_caseDisplay = ERROR;
                    break;       
            }
            printf("%s", constant_caseDisplay);
            int_curseur++;
        }
        printf("%s\n", SIDEBAR);
        int_curseur = 0;
    }
    printf(" ");
    for(int i=0; i<int_mapSize+1; i++)
    {
        printf("%s", UPBAR);
    }
    printf("\n");
}


//Fonctions de DEBUG pour dev, ne serons pas utiliser dans le process final

void DebugDisplayMap(int** matrice_Map, int int_mapSize)
{
    for( int i = 0 ; i<int_mapSize; i++) { 
        printf("%d> ", i);
       for( int j = 0 ; j<int_mapSize; j++){
            printf("%c", matrice_Map[i][j]);
            if(j != int_mapSize - 1) {
                printf(",");
            } else {
                printf("\n");
            }
        }
        if(i != int_mapSize - 1) {
            printf(";");
        } else {
            printf("\n");
        }
    }
    return;
}

void DebugDisplayMatriceDistance(int int_mapSize, int*** matrice_Distance)
{
    for(int p = 0; p < int_mapSize; p++)
    {
        printf("ligne %d :", p);
        for ( int m = 0; m < int_mapSize; m++)
        {
            printf(" %d :[", m);
            for ( int n = 0; n < 8; n++)
            {
                if(n != 7) {
                    printf("%d,", matrice_Distance[p][m][n]);
                } else {
                    printf("%d", matrice_Distance[p][m][n]);
                }
                
            }
            printf("],");
        }
        printf("\n");
    }
}

void DebugInfoPlayer(PlayerInfo s_playerInfo)
{   
    printf("Votre position x : %d\n",s_playerInfo.coordonnees.x);
    printf("Votre position y : %d\n",s_playerInfo.coordonnees.y);
    printf("Votre energie : %d\n",s_playerInfo.energy);
    printf("Votre distance parcourue : %d\n",s_playerInfo.distance);
    printf("Votre energie gagnée : %d\n",s_playerInfo.gain_energy);
    printf("Votre energie perdue : %d\n",s_playerInfo.lost_energy);
    printf("Vos retour en arrière disponible : %d\n",s_playerInfo.backward);
}


void EditTerminal()
{
    system("\
coX=`xdpyinfo | grep dimensions | sed -r 's/^[^0-9]*([0-9]+x[0-9]+).*$/\\1/' | cut -d 'x' -f1`;\n\
coY=`xdpyinfo | grep dimensions | sed -r 's/^[^0-9]*([0-9]+x[0-9]+).*$/\\1/' | cut -d 'x' -f2`;\n\
resize -s `echo \"$(( $coY / 10 )) $(( $coX / 8 ))\"`>/dev/null;\n\
");

}


void PrintList(List* p_list) //affiche une liste passer en parametre
{
    if(p_list == NULL){
        printf("Liste Vide\n");
        return;
    }
    Node* node_current = p_list->firstnode;
    printf("List: |");
    while(node_current != NULL)
    {
        printf("x=%d, y=%d |", node_current->coordonnees.x, node_current->coordonnees.y);
        node_current = node_current->next;
    }
    printf("\n");
}

void PrintFirstList(List* p_list)
{
    if(p_list == NULL || p_list->firstnode == NULL){
        printf("Liste Vide\n");
        return;
    }
    printf("x=%d, y=%d \n", p_list->firstnode->coordonnees.x, p_list->firstnode->coordonnees.y);
}


void DisplayPathInMap(int** matric_Map, int int_mapSize, List* p_list)
{
    int** matric_tmp = AllocMatriceMap(int_mapSize);
    for(int i=0; i<int_mapSize; i++){
        for(int j=0; j<int_mapSize; j++){
            matric_tmp[i][j] = matric_Map[i][j];
        }
    }
    Node* node_current = p_list->firstnode;
    while(node_current != NULL)
    {
        matric_tmp[node_current->coordonnees.x][node_current->coordonnees.y]='.';
        node_current = node_current->next;
    }    
    DisplayMap(matric_tmp, int_m
