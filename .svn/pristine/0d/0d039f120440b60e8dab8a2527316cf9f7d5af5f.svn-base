#ifndef RICHMAN_DISPLAY_H
#define RICHMAN_DISPLAY_H

#include <stdbool.h>

#define START_X 50
#define START_Y 3

#define COLOR_IS_RED()  (printf("\033[31m"))
#define COLOR_IS_GREEN()  (printf("\033[32m"))
#define COLOR_IS_BLUE()  (printf("\033[34m"))
#define COLOR_IS_YELLOW()  (printf("\033[33m"))
#define COLOR_IS_WHITE()  (printf("\033[37m"))

#define GET_MAP_FLAG(game, pos_id, connect) do { \
    if((game)->map[pos_id].house_flag){ \
        (connect) = (game)->map[pos_id].house_flag->flag; \
    } \
    else { \
        (connect) = SPACE; \
    } \
}while(0);

//#define GOTO_CMD() printf("\033[19;63H")
#define GOTO_TIP() printf("\033[5;0H")

#define GOTOXY(x, y) do { \
    printf("\033[%d;%dH", y, x); \
}while(0);

#define CLEAN_GAME_FACE() do { \
    for(int i = 0; i < 16; ++ i){ \
        for(int j = START_X; j < 140; ++ j){ \
            GOTOXY(j,i); \
            printf(" "); \
        } \
    } \
}while(0);

#define CLEAN_TIPS() do { \
    for(int i = 0; i < 16; ++ i){ \
        for(int j = 0; j < START_X; ++ j){ \
            GOTOXY(j,i); \
            printf(" "); \
        } \
    } \
    GOTO_TIP(); \
}while(0);

#define CLEAN_LINE() do { \
    for(int i = 0; i < 7; ++ i){ \
        printf("\033[K"); \
        printf("\n"); \
    } \
}while(0);

typedef struct POS_ {
    int x;
    int y;
}POS;

bool DisplayMap(GAME *game_state);
void ShowTips(char *name, char _flag, POS _pos);
void DisplayBlock(POS pos, char connect, char owner);
#endif //RICHMAN_DISPLAY_H
