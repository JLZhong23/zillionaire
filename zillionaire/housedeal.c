#include "housedeal.h"
#include "display.h"

void BuyHouse(int role_id, int house_position, GAME *game_state)
{

    // pay the fees
    if(game_state->map[house_position].house_owner_id != 0 &&
       game_state->current_player->player_id != game_state->map[house_position].house_owner_id)
    {
        int sleep_time_flag;// the house owner in hospital or prison
        if(game_state->current_player->no_rent_time > 0){
            printf("该房子已经被其他玩家购买，但您财神附身，不需要支付租金\n您免租金次数剩余%d次", game_state->current_player->no_rent_time-1);
            getchar();
            return;
        }
        GET_OWNER_STATUS(game_state->map[house_position].house_owner_id,game_state->player,sleep_time_flag);
        if(sleep_time_flag){
            printf("该房子已经被其他玩家购买 ，但该玩家正处于监狱或医院之中，您不需要向他支付租金");
            getchar();
            return;
        }
        printf("该房子已经被其他玩家购买，你将被收取费用");
        PayFees(game_state);
        getchar();
        return;
    }
    
    //update the house 
    if (game_state->map[house_position].house_owner_id == game_state->current_player->player_id)
    {
        UpdateHouse(house_position, game_state);
        return;
    }

    //buy the house
    if(game_state->map[house_position].house_owner_id == 0)
    {
        char confirm;

        if(game_state->map[house_position].map_value > game_state->current_player->money)
        {
            printf("你的金钱不够购买此地块!");
            getchar();
            return;
        }

        printf("你的余额为:￥%d ", game_state->current_player->money);
        printf("是否花费￥%d购买此地块(Y/N)：", game_state->map[house_position].map_value);

        while(1){
            confirm = UsFgetsChar();
            if(confirm == 'N' || confirm == 'n')
            {
                printf("你已经放弃购买\n");
                getchar();
                return;
            }

            else if(confirm == 'Y' || confirm == 'y')
            {
                game_state->current_player->money -= game_state->map[house_position].map_value;
                game_state->map[house_position].house_owner_id = role_id;

                // 玩家中要添加该空地game_state->current_player->house[]
                game_state->current_player->house_id[house_position]
                        =  &(game_state->map[house_position]);
                printf("恭喜你购买成功! ");
                printf("你当前余额为:￥%d\n", game_state->current_player->money);
                getchar();
                return;
            }

            else
            {
                printf("输入错误，请选择：");
            }
        }
    }
    
}

// Update our house 
void UpdateHouse( int house_position, GAME *game_state)
{

    switch (game_state->map[house_position].house_level)
    {
        case 0:
            HouseUpdateOneLeve(house_position, "空地", "茅房", game_state);
            getchar();
            break;

        case 1:
            HouseUpdateOneLeve(house_position, "茅房", "洋房", game_state);
            getchar();
            break;

        case 2:
            HouseUpdateOneLeve(house_position, "洋房", "摩天楼", game_state);
            getchar();
            break;    

         case 3:
            printf("你的房子是摩天大楼，你不需要再升级");
            getchar();
            break;               

         default:
            printf("Error: house_level is out of 0~3!");
            getchar();
            break;
    }

}

void HouseUpdateOneLeve(int house_position, char *primary_level, char *update_level, GAME *game_state)
{
    char choose_bool; //role choose the level of house to update

    if(game_state->map[house_position].map_value > game_state->current_player->money) {
        printf("你的金钱不够升级此地块！\n");
        getchar();
        return;
    }

    printf("你的房子是%s，你要升级的等级:%s\n 是否选择升级(Y/N):", primary_level, update_level);

    while(1){
        choose_bool = UsFgetsChar();
        if(choose_bool == 'Y' || choose_bool == 'y') {

            game_state->current_player->money  -= game_state->map[house_position].map_value;
            game_state->map[house_position].house_level += 1;
            printf("房屋成功升级为%s", update_level);
            return;
        }
        else if(choose_bool == 'N' || choose_bool == 'n')
        {
            printf("你已放弃升级!");
            return;
        }

        printf("输入错误,请选择：");
    }

}


