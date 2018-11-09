#include "housedeal.h"
#include "display.h"
#include "richman.h"

void BuyHouse(int role_id, int house_position, GAME *game_state)
{

    // pay the fees
    if(game_state->map[house_position].house_owner_id != 0 &&
       game_state->current_player->player_id != game_state->map[house_position].house_owner_id)
    {
        int sleep_time_flag = 0;// the house owner in hospital or prison
        if(game_state->current_player->no_rent_time > 0){
            printf("该房子已经被%s购买\n但%s财神附身免租金\n",role_name[game_state->map[house_position].house_owner_id], game_state->current_player->player_name);
            printf("免租金次数剩余%d次\n",game_state->current_player->no_rent_time-1);
            return;
        }
        GET_OWNER_STATUS(game_state->map[house_position].house_owner_id,game_state->player,sleep_time_flag);
        if(sleep_time_flag){
            printf("该房子已经被%s购买\n但该玩家被使用了魔法\n不需要支付租金\n",role_name[game_state->map[house_position].house_owner_id - 1]);
            return;
        }
        printf("该房子已经被%s购买\n%s将被收取费用",role_name[game_state->map[house_position].house_owner_id - 1], game_state->current_player->player_name);
        PayFees(game_state);
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
            printf("%s的金钱不够购买此地块!\n",game_state->current_player->player_name);
            return;
        }

        printf("亲爱的%s您处于一块空地\n", game_state->current_player->player_name);
        printf("是否花费￥%d购买此地块(Y/N)：", game_state->map[house_position].map_value);

        while(1){
            confirm = UsFgetsChar();
            if(confirm == 'N' || confirm == 'n')
            {
                printf("%s已经放弃购买\n", game_state->current_player->player_name);
                return;
            }

            if(confirm == 'Y' || confirm == 'y')
            {
                game_state->current_player->money -= game_state->map[house_position].map_value;
                game_state->map[house_position].house_owner_id = role_id;

                // 玩家中要添加该空地game_state->current_player->house[]
                game_state->current_player->house_id[house_position]
                        =  &(game_state->map[house_position]);
                printf("恭喜%s购买空地成功! \n",game_state->current_player->player_name);
                return;
            }
            printf("输入错误，请选择：");
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
            break;

        case 1:
            HouseUpdateOneLeve(house_position, "茅房", "洋房", game_state);
            break;

        case 2:
            HouseUpdateOneLeve(house_position, "洋房", "摩天楼", game_state);
            break;

         case 3:
            printf("你的房子是摩天大楼，你不需要再升级");
            break;

         default:
            printf("Error: house_level is out of 0~3!");
            break;
    }

}

void HouseUpdateOneLeve(int house_position, char *primary_level, char *update_level, GAME *game_state)
{
    char choose_bool; //role choose the level of house to update

    if(game_state->map[house_position].map_value > game_state->current_player->money) {
        printf("亲爱的%s\n你的金钱不够升级此地块！\n",game_state->current_player->player_name);
        return;
    }

    printf("亲爱的%s,欢迎回家!\n",game_state->current_player->player_name);
    printf("你的房子是%s，下一等级:%s\n是否选择升级(Y/N):", primary_level, update_level);

    while(1){
        choose_bool = UsFgetsChar();
        if(choose_bool == 'Y' || choose_bool == 'y') {

            game_state->current_player->money  -= game_state->map[house_position].map_value;
            game_state->map[house_position].house_level += 1;
            printf("房屋成功升级为%s", update_level);
            return;
        }
        if(choose_bool == 'N' || choose_bool == 'n')
        {
            printf("你已放弃升级!");
            return;
        }

        printf("输入错误,请选择：");
    }

}


