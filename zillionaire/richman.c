#include "common.h"
#include "richman.h"
#include "display.h"
#include "housedeal.h"
#include "api.h"

int init_money;
GAME *game_state = NULL;
char role_name[4][16] = {"Q钱夫人", "A阿士伯", "J金贝贝", "S孙小美"};

int main() {
    bool status;
    bool if_debug = false;

    game_state = (GAME *)malloc(sizeof(GAME));

    CLEANSCREEN();
    printf("Welcome to Rich Man!\n");

    while (1) {
        char return_back;
        printf("您是否要恢复之前游戏进度：y or n  ");
        return_back = UsFgetsChar();
        //printf("\n%c\n",getchar());
        //DEBUG MODE
        // return_back = getchar();
        // getchar();
        if (return_back == 'y' || return_back == 'Y') {
            // TODO: recovery progress have saved!
            printf("recovery progress have saved!\n");
            goto Exit;
        }

        else if(return_back == 'n' || return_back == 'N') {
            // player choose to begin a new game
            break;
        }
        else if(return_back == 't' || return_back == 'T') {
            // can preset order
            if_debug = true;
            printf("\n进入debug模式\n");
            break;
        }
    }
    if (!if_debug) {
        SetInitMoney();
        
        status = ChooseRole(if_debug);
        if(!status){
            printf("exit game ..\n");
            goto Exit;
        }
    }

    InitMap();

    if (if_debug){
        // for(int i=0;i<50;i++){
        //     printf("%c",getchar());
        // }
        // printf("\n");
        printf("请输入预置指令\n");
        HandlePreset(game_state);
    }

    DisplayMap(game_state);

    GameStart();

    Dump(game_state);

    // TODO free memory;

    Exit:
    return 0;
}

void SetInitMoney()
{
    int money;
    while (1){
        printf("请设置玩家初始资金(1000~50000):");
        money = UsFgetsNum();
        if(money == 0){
            init_money = INITIAL_MONEY;
            return;
        }
        if(money >= 1000 && money <= 50000){
            init_money = money;
            return;
        }
    }
}

bool ChooseRole(int if_debug)
{
    int player_num;
    int exit_role[4] = {0,0,0,0};
    PLAYER *temp_player;
    bool ret = false;

    if (!if_debug){
        printf("请选择2~4位不重复的角色: 1.钱夫人，2.阿土伯，3.金贝贝，4.孙小美:");
        while(!(player_num = UsFgetsRole(exit_role))){
            for(int i = 0; i< 4; ++i){
                exit_role[i] = 0;
            }
            printf("输入错误，请重新输入:");
        }
    }
    else {
        char temp[5] = {};
        scanf("%s", temp);
        player_num = (int)strlen(temp);
        for (int i = 0; i < strlen(temp); i++)
            exit_role[i] = Flag2Id(temp[player_num - 1 - i]);
    }

    game_state->player_num = player_num;
    // choose roles
    for(int i = 0; i < player_num; ++ i){

        temp_player = (PLAYER *)malloc(sizeof(PLAYER));
        INIT_PLAYER_HOUSE(temp_player);
        temp_player->player_id = exit_role[i];
        memcpy(temp_player->player_name, role_name[exit_role[i]-1], 16);
        temp_player->block_num = 0;
        temp_player->robot_num = 0;
        temp_player->bomb_num = 0;
        temp_player->cur_pos = 0;
        temp_player->money = init_money;
        temp_player->point = 0;
        temp_player->sleep_time = 0;
        temp_player->no_rent_time = 0;
        temp_player->next = game_state->player;
        game_state->player = temp_player;

    }

    game_state->current_player = game_state->player;
    ret = true;

    return ret;
}

void InitMap()
{
    int i;
    for(i = 1; i < 69; ++i){
        game_state->map[i].ToolType = T_NO;
        game_state->map[i].house_level = 0;
        game_state->map[i].house_owner_id = 0;
        game_state->map[i].house_flag = NULL;
        game_state->map[i].map_value = 0;
    }

    for(i = 1; i < 29; ++i) {
        game_state->map[i].map_value = 200;
    }

    for(; i < 35; ++i) {
        game_state->map[i].map_value = 500;
    }

    for (; i < 64; ++i) {
        game_state->map[i].map_value = 300;
    }

    for(; i < 70; ++i) {
        ADD_HOUSE_FLAG(i,MINERAL);
    }

    ADD_HOUSE_FLAG(0, START);
    ADD_HOUSE_FLAG(14, HOSPITAL);
    ADD_HOUSE_FLAG(28, TOOL);
    ADD_HOUSE_FLAG(35, GIFT);
    ADD_HOUSE_FLAG(49, PRISON);
    ADD_HOUSE_FLAG(63, MAGIC);

}


