#include "Movements.h"

//Verifie la touche pressée
int KeyAvailable(int key)
{
    if (key == UP || key == MAJ_UP || key == DOWN || key == MAJ_DOWN ||key == LEFT || key == MAJ_LEFT ||key == RIGHT || key == MAJ_RIGHT ||key == UP_LEFT || key == MAJ_UP_LEFT ||key == UP_RIGHT || key == MAJ_UP_RIGHT || key == DOWN_LEFT || key == MAJ_DOWN_LEFT || key == DOWN_RIGHT || key == MAJ_DOWN_RIGHT || key == STEP_BACK || key == MAJ_STEP_BACK || key == SAVE || key == MAJ_SAVE || key == LEAVE_WITHOUT_SAVE || key == MAJ_LEAVE_WITHOUT_SAVE) {
        return 1;
    }
    else {
        return 0;
    }
}

//Change les valeur des variables dans UpdatePosition pour changer la position du personnage dans la matrice map
void ChangePosition(int key, int* x, int* y, PlayerInfo *p_playerInfo) 
{
    *x=p_playerInfo->coordonnees.x;
    *y=p_playerInfo->coordonnees.y;
    switch (key)
    {
    case LEFT:
        *y=*y-1;
        break;
    case MAJ_LEFT:
        *y=*y-1;
        break;
    case RIGHT:
        *y=*y+1;
        break;
    case MAJ_RIGHT:
        *y=*y+1;
        break;
    case UP:
        *x=*x-1;
        break;
    case MAJ_UP:
        *x=*x-1;
        break;
    case DOWN:
        *x=*x+1;
        break;
    case MAJ_DOWN:
        *x=*x+1;
        break;
    case UP_LEFT:
        *x=*x-1;
        *y=*y-1;
        break;
    case MAJ_UP_LEFT:
        *x=*x-1;
        *y=*y-1;
        break;
    case DOWN_LEFT:
        *x=*x+1;
        *y=*y-1;
        break;
    case MAJ_DOWN_LEFT:
        *x=*x+1;
        *y=*y-1;
        break;
    case UP_RIGHT:
        *x=*x-1;
        *y=*y+1;
        break;
    case MAJ_UP_RIGHT:
        *x=*x-1;
        *y=*y+1;
        break;
    case DOWN_RIGHT:
        *x=*x+1;
        *y=*y+1;
        break;
    case MAJ_DOWN_RIGHT:
        *x=*x+1;
        *y=*y+1;
        break;
    default:
        break;
    }
}

//Saute une ligne à chaque fois qu'on affiche 3 blocs touche sur le terminal
void SkipLine(int line_count, int *p_line_count) {
    if (line_count == 3) {
        printf("\n\n");
        *p_line_count=0;
    }
}

//Affiche les touches pour les coups dispos (et leur coup en distance)
void ShowKeyAvailable(PlayerInfo *p_playerInfo_player,  int*** matrice_Distance)
{
    int line_count=0;
    printf("\nListe des touches :\n\n");
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][0]) {
        printf("%s : a  (%d kilomètres)", UP_LEFT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][0]);
        printf("\t\t");
        line_count++;
    }
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][1]) {
        printf("%s : z  (%d kilomètres)", UP_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][1]);
        printf("\t\t");
        line_count++;
    }
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][2]) {
        printf("%s : e  (%d kilomètres)", UP_RIGHT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][2]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][7]) {
        printf("%s : q  (%d kilomètres)", LEFT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][7]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][3]) {
        printf("%s : d  (%d kilomètres)", RIGHT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][3]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][5]) {
        printf("%s : x  (%d kilomètres)", DOWN_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][5]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][6]) {
        printf("%s : w  (%d kilomètres)", DOWN_LEFT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][6]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][4]) {
        printf("%s : c  (%d kilomètres)", DOWN_RIGHT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][4]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    printf("%s : r ", STEP_BACK_ICON);
    line_count++;
    printf("\t\t");
    SkipLine(line_count, &line_count);
    printf("%s : p ", SAVE_ICON);
    printf("\n\n");
}

//Permet de lire la touche pressé. Le programme est en pause tant que utilisateur appuie touche
int ListenKeyboard()
{
    FILE* flux = stdin;
    tcgetattr(0, &old); //On recupere les propriétés actuelles du terminal
    current = old; //on les stock dans une variable
    current.c_lflag &= ~ICANON; //desactive input/output du terminal
    current.c_lflag &= ~ECHO; //Active le mode silencieux (pas de sortie texte du terminal)
    tcsetattr(0, TCSANOW, &current); //Applique ces modifications sur le terminal
    int ch;

    do
    {
        ch = getc(flux);
    } while (!KeyAvailable(ch));

    current.c_lflag |= ECHO; //desactive le mode silencieux
    tcsetattr(0, TCSANOW, &current); //Applique cette modification sur le terminal
    return ch;
}



int** UpdatePosition(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo) // Met à jour les informations de la map en fonction du déplacement
{   
    matrice_map[p_playerInfo->coordonnees.x][p_playerInfo->coordonnees.y] = REP_VOID;
    matrice_map[int_wanted_x][int_wanted_y] = REP_CHARACTER;
    return (matrice_map);
}

void UpdatePlayerInfo(int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo)//Met à jour les infos du joueur en fonction du déplacement
{
    p_playerInfo->coordonnees.x = int_wanted_x;
    p_playerInfo->coordonnees.y = int_wanted_y;
    p_playerInfo->energy = (p_playerInfo->energy) - LOST_ENERGY;
    p_playerInfo->distance = p_playerInfo->distance + 1;
}

void PlayerOnBonus(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo)//Donne de l'énergie à un joueur lorsqu'il marche sur un bonus
{
    p_playerInfo->energy = (p_playerInfo->energy) + GAIN_ENERGY;
    p_playerInfo->gain_energy = (p_playerInfo->energy) + GAIN_ENERGY;
}

void PlayerOnObstacle(PlayerInfo *p_playerInfo) //retire de l'énergie au joueur lorsqu'il rentre dans un obstacle
{
    p_playerInfo->energy = (p_playerInfo->energy) - LOST_ENERGY;
    p_playerInfo->lost_energy = (p_playerInfo->energy) - LOST_ENERGY;
}

int** AfterMovement(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo, int int_mapSize, int *int_victory)// Permet de déplacer ou non le joueur en fonction du déplacement demandé et de la carte
{
    if(int_wanted_x>=0 && int_wanted_x<int_mapSize && int_wanted_y>=0 && int_wanted_y<int_mapSize){
      switch(matrice_map[int_wanted_x][int_wanted_y])
        {
        case REP_OBSTACLE1 :
            PlayerOnObstacle(p_playerInfo);
            // printf("Test obstacle");
            break;

        case REP_OBSTACLE2 :
            PlayerOnObstacle(p_playerInfo);
            // printf("Test obstacle");
            break;
        
        case REP_BONUS1 :
            PlayerOnBonus(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, p_playerInfo);
            printf("Test bonus");
            break;

        case REP_BONUS2 :
        PlayerOnBonus(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
        matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
        UpdatePlayerInfo(int_wanted_x, int_wanted_y, p_playerInfo);
        // printf("Test bonus");
        break;
    
        case REP_END :
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, p_playerInfo);
            *int_victory = 1;
            break;
        
        default :
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, p_playerInfo);
            break;
       }
     
    }
    return (matrice_map);
}