void SellHouse(GAME *game_state)
{
    printf("你拥有的房产如下：\n");
    int number = 0;
    for(int i = 0; i < 70; i++)
    {
        if(game_state->map[i].house_owner_id == game_state->current_player->player_id)
        {
            PrintHouseInfo(i, game_state);
            number += 1;
        }
    }

    printf("你的房产总数为：%d\n", number);
    if (number != 0)
    {
        int house_position;
        printf("请选择你要卖的房子的位置:");
        house_position = UsFgetsNum();

        int id = game_state->current_player->player_id;

        if(game_state->map[house_position].house_owner_id != id)
        {
            printf("该房子还不属于你");
            getchar();
            return;
        }

        printf("是否确认出售房屋：\n输入Y或N:");
        char confirm = UsFgetsChar();

        if(confirm == 'N' || confirm == 'n')
        {
            printf("你已经放弃出售");
            getchar();
            return;
        }
        else if (confirm == 'Y' || confirm == 'y')
        {
            game_state->current_player->house_id[house_position] = 0;
            game_state->map[house_position].house_owner_id = 0;
            // game_state->map[house_position].house_flag = 0;
            //the money of selling the house
            int sell_money = game_state->map[house_position].map_value * (game_state->map[house_position].house_level + 1) * 2; 
            game_state->current_player->money += sell_money;

            printf("恭喜你售卖成功!\n");
            getchar();
        }
        else
        {
            printf("你的命令输入错误");
            getchar();
        }
    }
    
}

void PayFees(GAME *game_state)
{
    int house_value = game_state->map[game_state->current_player->cur_pos].map_value;

    int house_level = game_state->map[game_state->current_player->cur_pos].house_level;
    int fees = (house_level + 1) * house_value * 0.5;
    printf("￥ %d\n", fees);

    //current player subtract the fees
    game_state->current_player->money -= fees;
    PLAYER *map_player = Map_Player(game_state->map[game_state->current_player->cur_pos].house_owner_id, game_state);

    //map owner player add the fees
    map_player->money += fees;

    //check bankrupt
    if( game_state->current_player->money < 0)
    {
        printf("非常遗憾，你已破产!\n");
        DeleteCurrentPlayer(game_state);
    }
}