void GameStart() {
    char com_buf[BUF_SIZE];
    bool status;
    bool is_use_tool = false;
    while (1) {
        HouseShow();
        DisplayMap(game_state);

        // player play this round
        if (!game_state->current_player->sleep_time) {
            scanf("%s", com_buf);

            if(STR_EQU(COMMAND_ROLL, com_buf)){
                //Judge whether it is a god of wealth
                if(game_state->current_player->no_rent_time > 0){
                    game_state->current_player->no_rent_time -= 1;
                }
                getchar(); // clean input buffer.
                cmd_roll();

                status = AbleBuyHouse(game_state->current_player->cur_pos, game_state);
                if(status){
                    cmd_buyhouse();
                }

                // When the remaining player number is one, game over.
                if(GameEnd()){
                    goto Exit;
                }

                CHECK_OUT_PLAYER(game_state);
                is_use_tool = false;
            }
            else if (STR_EQU(COMMAND_QUWRY, com_buf)){
                cmd_query();
            }
            else if (STR_EQU(COMMAND_HELP, com_buf)) {
                cmd_help();
            }

            else if (STR_EQU(COMMAND_SELLHOUSE, com_buf)) {
                cmd_sellhouse();
            }
            else if (STR_EQU(COMMAND_STEP, com_buf)) {
                //Judge whether it is a god of wealth
                if(game_state->current_player->no_rent_time > 0){
                    game_state->current_player->no_rent_time -= 1;
                }
                getchar(); // clean input buffer.
                cmd_step();

                status = AbleBuyHouse(game_state->current_player->cur_pos, game_state);
                if(status){
                    cmd_buyhouse();
                }

                // When the remaining player number is one, game over.
                if(GameEnd()){
                    goto Exit;
                }

                CHECK_OUT_PLAYER(game_state);
                is_use_tool = false;
            }
            else if (STR_EQU(COMMAND_THREE, com_buf)) {
                cmd_buythree();
            }
            //use the bomb
            else if(STR_EQU(COMMAND_BOMB, com_buf)){
               if(is_use_tool){
                   while(getchar() != '\n');
                   printf("\n 你此回合已经使用了道具\n");
                   printf("\n please press any key to continue.");
                   getchar();
               }
               else{
                   getchar();
                   is_use_tool = cmd_place_bomb();

                   printf("\n please press any key to continue.");
                   getchar();
               }

            }
            else if(STR_EQU(COMMAND_BLOCK,com_buf)){
                if(is_use_tool){
                    while(getchar() != '\n');

                    printf("\n 你此回合已经使用了道具\n");
                    printf("\n please press any key to continue.");

                    getchar();
                }
                else{
                    getchar();
                    is_use_tool = cmd_place_block();

                    printf("\n please press any key to continue.");
                    getchar();
               }
            }
            else if(STR_EQU(COMMAND_ROBOT,com_buf)){
                if(is_use_tool){
                    while(getchar() != '\n');

                    printf("\n 你此回合已经使用了道具\n");
                    printf("\n please press any key to continue.");

                    getchar();
                }
                else{
                    getchar();
                    is_use_tool = cmd_use_robot();

                    printf("\n please press any key to continue.");
                    getchar();
                }
            }
            else if (STR_EQU(COMMAND_QUIT, com_buf)) {
                cmd_quit();
                goto Exit;
            }
            else {
                printf("\n 您输入的指令有误.");
                printf("\n please press any key to continue.");
                PAUSE();
                continue;
            }
        }

        // player skip this round
        else {
            -- game_state->current_player->sleep_time;
            printf("\n您跳过此轮.");
            getchar();
            CHECK_OUT_PLAYER(game_state);
        }
    }
    Exit:
    return;

}

bool GameEnd()
{
    bool ret = false;

    if(game_state->player_num == 1){
        printf("游戏结束.\n");
        printf("恭喜%s获得胜利\n",game_state->current_player->player_name);
        ret = true;
    }

    return ret;
}

void cmd_roll()
{
    short step;
    char flag;
    bool bomb_status = false;

    GET_STEP(step);

    bomb_status = BlockedOrBombed(step, game_state);

    if(bomb_status){
        goto Exit;
    }

    GET_PLAYER_FLAG(game_state, flag);

    // player leave current map block
    DEL_HOUSE_FLAG(game_state->current_player->cur_pos, flag);
    
    // player move
    game_state->current_player->cur_pos = (game_state->current_player->cur_pos + step) % 70;

    // player arrive new map block
    ADD_HOUSE_FLAG(game_state->current_player->cur_pos, flag);

    // update map
    DisplayMap(game_state);
    printf("\n您获得的步数为：%d\n",step);

    Exit:
    return;
}