bool SellHouse(GAME *game_state, int house_pos)
{
    bool ret = false;
    if(game_state->map[house_pos].house_owner_id != game_state->current_player->player_id){
        printf("\n%s不好意思，地块%d不是你的房产\n",game_state->current_player->player_name, house_pos);
        goto Exit;
    }

    int sell_money = game_state->map[house_pos].map_value * (game_state->map[house_pos].house_level + 1) * 2;

    printf("亲爱的%s\n",game_state->current_player->player_name);
    printf("  这块地购入价格%d\n",game_state->map[house_pos].map_value);
    printf("  现在出手可以卖￥%d\n",sell_money);
    printf("  是否确认出售房屋(y/n):");
    char confirm;
    while ((confirm = UsFgetsChar())){
        if(confirm == 'N' || confirm == 'n')
        {
            printf("你已经放弃出售");
            goto Exit;
        }
        else if (confirm == 'Y' || confirm == 'y')
        {
            game_state->current_player->house_id[house_pos] = NULL;
            game_state->map[house_pos].house_owner_id = 0;
            game_state->map[house_pos].house_level = 0;
            //the money of selling the house
            game_state->current_player->money += sell_money;

            printf("恭喜%s售卖成功!\n",game_state->current_player->player_name);
            ret = true;
            goto Exit;
        }
        printf("你的命令输入错误:");
    }

    Exit:
    return ret;
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
        printf("\n非常遗憾，%s已破产!\n",game_state->current_player->player_name);
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
    PLAYER *temp_player = game_state->player, *cur_ply;

    while(temp_player){
        if(temp_player->player_id == current_player_id){
            if(!pre_player) { //when the first player in bankrupt is current player.
                game_state->player = temp_player->next;
                cur_ply = game_state->player;
                while (cur_ply->next){
                    cur_ply = cur_ply->next;
                }
                game_state->current_player = cur_ply;
            }
//            else if(!temp_player->next){
//                pre_player->next = temp_player->next;
//                game_state->current_player = pre_player;
//            }
            else {
                pre_player->next = temp_player->next;
                game_state->current_player = pre_player;
            }
            game_state->player_num --;
            char ply_flag = temp_player->player_name[0];
            for(int i = 0; i < 64; ++ i){
                if(temp_player->house_id[i]){
                    //GET_PLAYER_FLAG(game_state,ply_flag);
                    DEL_HOUSE_FLAG(i,ply_flag);
                    game_state->map[i].house_level = 0;
                    game_state->map[i].house_owner_id = 0;
                }
            }
            free(temp_player);
            return;
        }
        pre_player = temp_player;
        temp_player = temp_player->next;
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
        CLEAN_TIPS();
        PlayerInToolHouse(game);
        ret = false;
    }
    else if(house_id == 35){
        // gift house
        CLEAN_TIPS();
        PlayerInGiftHouse(game);
        ret = false;
    }
    else if(house_id == 49) {
        // prison
        CLEAN_TIPS();
        //PlayerInPrison(game);
        ret = false;
    }
    else if(house_id == 63) {
        // magic
        PlayerInMagicHouse(game);
        ret = false;
    }
    else if(house_id > 63 && house_id <70) {
        // mineral
        CLEAN_TIPS();
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
            printf("恭喜%s获得 20 点数.",game->current_player->player_name);
            break;
        case 67:
            game->current_player->point += 100;
            printf("恭喜%s获得 100 点数.",game->current_player->player_name);
            break;
        case 66:
            game->current_player->point += 40;
            printf("恭喜%s获得 40 点数.",game->current_player->player_name);
            break;
        case 64:
            game->current_player->point += 60;
            printf("恭喜%s获得 60 点数.",game->current_player->player_name);
            break;
        default:
            // when mineral id equal 68 and 65
            game->current_player->point += 80;
            printf("恭喜%s获得 80 点数.",game->current_player->player_name);
            break;
    }
}

void PlayerInGiftHouse(GAME *game)
{
    int choose_gift;
    printf("欢迎%s光临礼品屋, 请选择一件您喜欢的礼品\n1.2000元奖金\n2.200点数卡\n3.财神附身\n输入其他自动退出\n请输入:",game->current_player->player_name);

    choose_gift = UsFgetsNum();
    if(choose_gift == 1){
        game->current_player->money += G_MONEY;
        printf("%s已获得2000奖金！", game->current_player->player_name);
    }
    else if(choose_gift == 2){
        game->current_player->point += G_POINT;
        printf("%s已获得200点数！", game->current_player->player_name);
    }
    else if(choose_gift == 3){
        game->current_player->no_rent_time = G_NO_RENT_TIME;
        printf("%s已财神附体！", game->current_player->player_name);
    }
    printf("%s退出了礼品屋.", game->current_player->player_name);
    return;
}

void PlayerInPrison(GAME *game){
    printf(" %s被抓紧了监狱，将被轮空两次!",game->current_player->player_name);
    game->current_player->sleep_time = SLEEP_TIME_PRISON;
    return;
}

