#include "housedeal.h"
#include "common.h"

void BuyHouse(int role_id, int house_position, GAME *game_state)
{
    if(role_id>4 | role_id < 1)
    {
        printf("Error: role_id is out of 1~4!");
        PAUCE();
        return;
    }
    
    if(game_state->map[house_position].house_owner_id != 0)
    {
        printf("该房子已经被其他玩家购买");
        PAUCE();
        return;
    }
 

    char confirm;
    printf("是否确认购买：输入Y或N:");
    scanf("%c", &confirm);
    if(confirm == 'N')
    {
        printf("你已经放弃购买");
        PAUCE();    
        return;
    }
    else
    {
        game_state->current_player->money = game_state->current_player->money - game_state->map[house_position].map_value;
        game_state->map[house_position].house_owner_id = role_id;
        // 玩家中要添加该空地game_state->current_player->house[] 
        game_state->current_player->house_id[house_position] 
        =  &(game_state->map[house_position]);
        printf("恭喜你购买成功\n");
        PAUCE();
    }
}

// Update our house 
void UpdateHouse(int role_id, int house_position, GAME *game_state)
{
    if(role_id>4 | role_id < 1)
    {
        printf("Error: role_id is out of 1~4!");
        PAUCE();
        return;
    }
    
    if(game_state->map[house_position].house_owner_id != role_id)
    {
        printf("该房子还不属于你");
        PAUCE();
        return;
    }

    
    switch (game_state->map[house_position].house_level)
    {
        case 0:
            HouseUpdateOneLeve(house_position, "空地", "茅房", game_state);
            PAUCE(); 
            break;

        case 1:
            HouseUpdateOneLeve(house_position, "茅房", "洋房", game_state);
            PAUCE(); 
            break;

        case 2:
            HouseUpdateOneLeve(house_position, "洋房", "摩天楼", game_state);
            PAUCE(); 
            break;    

         case 3:
            printf("你的房子是摩天大楼，你不需要再升级");
            PAUCE(); 
            break;               

         default:
            printf("Error: house_level is out of 0~3!");
            PAUCE();
            break;
    }

}

void HouseUpdateOneLeve(int house_position, char *primary_level, char *update_level, GAME *game_state)
{
    char choose_bool; //role choose the level of house to update
    printf("你的房子是%s，你要升级的等级:\n%s\n是否选择升级:\n1.Y;\n2.N", primary_level, update_level);
    scanf("%c", &choose_bool);
    if(choose_bool == 'Y')
    {
        if(game_state->map[house_position].map_value > game_state->current_player->money)
        {
            printf("你的金钱不够升级！");
            return;
        }
        else
        {
            game_state->current_player->money = game_state->current_player->money - game_state->map[house_position].map_value;
            game_state->map->house_level = 1;
            printf("房屋成功升级为%s", update_level);
            return;
        }
    }else
    {
        printf("你已放弃升级!");
        return;
    }
}


void SellHouse(int house_position, GAME *game_state)
{
    if(game_state->map[house_position].house_owner_id != game_state->current_player->player_id)
    {
        printf("该房子还不属于你");
        PAUCE();
        return;
    }

    char confirm;
    printf("是否确认出售房屋：输入Y或N:");
    scanf("%c", &confirm);
    if(confirm == 'N')
    {
        printf("你已经放弃购买");
        PAUCE(); 
        return;
    }
    else
    {
       
       game_state->current_player->house_id[house_position] = 0;
       game_state->map[house_position].house_owner_id = 0;
       game_state->map[house_position].house_flag = 0;
       //the money of selling the house
       int sell_money = game_state->map[house_position].map_value * (game_state->map[house_position].house_level + 1) * 2; 
       game_state->current_player->money += sell_money;

       printf("恭喜你售卖成功!\n");
       PAUCE();
    }
}