bool cmd_place_block(){
    bool ret = false;
    int target_block;

    while(1){
        target_block = UsFgetsNum();

        if(target_block >= -10 && target_block <= 10){
            break;
        }
        printf("请输入正确的目标的距离(-10~10):");
    }

    if(game_state->current_player->block_num > 0){
        target_block = target_block + game_state->current_player->cur_pos;

        if(game_state->map[target_block].house_flag != NULL){
            printf("该地块不能放置道具.");
            return ret;
        }

        if(game_state->map[target_block].ToolType == T_NO){
            game_state->current_player->block_num --;
            game_state->map[target_block].ToolType = T_BLOCK;
            ADD_HOUSE_FLAG(target_block, ROADBLOCK);

            DisplayMap(game_state);
            printf("\n 你在地图块 %d 放置了路障",target_block);
            ret = true;

            return ret;
        }
        else{
            printf("\n地图块 %d 已经放置了其他道具，不能再放置了",target_block);
            return ret;
        }
        
    }
    else{
        printf("你没有路障了，想什么呢");
        return ret;
    }

}

bool cmd_place_bomb(){
    int target_block;
    bool ret = false;

    while(1){
        target_block = UsFgetsNum();

        if(target_block >= -10 && target_block <= 10){
            break;
        }
        printf("请输入正确的目标的距离(-10~10):");
    }

    if(game_state->current_player->bomb_num > 0){
        target_block=target_block + game_state->current_player->cur_pos;

        if(game_state->map[target_block].house_flag != NULL){
            printf("该地块不能放置道具.");
            return ret;
        }

        if(game_state->map[target_block].house_flag == T_NO){
            game_state->current_player->bomb_num--;
            game_state->map[target_block].ToolType = T_BOMB;
            ADD_HOUSE_FLAG(target_block, BOMB);

            DisplayMap(game_state);
            printf("\n 你在地图块 %d 放置了炸弹",target_block);
            ret = true;

            return ret;
        }
        else{
            printf("\n地图块 %d 已经放置了其他道具，不能再放置了",target_block);
            return ret;
        }
        
    }
    else{
        printf("你没有炸弹了，想什么呢");
        return ret;
    }
}

bool cmd_use_robot()
{
    bool ret = false;
    int pos_range = game_state->current_player->cur_pos;

    if(game_state->current_player->robot_num <= 0){
        printf("你没有机器人了，想什么呢");
        goto Exit;
    }

    game_state->current_player->robot_num --;

    for(int i = 0; i <= 10; ++i){
        if(game_state->map[pos_range+i].house_flag != NULL){
            if(game_state->map[pos_range+i].house_flag->flag == BOMB){
                DEL_HOUSE_FLAG(pos_range + i, BOMB);
            }
            else if(game_state->map[pos_range +i].house_flag->flag == ROADBLOCK){
                DEL_HOUSE_FLAG(pos_range + i, ROADBLOCK);
            }
        }
    }
    DisplayMap(game_state);

    printf("\n你已经使用了机器娃娃.");
    ret = true;

    Exit:
    return  ret;
}

void cmd_step()
{
    int step;
    char flag;
    bool bomb_status;

    while((step = UsFgetsNum()) == 0){
        printf("请输入距离!");
    }

    bomb_status = BlockedOrBombed(step, game_state);

    if(bomb_status){
        goto Exit;
    }

    GET_PLAYER_FLAG(game_state, flag);

    // player leave current map block
    DEL_HOUSE_FLAG(game_state->current_player->cur_pos, flag);

    // player move
    game_state->current_player->cur_pos = (game_state->current_player->cur_pos + step) % 70;

    // player arrive new map block
    ADD_HOUSE_FLAG(game_state->current_player->cur_pos, flag);

    // update map
    DisplayMap(game_state);
    printf("\n您获得的步数为：%d\n",step);

    Exit:
    return;
}

void cmd_query()
{
    PlayQuery(game_state);
    printf("\n please press any key to continue.");
    PAUSE();
}

void cmd_help()
{
    PlayHelp(game_state);
    printf("\n please press any key to continue.");
    PAUSE();
}

void cmd_quit()
{
    printf("\n Thanks for playing.");
    printf("\n please press any key to continue.");
    PAUSE();
}

void cmd_buyhouse()
{
    BuyHouse(game_state->current_player->player_id, game_state->current_player->cur_pos, game_state);
}

void cmd_sellhouse()
{
    printf("Debug:start to sell house\n");
    getchar();
    SellHouse(game_state);
}

void cmd_buythree()
{
    printf("Debug:start to buy three house\n");
    getchar();
    BuyHouseThree(game_state);
}


void HouseShow(){
    H_FLAG *first_pos_flag = game_state->map[game_state->current_player->cur_pos].house_flag;
    H_FLAG *flag = first_pos_flag;
    char player_flag ;
    GET_PLAYER_FLAG(game_state, player_flag);
    while(flag->flag != player_flag && flag->next) {
        flag = flag->next;
    }
    char current_flag = flag->flag;
    char first_flag = first_pos_flag->flag;
    flag->flag = first_flag;
    first_pos_flag ->flag = current_flag;
}
