#include "housedeal.h"

void BuyHouse(int role_id, int house_position, GAME *game_state)
{

    if(role_id>4 || role_id < 1)
    {
        printf("Error: role_id is out of 1~4!");
        PAUSE();
        return;
    }

    // pay the fees
    if(game_state->map[house_position].house_owner_id != 0 &&
       game_state->current_player->player_id != game_state->map[house_position].house_owner_id)
    {
        printf("该房子已经被其他玩家，你将被收取费用");
        PayFees(game_state);
        PAUCE();
        return;
    }
    
    //update the house 
    if (game_state->map[house_position].house_owner_id == game_state->current_player->player_id)
    {

        UpdateHouse(game_state->current_player->player_id, house_position, game_state);

    }


    //buy the house
    if(game_state->map[house_position].house_owner_id == 0)
    {

        char confirm;
        printf("你的余额为:%d\n", game_state->current_player->money);
        PrintHouseInfo(game_state);
        printf("是否确认购买：\n输入Y或N:");
        scanf("%c", &confirm);
        
        if(confirm == 'N' || confirm == 'n')
        {
            printf("你已经放弃购买");
            PAUCE();    
            return;
        }
        else if(confirm == 'Y' || confirm == 'y')
        {
            if(game_state->map[house_position].map_value > game_state->current_player->money)
            {
                printf("你的金钱不够购买!");
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
                printf("你的余额为:%d", game_state->current_player->money);
                printf("\n");
                PAUCE();
            }
        }
        else
        {
            printf("你的命令输入错误");
            PAUCE();
        }
    }
    
}

// Update our house 
void UpdateHouse(int role_id, int house_position, GAME *game_state)
{
    if(role_id>4 || role_id < 1)
    {
        printf("Error: role_id is out of 1~4!");
        PAUSE();
        return;
    }  


    
    switch (game_state->map[house_position].house_level)
    {
        case 0:
            HouseUpdateOneLeve(house_position, "空地", "茅房", game_state);
            PAUSE();
            break;

        case 1:
            HouseUpdateOneLeve(house_position, "茅房", "洋房", game_state);
            PAUSE();
            break;

        case 2:
            HouseUpdateOneLeve(house_position, "洋房", "摩天楼", game_state);
            PAUSE();
            break;    

         case 3:
            printf("你的房子是摩天大楼，你不需要再升级");
            PAUSE();
            break;               

         default:
            printf("Error: house_level is out of 0~3!");
            PAUSE();
            break;
    }

}

void HouseUpdateOneLeve(int house_position, char *primary_level, char *update_level, GAME *game_state)
{
    char choose_bool; //role choose the level of house to update
    printf("你的房子是%s，你要升级的等级:\n%s\n是否选择升级:\n1.Y\n2.N\n", primary_level, update_level);
    getchar();
    scanf("%c", &choose_bool);
    if(choose_bool == 'Y' || choose_bool == 'y')
    {
        if(game_state->map[house_position].map_value > game_state->current_player->money)
        {
            printf("你的金钱不够升级！");
            return;
        }
        else
        {
            game_state->current_player->money = game_state->current_player->money - game_state->map[house_position].map_value;
            game_state->map[house_position].house_level += 1;
            printf("房屋成功升级为%s", update_level);
            return;
        }
    }else if(choose_bool == 'N' || choose_bool == 'n')
    {
        printf("你已放弃升级!");
        return;
    }
    else
    {
        printf("你输入的命令有误");
        PAUCE();
    }
}


void SellHouse(int house_position, GAME *game_state)
{
    if(game_state->map[house_position].house_owner_id != game_state->current_player->player_id)
    {
        printf("该房子还不属于你");
        PAUSE();
        return;
    }

    char confirm;
    printf("是否确认出售房屋：输入Y或N:");

    scanf("%c", &confirm);
    if(confirm == 'N' || confirm == 'n')
    {
        printf("你已经放弃购买");
        PAUSE();
        return;
    }
    else if (confirm == 'Y' || confirm == 'y')
    {
       
       game_state->current_player->house_id[house_position] = 0;
       game_state->map[house_position].house_owner_id = 0;
       game_state->map[house_position].house_flag = 0;
       //the money of selling the house
       int sell_money = game_state->map[house_position].map_value * (game_state->map[house_position].house_level + 1) * 2; 
       game_state->current_player->money += sell_money;

       printf("恭喜你售卖成功!\n");
       PAUSE();
    }
    else
    {
        printf("你的命令输入错误");
        PAUCE();
    }
}

void PayFees(GAME *game_state)
{
    int house_value = game_state->map[game_state->current_player->cur_pos].map_value;

    int house_level = game_state->map[game_state->current_player->cur_pos].house_level;
    int fees = (house_level + 1) * house_value * 0.5;
    printf("%d\n", fees);
    //current player add the fees
    game_state->current_player->money -= fees;
    PLAYER *map_player = Map_Player(game_state->map[game_state->current_player->cur_pos].house_owner_id, game_state);
    //map player subtract the fees
    map_player->money += fees;
    printf("缴费成功\n");

    //check bankrupt
    if( game_state->current_player->money < 0)
    {
        printf("非常遗憾，你已破产!\n");
        DeleteCurrentPlayer(game_state);
        PAUCE();
    }
}

//get the player of map
PLAYER * Map_Player(int plyr_id, GAME *game_state)
{

    PLAYER *map_player;
    map_player = game_state->player;
    while(map_player)
    {
        if (map_player->player_id == plyr_id)
        {
            return map_player;
        }
        map_player = map_player->next;
    }
    return NULL;
}

void DeleteCurrentPlayer(GAME *game_state)
{
    int current_player_id = game_state->current_player->player_id;
    PLAYER *pre_player = NULL;
    PLAYER *temp_player = game_state->player;
    
    //when the first player bankrupt
    if (temp_player->player_id == current_player_id)
    {
        temp_player = game_state->current_player->next;
        free(game_state->current_player);
        game_state->current_player = temp_player;
    }
    else
    {
        while(1)
        {
            pre_player = temp_player;
            temp_player = temp_player->next;
            if (temp_player->player_id == current_player_id)
            {
                pre_player ->next = temp_player->next;
                free(game_state->current_player);
                game_state->current_player = temp_player;
                break;
            }
            else{
                pre_player = temp_player;
                temp_player = temp_player->next;
            }
        }
    }
} 

//debug info
void PrintHouseInfo(GAME *game_state)
{
    int house_position = game_state->current_player->cur_pos;

    printf("房子的位置：%d\n", house_position);
    printf("房子的类型：%c\n", game_state->map[house_position].house_flag->flag);
    printf("房子的等级：%d\n", game_state->map[house_position].house_level);
    printf("房子的主人id：%d\n", game_state->map[house_position].house_owner_id);
    printf("房子的价格：%d\n", game_state->map[house_position].map_value);

}