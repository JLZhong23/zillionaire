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
    for(int i = 0; i < 64; ++i){
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


int UsFgetsNum()
{
    int ret;
    char c_buf[BUF_SIZE] = {0};

    fgets(c_buf, BUF_SIZE, stdin);
    setbuf(stdin, NULL);

    for (int i = 0; i < BUF_SIZE; ++i) {
        if (c_buf[i] == '\r' ||
            c_buf[i] == '\n' ||
            c_buf[i] == ' '  ||
            c_buf[i] == '\t' ||
            c_buf[i] == '\v' ||
            c_buf[i] == '\f') {

            c_buf[i] = '\0';
            break;
        }
    }

    ret = (int)strtol(c_buf, '\0', 10);

    return ret;
}

char UsFgetsChar()
{
    char ret;
    char c_buf[BUF_SIZE] = {0};

    fgets(c_buf, BUF_SIZE, stdin);
    //setbuf(stdin, NULL);

    if(strlen(c_buf) > 2){
        ret = 'q';
    }
    else{
        ret = c_buf[0];
    }

    return ret;
}

int UsFgetsRole(int *exist_role)
{
    int role_num = 0;
    char c_buf[BUF_SIZE] = {0};
    int ipt_;
    int temp_ply_num;
    bool status;

    fgets(c_buf, BUF_SIZE, stdin);
    setbuf(stdin, NULL);
    for (int i = 0; i < BUF_SIZE; ++i) {
        if (c_buf[i] == '\r' ||
            c_buf[i] == '\n' ||
            c_buf[i] == ' '  ||
            c_buf[i] == '\t' ||
            c_buf[i] == '\v' ||
            c_buf[i] == '\f') {

            c_buf[i] = '\0';
            break;
        }
    }

    // Input must be all Numbers
    for(int i = 0; i < strlen(c_buf); ++i){
        if(c_buf[i] < '0' || c_buf[i] > '9'){
            goto Exit;
        }
    }

    ipt_ = strtol(c_buf,'\0',10);
    if(ipt_ == 0){
        goto Exit;
    }

    int i = 0;
    while(ipt_ > 0){
        temp_ply_num = ipt_ % 10;
        if(temp_ply_num > 4 || temp_ply_num < 1){
            goto Exit;
        }
        ROLE_EXIST(temp_ply_num, exist_role, status);
        if(status){
            goto Exit;
        }
        exist_role[i] = temp_ply_num;
        ipt_ /= 10;
        ++ i;
    }

    if(i < 2 || i > 4){
        role_num = 0;
    }
    else{
        role_num = i;
    }

    Exit:
    return role_num;
}