//get the player of map
PLAYER * Map_Player(int plyr_id, GAME *game_state)
{
    PLAYER *map_player;

    map_player = game_state->player;
    while(map_player)
    {
        if (map_player->player_id == plyr_id) {
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

    while(temp_player){
        if(temp_player->player_id == current_player_id){
            if(!pre_player) { //when the first player in bankrupt is current player.
                game_state->player = temp_player->next;
                game_state->current_player = game_state->player;
            }
            else if(!temp_player->next){
                pre_player->next = temp_player->next;
                game_state->current_player = game_state->player;
            }
            else {
                pre_player->next = temp_player->next;
                game_state->current_player = pre_player->next;
            }
            game_state->player_num --;
            char ply_flag;
            for(int i = 0; i < 64; ++ i){
                if(temp_player->house_id[i]){
                    GET_PLAYER_FLAG(game_state,ply_flag);
                    DEL_HOUSE_FLAG(i,ply_flag);
                    game_state->map[i].house_level = 0;
                    game_state->map[i].house_owner_id = 0;
                }
            }
            free(temp_player);
            break;
        }
        pre_player = temp_player;
        temp_player = temp_player->next;
    }
} 

//debug info
void PrintHouseInfo(int house_position, GAME *game_state)
{
    printf("房子的位置：%d\n", house_position);
    printf("房子的等级：%d\n", game_state->map[house_position].house_level);
    printf("房子的主人id：%d\n", game_state->map[house_position].house_owner_id);
    printf("房子的价格：%d\n", game_state->map[house_position].map_value);

}

void BuyHouseThree(GAME *game_state)
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

bool AbleBuyHouse(int house_id, GAME *game)
{
    bool ret;
    if(house_id == 0){
        // start
        ret = false;
    }
    else if (house_id == 14){
        // hospital
        ret = false;
    }
    else if(house_id == 28) {
        // tool
        PlayerInToolHouse(game);
        ret = false;
    }
    else if(house_id == 35){
        // gift house
        PlayerInGiftHouse(game);
        ret = false;
    }
    else if(house_id == 49) {
        // prison
        PlayerInPrison(game);
        ret = false;
    }
    else if(house_id == 63) {
        // magic
        ret = false;
    }
    else if(house_id > 63 && house_id <70) {
        // mineral
        PlayerInMineral(house_id, game);
        ret = false;
    }
    else {
        ret = true;
    }

    return ret;
}

void PlayerInMineral(int mineral_id, GAME *game)
{
    switch (mineral_id){
        case 69:
            game->current_player->point += 20;
            printf("恭喜获得 20 点数.");
            getchar();
            break;
        case 67:
            game->current_player->point += 100;
            printf("恭喜获得 100 点数.");
            getchar();
            break;
        case 66:
            game->current_player->point += 40;
            printf("恭喜获得 40 点数.");
            getchar();
            break;
        case 64:
            game->current_player->point += 60;
            printf("恭喜获得 60 点数.");
            getchar();
            break;
        default:
            // when mineral id equal 68 and 65
            game->current_player->point += 80;
            printf("恭喜获得 80 点数.");
            getchar();
            break;
    }
}

void PlayerInGiftHouse(GAME *game)
{
    int choose_gift;
    printf("欢迎进入礼品屋, 请选择一件您喜欢的礼品\n输入 1————获得2000元奖金\n输入 2————获得200点数卡\n输入 3————财神附身,路过其他玩家地产,均可免费, 5轮内有效\n输入其他自动退出\n请输入");

    choose_gift = UsFgetsNum();
    if(choose_gift == 1){
        game->current_player->money += G_MONEY;
        printf("您已获得2000奖金！祝您游戏顺利");
        getchar();
        return;
    }
    else if(choose_gift == 2){
        game->current_player->point += G_POINT;
        printf("您已获得200点数！祝您游戏顺利");
        getchar();
        return;
    }
    else if(choose_gift == 3){
        game->current_player->no_rent_time = G_NO_RENT_TIME;
        printf("您已财神附体！祝您游戏顺利");
        getchar();
        return;
    }
    printf("不合理输入,将退出礼品屋.");
    getchar();

}

void PlayerInPrison(GAME *game){
    printf("您走到了监狱，将被轮空两次");
    game->current_player->sleep_time = SLEEP_TIME_PRISON;
    getchar();
    return;
}

void PlayerInToolHouse(GAME *game)
{
    char choose_tool;

    if(game->current_player->point <30){
        printf("您的点数不足购买道具.\n");
        getchar();
        goto Exit;
    }

    if(game->current_player->robot_num + game->current_player->block_num + game->current_player->bomb_num >= 10){
        printf("您的道具已达上限，无法购买新的道具.\n");
        getchar();
        goto Exit;
    }

    printf("欢迎进入道具屋, 请选择一件您需要的道具\n 1: 路障，价值￥50\n 2: 机器娃娃，价值￥30\n 3: 炸弹，价值￥50\n请输入要购买的道具序号(F退出):");
    while(1){
        choose_tool = UsFgetsChar();

        if(choose_tool == 'F' || choose_tool == 'f'){
            printf("您已放弃购买.");
            getchar();
            goto Exit;
        }

        if(choose_tool == '1'){
            if(game->current_player->point < 50){
                printf("点数不足，无法购买，请重新选择：");
                continue;
            }
            game->current_player->point -= 50;
            game->current_player->block_num += 1;
            printf("购买路障成功.");
            getchar();
            goto Exit;
        }
        if(choose_tool == '2'){
            game->current_player->point -= 30;
            game->current_player->robot_num += 1;
            printf("购买机器娃娃成功.");
            getchar();
            goto Exit;
        }
        if(choose_tool == '3'){
            if(game->current_player->point < 50){
                printf("点数不足，无法购买，请重新选择：");
                continue;
            }
            game->current_player->point -= 50;
            game->current_player->bomb_num += 1;
            printf("购买炸弹成功.");
            getchar();
            goto Exit;
        }
        printf("输入错误,请重新输入:");
    }

Exit:
    return;
}

//determin whether blocked or bombed or nothing happend
bool BlockedOrBombed(int step, GAME *game_state) {
    for (int i = 0; i <= step; i ++) {
        int pos = (game_state->current_player->cur_pos + i) % MAP_SIZE;
        char flag;
        if (game_state->map[pos].ToolType == T_BOMB) {     // bomb
            GET_PLAYER_FLAG(game_state, flag);
            DEL_HOUSE_FLAG(game_state->current_player->cur_pos, flag);
            DEL_HOUSE_FLAG(pos, BOMB);

            game_state->map[pos].ToolType = T_NO;
            game_state->current_player->cur_pos = HOSPITAL_POS;
            ADD_HOUSE_FLAG(HOSPITAL_POS, flag);
            game_state->current_player->sleep_time = SLEEP_TIME;

            printf("您遇到了炸弹,将被送往医院.\n");
            getchar();
            DisplayMap(game_state);
            return true;
        }
        if (game_state->map[pos].ToolType == T_BLOCK) {
            GET_PLAYER_FLAG(game_state, flag);
            DEL_HOUSE_FLAG(game_state->current_player->cur_pos, flag);
            DEL_HOUSE_FLAG(pos, ROADBLOCK);

            game_state->map[pos].ToolType = T_NO;
            game_state->current_player->cur_pos = pos;
            ADD_HOUSE_FLAG(pos, flag);

            printf("您遇到了路障，被拦了下来.\n");
            getchar();
            DisplayMap(game_state);

            return true;
        }
    }
    return false;
}
