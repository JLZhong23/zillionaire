#ifndef RICHMAN_RICHMAN_H
#define RICHMAN_RICHMAN_H

#include <time.h>

#define COMMAND_ROLL "roll"
#define COMMAND_QUWRY "query"
#define COMMAND_HELP "help"

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

char get_house_flag(int i);


GAME *game_state = NULL;
char role_name[4][16] = {"钱夫人", "阿士伯", "金贝贝", "孙小美"};

#endif //RICHMAN_RICHMAN_H
