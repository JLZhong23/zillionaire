#ifndef RICHMAN_RICHMAN_H
#define RICHMAN_RICHMAN_H

#include <time.h>

#define COMMAND_ROLL "roll"
#define COMMAND_QUWRY "query"
#define COMMAND_HELP "help"
#define COMMAND_QUIT "quit"
#define COMMAND_SELLHOUSE "sell"
#define COMMAND_STEP "step"
#define COMMAND_THREE "three"
#define COMMAND_BOMB "bomb"
#define COMMAND_BLOCK "block"
#define COMMAND_ROBOT "robot"

#define COMMAND_STORE_TEST "saveall"

#define INITIAL_MONEY 1000

#define STR_EQU(str1, str2) (strcasecmp((str1), (str2)) == 0)

#define INIT_PLAYER_HOUSE(player) do { \
    for(int i = 0; i < 64; ++i) { \
        (player)->house_id[i] = NULL; \
    } \
} while(0);

#define GET_STEP(_step) do { \
    srand(time(NULL)); \
    (_step) = rand() % 6; \
    ++ (_step); \
} while(0);


#define CHECK_OUT_PLAYER(game) do { \
    if ((game)->current_player->next) { \
        (game)->current_player = (game)->current_player->next; \
    }\
    else { \
        (game)->current_player = (game)->player;\
    } \
}while(0);


void SetInitMoney();
void InitMap();
void GameStart();
bool GameEnd();
void cmd_help();
void cmd_query();
void cmd_roll();
void cmd_quit();
void cmd_buyhouse();
void cmd_sellhouse();
void cmd_step();
void cmd_buythree();
void HouseShow();
bool cmd_place_bomb();
bool cmd_place_block();
bool cmd_use_robot();
bool StoreTheGameState();
GAME * LoadTheGameState();

extern int init_money ;
extern GAME *game_state ;
extern char role_name[4][16] ;

#endif //RICHMAN_RICHMAN_H
