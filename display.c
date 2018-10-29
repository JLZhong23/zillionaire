#include "common.h"
#include "display.h"

bool DispalyMap(GAME *game_state)
{
    bool ret = false;
    int curr_pos_id = 0;
    char connect;
    POS pos;

    if(!game_state){
        printf("The game pointer is null!\n");
        goto Exit;
    }

    CLEANSCREAM();
    pos.y = START_Y;
    pos.x = START_X;

    for(int i = 0 ; curr_pos_id < 29; ++i, ++curr_pos_id){
        ++ pos.x;
        connect = game_state->map[curr_pos_id].house_flag;
        DisplayBlock(pos, connect);
    }

    for(int i = 0; curr_pos_id < 35; ++i, ++curr_pos_id){
        ++ pos.y;
        connect = game_state->map[curr_pos_id].house_flag;
        DisplayBlock(pos, connect);
    }

    for(int i = 0 ; curr_pos_id < 64; ++i, ++curr_pos_id){
        -- pos.x;
        connect = game_state->map[curr_pos_id].house_flag;
        DisplayBlock(pos, connect);
    }

    for(int i = 0; curr_pos_id < 70; ++i, ++curr_pos_id){
        -- pos.y;
        connect = game_state->map[curr_pos_id].house_flag;
        DisplayBlock(pos, connect);
    }

    pos.y += 8;
    ShowTips(game_state->current_player->player_name, GET_PLAYER_FLAG, pos);

    ret = true;

    Exit:
    return ret;
}


// there is a bug to fix tue color
void ShowTips(char *name, char _flag, POS _pos)
{
    switch (_flag)
    {
        case P_QFR:
            COLOR_IS_RED();
            break;
        case P_ASB:
            COLOR_IS_GREEN();
            break;
        case P_SXM:
            COLOR_IS_BLUE();
            break;
        case P_JBB:
            COLOR_IS_YELLOW();
            break;
        default:
            COLOR_IS_WHITE();
            break;
    }

    GOTOXY(_pos.x, _pos.y);
    printf("**%s >", name);

}

void DisplayBlock(POS pos, char connect)
{
    GOTOXY(pos.x, pos.y);

    //set color
    switch (connect)
    {
        case P_QFR:
            COLOR_IS_RED();
            break;
        case P_ASB:
            COLOR_IS_GREEN();
            break;
        case P_SXM:
            COLOR_IS_BLUE();
            break;
        case P_JBB:
            COLOR_IS_YELLOW();
            break;
        default:
            COLOR_IS_WHITE();
            break;
    }

    printf("%c", connect);

}