void PlayerInToolHouse(GAME *game)
{
    char choose_tool;

    if(game->current_player->point <30){
        printf("%s的点数不足购买道具.\n", game->current_player->player_name);
        goto Exit;
    }

    if(game->current_player->robot_num + game->current_player->block_num + game->current_player->bomb_num >= 10){
        printf("%s的道具已达上限，无法购买新的道具.\n", game->current_player->player_name);
        goto Exit;
    }

    //printf("欢迎%s光临道具屋, 请选择一件道具\n 1: 路障，价值￥50\n 2: 机器娃娃，价值￥30\n 3: 炸弹，价值￥50\n请输入要购买的道具序号(F退出):", game->current_player->player_name);
    printf("欢迎%s光临道具屋, 请选择一件道具\n 1: 路障，价值￥50\n 2: 机器娃娃，价值￥30\n 请输入要购买的道具序号(F退出):", game->current_player->player_name);

    while(1){
        choose_tool = UsFgetsChar();

        if(choose_tool == 'F' || choose_tool == 'f'){
            printf("%s已放弃购买道具.", game->current_player->player_name);
            goto Exit;
        }

        if(choose_tool == '1'){
            if(game->current_player->point < 50){
                printf("%s的点数不足，无法购买路障，请重新选择：", game->current_player->player_name);
                continue;
            }
            game->current_player->point -= 50;
            game->current_player->block_num += 1;
            printf("%s购买路障成功.", game->current_player->player_name);
            goto Exit;
        }
        if(choose_tool == '2'){
            game->current_player->point -= 30;
            game->current_player->robot_num += 1;
            printf("%s购买机器娃娃成功.", game->current_player->player_name);
            goto Exit;
        }
//        if(choose_tool == '3'){
//            if(game->current_player->point < 50){
//                printf("%s的点数不足，无法购买炸弹，请重新选择：", game->current_player->player_name);
//                continue;
//            }
//            game->current_player->point -= 50;
//            game->current_player->bomb_num += 1;
//            printf("%s购买炸弹成功.", game->current_player->player_name);
//            goto Exit;
//        }
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
//        if (game_state->map[pos].ToolType == T_BOMB) {     // bomb
//            GET_PLAYER_FLAG(game_state, flag);
//            DEL_HOUSE_FLAG(game_state->current_player->cur_pos, flag);
//            DEL_HOUSE_FLAG(pos, BOMB);
//
//            game_state->map[pos].ToolType = T_NO;
//            game_state->current_player->cur_pos = HOSPITAL_POS;
//            ADD_HOUSE_FLAG(HOSPITAL_POS, flag);
//            game_state->current_player->sleep_time = SLEEP_TIME;
//
//            DisplayMap(game_state);
//            CLEAN_TIPS();
//            printf("\n%s遇到了炸弹,将被送往医院.\n",game_state->current_player->player_name);
//
//            return true;
//        }
        if (game_state->map[pos].ToolType == T_BLOCK) {
            GET_PLAYER_FLAG(game_state, flag);
            DEL_HOUSE_FLAG(game_state->current_player->cur_pos, flag);
            DEL_HOUSE_FLAG(pos, ROADBLOCK);

            game_state->map[pos].ToolType = T_NO;
            game_state->current_player->cur_pos = pos;
            ADD_HOUSE_FLAG(pos, flag);

            DisplayMap(game_state);
            CLEAN_TIPS();
            printf("\n%s遇到了路障，被拦了下来.\n",game_state->current_player->player_name);

            return true;
        }
    }
    return false;
}
void PlayerInMagicHouse (GAME *game){
    int against_player;
    PLAYER *tmp_ply = game->player;
    printf("欢迎进入魔法屋！您可以陷害以为玩家使其轮空两次\n现在正在游戏的玩家有\n");
    while (tmp_ply){
        printf("%d %s  ",tmp_ply->player_id,tmp_ply->player_name);
        tmp_ply = tmp_ply->next;
    }
    printf("\n请输入您想陷害玩家的编号,输入0代表放弃\n");
    against_player = UsFgetsNum();
    tmp_ply = game->player;
    while (tmp_ply){
        if(tmp_ply->player_id == against_player){
            tmp_ply->sleep_time += MAGIC_TIME;
            printf("陷害成功,%s轮空次数加二",tmp_ply->player_name);
        }
        tmp_ply = tmp_ply->next;
    }
    if(against_player == 0){
        printf("您放弃了此次机会！");
    }
    printf("\n%s退出了魔法屋.", game->current_player->player_name);
}
