#include "test.h"
#include "common.h"
#include "housedeal.h"

void TestInit(GAME *game_state)
{

}

void TestBuyHouseThree(GAME *game_state)
{
    for(int i = 1; i < 4; i++)
    {
        game_state->current_player->money = 
        game_state->current_player->money - game_state->map[i].map_value;
        game_state->map[i].house_owner_id = game_state->current_player->player_id;

        // 玩家中要添加该空地game_state->current_player->house[] 
        game_state->current_player->house_id[i] 
        =  &(game_state->map[i]);
        printf("恭喜你购买成功\n");
        printf("你的余额为:%d", game_state->current_player->money);
        printf("\n");
    }

}

void TestBuyHouse(GAME *game_state)
{
    game_state->map[2].house_owner_id = 0;
    game_state->current_player->cur_pos = 2;
    BuyHouse(game_state->current_player->player_id, 2, game_state);
}

void TestBankrupt(GAME *game_state)
{
    game_state->current_player->money = -100;
    game_state->map[game_state->current_player->cur_pos].house_owner_id = game_state->current_player->player_id + 1;
    BuyHouse(game_state->current_player->player_id, game_state->current_player->cur_pos, game_state);
}

void TestUpdateHouse(GAME *game_state)
{
    game_state->map[2].house_owner_id = game_state->current_player->player_id;
    BuyHouse(game_state->current_player->player_id, 2, game_state);
}
