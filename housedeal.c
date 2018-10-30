#include "housedeal.h"
#include "common.h"
#include "richman.h"

void BuyHouse(int role_id, int house_value)
{
    if(role_id>4 | role_id < 1)
    {
        printf("Error: role_id is out of 1~4!");
        return;
    }
    
    if(game_state->map[house_value].house_owner_id =! role_id)
    {
        printf("该房子已经被其他玩家购买");
        return;
    }

    char confirm;
    printf("是否确认购买：输入Y或N;");
    scanf("%s",confirm);
    if(confirm == "N")
    {
        printf("你已经放弃购买");
        return;
    }
    else
    {
        game_state->current_player->money = game_state->current_player->money - game_state->map[house_value].map_value;
        game_state->map[house_value].house_owner_id = role_id;
        // 玩家中要添加该空地game_state->current_player->house[] 
        printf("恭喜你购买成功");
    }
}

// Update our house 
void UpdateHouse(int role_id, int house_value)
{
    if(role_id>4 | role_id < 1)
    {
        printf("Error: role_id is out of 1~4!");
        return;
    }
    
    if(game_state->map[house_value].house_owner_id =! role_id)
    {
        printf("该房子已经被其他玩家购买");
        return;
    }

    
    switch (game_state->map[house_value].house_level)
    {
        case 0:
            HouseUpdateOneLeve(house_value, "空地", "茅房");
            break;

        case 1:
            HouseUpdateOneLeve(house_value, "茅房", "洋房");
            break;

        case 2:
            HouseUpdateOneLeve(house_value, "洋房", "摩天楼");
            break;    

         case 3:
            printf("你的房子是摩天大楼，你不需要再升级");
            break;               

         default:
            printf("Error: house_level is out of 0~3!");
            break;
    }

}

void HouseUpdateOneLeve(int house_value, char primary_level, char update_level)
{
    char choose_bool; //role choose the level of house to update
    printf("你的房子是%s，你要升级的等级:\n%s；\n是否选择升级:\n1.Y;\n2.N", primary_level, update_level);
    scanf("%s", &choose_bool);
    if(choose_bool == "Y")
    {
        if(game_state->map[house_value].map_value > game_state->current_player->money)
        {
            printf("你的金钱不够升级！");
            return;
        }
        else
        {
            game_state->current_player->money = game_state->current_player->money - game_state->map[house_value].map_value;
            game_state->map->house_level = 1;
            printf("房屋成功升级为%s", update_level);
            return;
        }
    }else
    {
        printf("你已放弃升级");
        return;
    }
}

