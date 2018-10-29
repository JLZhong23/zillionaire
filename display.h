#ifndef RICHMAN_DISPLAY_H
#define RICHMAN_DISPLAY_H

#include <stdbool.h>

#define START_X 0
#define START_Y 0

#define COLOR_IS_RED()  (printf("\033[31m"))
#define COLOR_IS_GREEN()  (printf("\033[32m"))
#define COLOR_IS_BLUE()  (printf("\033[34m"))
#define COLOR_IS_YELLOW()  (printf("\033[33m"))
#define COLOR_IS_WHITE()  (printf("\033[37m"))

#define CLEANSCREAM() do { \
    printf("\033[2J "); \
    printf("\033[1;1H"); \
}while(0);

#define GOTOXY(x, y) do { \
    printf("\033[%d;%dH", y, x); \
}while(0);


typedef struct POS_ {
    int x;
    int y;
}POS;

bool DispalyMap(GAME *game_state);
void ShowTips(char *name, char _flag, POS _pos);
void DisplayBlock(POS pos, char connect);
#endif //RICHMAN_DISPLAY_H
