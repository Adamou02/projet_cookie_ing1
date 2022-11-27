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
void ChangePosition(int key, int* x, int* y, PlayerInfo *s_playerInfo_player) 
{
    *x=s_playerInfo_player->coordonnees_player.int_x;
    *y=s_playerInfo_player->coordonnees_player.int_y;
    switch (key)
    {
    case LEFT:
        *y=*y-1;
        break;
    case RIGHT:
        *y=*y+1;
        break;
    case UP:
        *x=*x-1;
        break;
    case DOWN:
        *x=*x+1;
        break;
    case UP_LEFT:
        *x=*x-1;
        *y=*y-1;
        break;
    case DOWN_LEFT:
        *x=*x+1;
        *y=*y-1;
        break;
    case UP_RIGHT:
        *x=*x-1;
        *y=*y+1;
        break;
    case DOWN_RIGHT:
        *x=*x+1;
        *y=*y+1;
        break;
    default:
        break;
    }
}

//Affiche les touches pour les coups dispos (et leur coup en distance)
void ShowKeyAvailable(PlayerInfo *p_playerInfo_player,  int*** matrice_Distance)
{
    printf("\nListe des touches :\n\n");
    printf("%s : a  (%d kilomètres)", UP_LEFT_ARROW, matrice_Distance[p_playerInfo_player->int_x][p_playerInfo_player->int_y][0]);
    printf("\t\t");
    printf("%s : e  (%d kilomètres)", UP_RIGHT_ARROW, matrice_Distance[p_playerInfo_player->int_x][p_playerInfo_player->int_y][2]);
    printf("\t\t");
    printf("%s : z  (%d kilomètres)", UP_ARROW, matrice_Distance[p_playerInfo_player->int_x][p_playerInfo_player->int_y][1]);
    printf("\t\t");
    printf("%s : p ", SAVE_ICON);
    printf("\n\n");
    printf("%s : q  (%d kilomètres)", LEFT_ARROW, matrice_Distance[p_playerInfo_player->int_x][p_playerInfo_player->int_y][7]);
    printf("\t\t");
    printf("%s : d  (%d kilomètres)", RIGHT_ARROW, matrice_Distance[p_playerInfo_player->int_x][p_playerInfo_player->int_y][3]);
    printf("\t\t");
    printf("%s : x  (%d kilomètres)", DOWN_ARROW, matrice_Distance[p_playerInfo_player->int_x][p_playerInfo_player->int_y][5]);
    printf("\n\n");
    printf("%s : w  (%d kilomètres)", DOWN_LEFT_ARROW, matrice_Distance[p_playerInfo_player->int_x][p_playerInfo_player->int_y][6]);
    printf("\t\t");
    printf("%s : c  (%d kilomètres)", DOWN_RIGHT_ARROW, matrice_Distance[p_playerInfo_player->int_x][p_playerInfo_player->int_y][4]);
    printf("\t\t");
    printf("%s : r ", STEP_BACK_ICON);
    printf("\t\t\n");
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



int** UpdatePosition(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *s_playerInfo_player) // Met à jour les informations de la map en fonction du déplacement
{   
    matrice_map[s_playerInfo_player->coordonnees_player.int_x][s_playerInfo_player->coordonnees_player.int_y] = REP_VOID;
    matrice_map[int_wanted_x][int_wanted_y] = REP_CHARACTER;
    return (matrice_map);
}

void UpdatePlayerInfo(int int_wanted_x, int int_wanted_y, PlayerInfo *s_playerInfo_player)//Met à jour les infos du joueur en fonction du déplacement
{
    s_playerInfo_player->coordonnees_player.int_x = int_wanted_x;
    s_playerInfo_player->coordonnees_player.int_y = int_wanted_y;
    s_playerInfo_player->int_energy = (s_playerInfo_player->int_energy) - LOST_ENERGY;
    s_playerInfo_player->int_distance = s_playerInfo_player->int_distance + 1;
}

void PlayerOnBonus(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *s_playerInfo_player)//Donne de l'énergie à un joueur lorsqu'il marche sur un bonus
{
    s_playerInfo_player->int_energy = (s_playerInfo_player->int_energy) + GAIN_ENERGY;
    s_playerInfo_player->int_gain_energy = (s_playerInfo_player->int_energy) + GAIN_ENERGY;
}

void PlayerOnObstacle(PlayerInfo *s_playerInfo_player) //retire de l'énergie au joueur lorsqu'il rentre dans un obstacle
{
    s_playerInfo_player->int_energy = (s_playerInfo_player->int_energy) - LOST_ENERGY;
    s_playerInfo_player->int_lost_energy = (s_playerInfo_player->int_energy) - LOST_ENERGY;
}

int** AfterMovement(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *s_playerInfo_player, int int_mapSize, int *int_victory)// Permet de déplacer ou non le joueur en fonction du déplacement demandé et de la carte
{
    if(int_wanted_x>=0 && int_wanted_x<int_mapSize && int_wanted_y>=0 && int_wanted_y<int_mapSize){
      switch(matrice_map[int_wanted_x][int_wanted_y])
        {
        case REP_OBSTACLE1 :
            PlayerOnObstacle(s_playerInfo_player);
            // printf("Test obstacle");
            break;

        case REP_OBSTACLE2 :
            PlayerOnObstacle(s_playerInfo_player);
            // printf("Test obstacle");
            break;
        
        case REP_BONUS1 :
            PlayerOnBonus(matrice_map, int_wanted_x, int_wanted_y, s_playerInfo_player);
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, s_playerInfo_player);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, s_playerInfo_player);
            printf("Test bonus");
            break;

        case REP_BONUS2 :
        PlayerOnBonus(matrice_map, int_wanted_x, int_wanted_y, s_playerInfo_player);
        matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, s_playerInfo_player);
        UpdatePlayerInfo(int_wanted_x, int_wanted_y, s_playerInfo_player);
        // printf("Test bonus");
        break;
    
        case REP_END :
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, s_playerInfo_player);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, s_playerInfo_player);
            *int_victory = 1;
            break;
        
        default :
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, s_playerInfo_player);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, s_playerInfo_player);
            break;
       }
     
    }
    return (matrice_map);
}
