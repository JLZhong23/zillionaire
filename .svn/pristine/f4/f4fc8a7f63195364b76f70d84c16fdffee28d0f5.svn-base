#ifndef RICHMAN_COMMON_H
#define RICHMAN_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 1024
#define MAP_SIZE 70
#define HOSPITAL_POS 14
#define SLEEP_TIME 3
#define SLEEP_TIME_PRISON 2
#define MAGIC_TIME 2

#define HOSPITAL 'H'    // hospital
#define TOOL 'T'        // tools
#define SPACE '0'       // space
#define GIFT 'G'        // gift house
#define MAGIC 'M'       // magic house
#define PRISON 'P'      // prison
#define PARK 'P'
#define MINERAL '$'     // mineral area
#define START 's'       // start area
#define ROADBLOCK '#'
#define BOMB '@'

#define T_NO 0
#define T_BLOCK 1
#define T_BOMB 2
#define T_ROBOT 3

#define G_MONEY 2000
#define G_POINT 200
#define G_NO_RENT_TIME 6


#define P_QFR 'Q'       // qian fu ren who color is red
#define P_ASB 'A'       // a shi bo who color is green
#define P_SXM 'S'       // sun xiao mei who color is blue
#define P_JBB 'J'       // jin bei bei who color is yellow


#define CLEANSCREEN() do { \
    printf("\033[2J "); \
    printf("\033[1;1H"); \
}while(0);

#define DEL_HOUSE_FLAG(map_id, connect) do { \
    H_FLAG *pre_flag = NULL; \
    H_FLAG *temp_flag = game_state->map[map_id].house_flag; \
    while(temp_flag) { \
        if(temp_flag->flag == (connect)){ \
            if(!pre_flag){ \
                game_state->map[map_id].house_flag = temp_flag->next; \
            }\
            else{ \
                pre_flag->next = temp_flag->next; \
            } \
            free(temp_flag); \
            break; \
        } \
    pre_flag = temp_flag; \
    temp_flag = temp_flag->next; \
    }\
}while(0);

#define ADD_HOUSE_FLAG(map_id, connect) do { \
    H_FLAG *temp_h_flag; \
    temp_h_flag = (H_FLAG *)malloc(sizeof(H_FLAG)); \
    temp_h_flag->flag = connect; \
    temp_h_flag->next = game_state->map[map_id].house_flag; \
    game_state->map[map_id].house_flag = temp_h_flag; \
}while(0);

#define GET_PLAYER_FLAG(game, flag) do { \
    (flag) = ((game)->current_player->player_name[0]); \
}while(0);

#define PAUSE() do { \
    getchar(); \
    getchar(); \
}while(0);

#define ROLE_EXIST(role_id, all_role, status) do { \
    (status) = false; \
    for(int i = 0; i < 4; ++i){ \
        if((role_id) == (all_role)[i]){ \
            (status) = true; \
            break; \
        } \
    } \
}while(0);

#define GET_OWNER_COLOR(owner_id, players, owner_flag) do { \
    (owner_flag) = SPACE;\
    PLAYER *tmp_ply = players; \
    while(tmp_ply) {\
        if((tmp_ply)->player_id == (owner_id)) { \
            (owner_flag) = (tmp_ply)->player_name[0]; \
            break; \
        } \
        tmp_ply = tmp_ply->next; \
    } \
}while(0);

// the house owner in hospital or prison
#define GET_OWNER_STATUS(owner_id, players, sleep_time_flag) do { \
    PLAYER *tmp_ply = players; \
    while(tmp_ply) {\
        if((tmp_ply)->player_id == (owner_id)) { \
            (sleep_time_flag) = (tmp_ply)->sleep_time; \
            break; \
        } \
        tmp_ply = tmp_ply->next; \
    } \
}while(0);

typedef struct PLAYER_ {
    // user id
    int player_id;

    // user name
    char player_name[16];

    // current position
    int cur_pos;

    // number of bombs
    int bomb_num;

    // number of robot baby
    int robot_num;

    // number of road block
    int block_num;

    // number of player need to skip
    int sleep_time;

    // number of player don`t pay the rent
    int no_rent_time;

    // money
    int money;

    // number of point
    int point;

    // house owned by player, this is a pointer array, size is 64
    // every one point to a MAP_BLOCK zone.
    struct MAP_BLOCK_ * house_id[64];

    // next player
    struct PLAYER_ *next;
}PLAYER;

typedef struct H_FLAG_ {
    char flag;
    struct H_FLAG_ *next;
}H_FLAG;

typedef struct MAP_BLOCK_ {
    // id of owner
    int house_owner_id;

    // house flag which to display
    // value just as 0 # @ $ Q H M ....
    H_FLAG *house_flag;

    // house level and equal 0 when no owner
    int house_level;

    // value of this map block
    int map_value;

    // type of tool on this map block
    int ToolType;
}MAP_BLOCK;


typedef struct GAME_ {
    // total number of player
    int player_num;

    // current player pointer
    PLAYER *current_player;

    // all player pointer
    PLAYER *player;

    // file path to save
    char path[50];

    // all the map block
    MAP_BLOCK map[70];
}GAME;


int UsFgetsNum();
char UsFgetsChar();
int UsFgetsRole(int *exist_role);

#endif //RICHMAN_COMMON_H
