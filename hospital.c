#include<stdio.h>
#include "common.h"
#include "richman.h"
#include "hospital.h"

#define MAP_SIZE 70

#define HOSPITAL_POS 14

#define NO_TOOL_TYPE 0
#define BOMB_TOOL_TYPE 1
#define BLOCK_TO0L_TYPE 2

#define SLEEP_TIME 3



//determin whether blocked or bombed or nothing happend
void BlockedOrBombed(int step) {
    for (int i = 0; i <= step; i ++) {
        int pos = (game_state->current_player->cur_pos + i) % MAP_SIZE;

        if (game_state->map[pos].ToolType == BOMB_TOOL_TYPE) {     // bomb
            game_state->map[pos].ToolType = NO_TOOL_TYPE;
            game_state->current_player->cur_pos = HOSPITAL_POS;
            game_state->current_player->sleep_time = SLEEP_TIME;
            break;
        } else if (game_state->map[pos].ToolType == BLOCK_TO0L_TYPE) {
            game_state->map[pos].ToolType = NO_TOOL_TYPE;
            game_state->current_player->cur_pos = pos;
            break;
        }
    }
}