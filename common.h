#ifndef RICHMAN_COMMON_H
#define RICHMAN_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define HOSPITAL 'H'    // hospital
#define TOOL 'T'        // tools
#define SPACE '0'       // space
#define GIFT 'G'        // gift house
#define MAGIC 'M'       // magic house
#define PRISON 'P'      // prison
#define MINERAL '$'     // mineral area
#define START 'S'       // start area
#define ROADBLOCK '#'
#define BOMB '@'

#define T_NO 0
#define T_BLOCK 1
#define T_BOMB 2
#define T_ROBOT 3




#define P_QFR 'Q'       // qian fu ren who color is red
#define P_ASB 'A'       // a shi bo who color is green
#define P_SXM 'S'       // sun xiao mei who color is blue
#define P_JBB 'J'       // jin bei bei who color is yellow

#define INITIAL_MONEY 10000

#define GET_PLAYER_FLAG ((game_state)->map[(game_state)->current_player->cur_pos].house_flag)

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

    // money
    int money;

    // number of point
    int point;

    // house owned by player, this is a pointer array, size is 57
    // every one point to a MAP_BLOCK zone.
    struct MAP_BLOCK_ * house_id[57];

    // next player
    struct PLAYER_ *next;
}PLAYER;



typedef struct MAP_BLOCK_ {
    // id of owner
    int house_owner_id;

    // house flag which to display
    // value just as 0 # @ $ Q H M ....
    char house_flag;

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


#endif //RICHMAN_COMMON_H
