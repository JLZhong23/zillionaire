#include "api.h"
#include "display.h"

void PlayQuery(GAME *game_state)
{
    POS t_pos = {66, 4};

    GOTOXY(t_pos.x , t_pos.y);
    printf("Dear %s:",game_state->current_player->player_name);

    t_pos.x += 2;
    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y);
    printf("您现在所处的位置为：%d ",game_state->current_player->cur_pos);

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y);
    printf("您拥有的财产为：￥ %d", game_state->current_player->money);

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y);
    printf("您的游戏点数为： %d", game_state->current_player->point);

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y);
    printf("您拥有的炸弹数量：%d", game_state->current_player->bomb_num);

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y)
    printf("您拥有的路障数量：%d", game_state->current_player->block_num);

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y)
    printf("您拥有的机器娃娃的数量：%d", game_state->current_player->robot_num);

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y)
    printf("您名下的房产为：");
    for(int i = 0; i < 57; ++i){
        if (game_state->current_player->house_id[i]){
            printf(" %d", i);
        }
    }

    GOTOXY(6, 20);
}

void PlayHelp(GAME *game_state)
{
    POS t_pos = {66, 4};

    GOTOXY(t_pos.x , t_pos.y);
    printf("Dear %s: 欢迎来到玩家指引.",game_state->current_player->player_name);

    t_pos.x += 2;
    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y);
    printf("roll  : 掷骰子命令，行走1~6步");

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y);
    printf("query ： 显示个人资产");

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y);
    printf("quit ： 退出游戏");

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y);
    printf("help ： 查看命令帮助");

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y)
    printf("sell n：出售指定位置的房产");

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y)
    printf("block n ： 在当前位置的相对距离放置路障(-10~10)");

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y)
    printf("bomb n : 在当前位置的相对距离放置炸弹(-10~10)");

    t_pos.y ++;
    GOTOXY(t_pos.x , t_pos.y)
    printf("robot : 使用机器娃娃清楚路障和炸弹");

    GOTOXY(6, 20);
}