#include "api.h"

void Dump(GAME *game_state){
    PLAYER * _player = game_state->player;
    FILE * fp = NULL;
    fp = fopen("../test_file/temp/output", "w");
    if(!fp){
        printf("无法打开该文件");
        return;
    }
    // user AQS
    char name[5] = {};
    for (int i = 0; i < game_state->player_num; i++){
        name[i] = _player->player_name[0];
        _player = _player->next;
    }
    fprintf(fp, "user %s\n", name);
    // map 0 A 1
    char _owner_flag = SPACE;
    for (int i = 0; i < 70; i++){
        if (game_state->map[i].house_owner_id != 0){
            GET_OWNER_COLOR(game_state->map[i].house_owner_id, game_state->player, _owner_flag);
            fprintf(fp, "map %d %c %d\n", i, _owner_flag, game_state->map[i].house_level);
        }
    }
    // fund A 1000
    _player = game_state->player;
    for (int i = 0; i < game_state->player_num; i++){
        fprintf(fp, "fund %c %d\n", _player->player_name[0], _player->money);
        _player = _player->next;
    }
    // credit A 30
    _player = game_state->player;
    for (int i = 0; i < game_state->player_num; i++){
        if (_player->point != 0)
            fprintf(fp, "credit %c %d\n", _player->player_name[0], _player->point);
        _player = _player->next;
    }
    // gift A bomb 1
    char gift[4][8] = {"bomb", "barrier", "robot", "god"};
    _player = game_state->player;
    for (int i = 0; i < game_state->player_num; i++){
        for (int j = 0; j < 4; j++){
            if (j == 0 && _player->bomb_num)
                fprintf(fp, "gift %c %s %d\n", _player->player_name[0], gift[j], _player->bomb_num);
            if (j == 1 && _player->block_num)
                fprintf(fp, "gift %c %s %d\n", _player->player_name[0], gift[j], _player->block_num);
            if (j == 2 && _player->robot_num)
                fprintf(fp, "gift %c %s %d\n", _player->player_name[0], gift[j], _player->robot_num);
            if (j == 3 && _player->no_rent_time)
                fprintf(fp, "gift %c %s %d\n", _player->player_name[0], gift[j], _player->no_rent_time);
        }
        _player = _player->next;
    }
    // bomb in 23
    struct H_FLAG_ * hflag = NULL;
    for (int i = 0; i < 70; i++){
        hflag = game_state->map[i].house_flag;
        if(hflag){
            if (hflag->flag == BOMB)
                fprintf(fp, "bomb in %d\n", i);
            else if (hflag->flag == ROADBLOCK)
                fprintf(fp, "barrier in %d\n", i);
        }
        
    }
    // userloc A 25
    _player = game_state->player;
    for (int i = 0; i < game_state->player_num; i++){
        if (_player->sleep_time == 0)
            fprintf(fp, "userloc %c %d\n", _player->player_name[0], _player->cur_pos);
        else
            fprintf(fp, "userloc %c %d %d\n", _player->player_name[0], _player->cur_pos, _player->sleep_time);
        _player = _player->next;
    }
    //nextuser A
    fprintf(fp, "nextuser %c\n", game_state->current_player->player_name[0]);
    fclose(fp);
}

void HandlePreset(GAME *game_state){
    char preset_order[50] = {};
    char temp[50] = {};
    // setbuf(stdin, NULL);
    while(true){
        scanf("%s", temp);
        if (!strcmp(temp, "preset")){
            scanf("%s", temp);
            if (!strcmp(temp, "user"))
                ChooseRole(1);
            else if(!strcmp(temp, "map")){      // TODO
                int where;
                char whose;
                int level;
                scanf("%d %c %d", &where, &whose, &level);
                game_state->map[where].house_level = level;
                game_state->map[where].house_owner_id = Flag2Id(whose);
                PLAYER *player = game_state->player;
                while(player){
                    if(player->player_name[0] == whose){
                        player->house_id[where] = &(game_state->map[where]);
                        break;
                    }
                    else
                        player = player->next;
                }
            }
            else if(!strcmp(temp, "fund")){
                getchar();
                char who;
                int number = 0;
                scanf("%c %d", &who, &number);
                PLAYER *p = game_state->player;
                while(p){
                    if(p->player_name[0] == who){
                        p->money = number;
                        break;
                    }
                    else{
                        p = p->next;
                    }
                }
            }
            else if(!strcmp(temp, "credit")){
                getchar();
                char who;
                int number = 0;
                scanf("%c %d", &who, &number);
                PLAYER *p = game_state->player;
                while(p){
                    if(p->player_name[0] == who){
                        p->point = number;
                        break;
                    }
                    else{
                        p = p->next;
                    }
                }
            }
            else if(!strcmp(temp, "gift")){
                getchar();
                char who;
                int number;
                scanf("%c%s%d", &who, temp, &number);
                PLAYER *p = game_state->player;
                while(p){
                    if(p->player_name[0] == who){
                        if (!strcmp(temp, "bomb")){
                            p->bomb_num = number;
                        }
                        if (!strcmp(temp, "barrier")){
                            p->block_num = number;
                        }
                        if (!strcmp(temp, "robot")){
                            p->robot_num = number;
                        }
                        if (!strcmp(temp, "god")){
                            p->no_rent_time = number;
                        }
                        break;
                    }
                    else{
                        p = p->next;
                    }
                }
            }
            else if(!strcmp(temp, "bomb")){     // TODO
                int number;
                scanf("%d", &number);
                H_FLAG *hflag = (H_FLAG *)malloc(sizeof(H_FLAG));
                hflag->flag = BOMB;
                hflag->next = NULL;
                game_state->map[number].house_flag = hflag;
            }
            else if(!strcmp(temp, "barrier")){  // TODO
                int number;
                scanf("%d", &number);
                H_FLAG *hflag = (H_FLAG *)malloc(sizeof(H_FLAG));
                hflag->flag = ROADBLOCK;
                hflag->next = NULL;
                game_state->map[number].house_flag = hflag;
            }
            else if(!strcmp(temp, "userloc")){  // TODO
                getchar();
                char who;
                int where = 0;
                int when = 0;
                scanf("%c %d %d", &who, &where, &when);
                        player->sleep_time = when;
                        break;
                    }
                    else
                        player = player->next;
                }
                H_FLAG *hflag = (H_FLAG *)malloc(sizeof(H_FLAG));
                hflag->flag = who;
                hflag->next = NULL;
                H_FLAG *hflag2 = game_state->map[where].house_flag;
                if(hflag2)
                    hflag->next = hflag2;
                game_state->map[where].house_flag = hflag;
            }
            else if(!strcmp(temp, "nextuser")){ // TODO
                getchar();
                char who;
                scanf("%c", &who);
                PLAYER *player = game_state->player;
                while(player){
                    if(player->player_name[0] == who){
                        game_state->current_player = player;
                        break;
                    }
                    else
                        player = player->next;
                }
            }
        }
        else{
            break;
        }      
    }
}

int Flag2Id(char flag){
    if (flag == 'Q')
        return 1;
    if (flag == 'A')
        return 2;
    if (flag == 'J')
        return 3;
    if (flag == 'S')
        return 4;
    return 0;
}

char Id2Flag(int id){
    if (id == 1)
        return 'Q';
    if (id == 2)
        return 'A';
    if (id == 3)
        return 'J';
    if (id == 4)
        return 'S';
    return 0;
}