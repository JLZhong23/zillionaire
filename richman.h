#ifndef RICHMAN_RICHMAN_H
#define RICHMAN_RICHMAN_H

#include <time.h>

#define COMMAND_ROLL "roll"
#define COMMAND_QUWRY "query"
#define COMMAND_HELP "help"
#define COMMAND_QUIT "quit"
#define COMMAND_SELLHOUSE "sell"
#define COMMAND_STEP "step"

#define STR_EQU(str1, str2) (strcasecmp((str1), (str2)) == 0)

#define INIT_PLAYER_HOUSE(player) do { \
    for(int i = 0; i < 57; ++i) { \
        (player)->house_id[i] = NULL; \
    } \
} while(0);

#define GET_STEP(_step) do { \
    srand(time(NULL)); \
    (_step) = rand() % 6; \
    ++ (_step); \
} while(0);

#define ROLE_EXIST(role_id, all_role, status) do { \
    (status) = false; \
    for(int i = 0; i < 4; ++i){ \
        if((role_id) == (all_role)[i]){ \
            (status) = true; \
            break; \
        } \
    } \
}while(0);

#define CHECK_OUT_PLAYER(game) do { \
    if ((game)->current_player->next) { \
        (game)->current_player = (game)->current_player->next; \
    }\
    else { \
        (game)->current_player = (game)->player;\
    } \
}while(0);


bool ChooseRole();
void InitMap();
void GameStart();
void cmd_help();
void cmd_query();
void cmd_roll();
void cmd_quit();
void cmd_buyhouse();
void cmd_sellhouse();
void cmd_step();

GAME *game_state = NULL;
char role_name[4][16] = {"Q钱夫人", "A阿士伯", "J金贝贝", "S孙小美"};

#endif //RICHMAN_RICHMAN_H
