#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INITIAL_MONEY 10000  // 初始金钱


/*
*每个地图块的结构体定义
*/

typedef struct MAP_BLOCK_ {
    int HouseOwnerId;   //房产主人Id
    char house_flag;    //房屋表示
    int HouseLevel;     //房屋等级
    int HouseType;      //房屋类型
    int MapValue;       //当前地块价值
    int BlockType;      //道具类型
}MAP_BLOCK;

/*
*每个玩家的结构体定义
*/
typedef struct PLAYER_ {
    int PlayerId;   //用户ID
    char *Name;  //用户名称
    int CurPos;     //当前位置
    int *HouseId;   //名下房产位置
    int BombNum;    //炸弹数量
    int RobotNum;   //机器娃娃数量
    int BlockNUm;   //路障数量
    int SleepTime;  //跳过轮数
    int Money;      //可移动资产
    int Point;      //点数
    struct PLAYER_ *next; // 下一个玩家
    // 固定资产待定
}PLAYER;

/*
*游戏状态的记录
*/
typedef struct GAME_ {
    int play_num; //玩家数量
    PLAYER *current_player; //当前玩家
    PLAYER *player;     // 指向玩家的指针
    char path[50];      // 存档路径
    MAP_BLOCK map[70];  // 地图
}GAME;

void game_start(MAP_BLOCK *map, GAME *game);
void initialize(MAP_BLOCK *map, GAME *game_state, int play_num);
char get_house_flag(int i);


int main() {
    GAME *game_state;
    
    game_state = (GAME *)malloc(sizeof(game_state));
    int play_num;
    while (1) {
        char return_back;
        printf("您是否要恢复之前游戏进度：y or n  ");
        return_back = getchar();
        if (return_back != 'y' && return_back != 'n') {
            // 做恢复进度处理
            system("cls");            
            continue;
        } else{
        	break;
		} 
        
    }
    printf("请输入玩家数量（2-4人）:");
    scanf("%d", &play_num);
    while (1) {
        if (play_num >= 2 && play_num <= 4) {
            game_state->play_num = play_num;
            break;
        }
        printf("\n您输入的人数有误请重新输入");
        scanf("%d", &play_num);
    }
    int count = play_num;
    int role[4] = {0,0,0,0};
    char role_name[5][10] = {"0", "钱夫人Q", "阿拉伯A", "金贝贝J", "孙小美S"};
    PLAYER *pp;
    while (count) {
        PLAYER *p = (PLAYER*)malloc(sizeof(PLAYER));
        if (count == play_num) {
            game_state->player = p;
            game_state->current_player = p;
            pp = p;
        } else {
            pp->next = p;
            pp = p;
        }
        printf("选择%d号的角色: 1为钱夫人，2为阿土伯，3为金贝贝，4为孙小美", play_num - count + 1);
        short num;
        scanf("%d", &num);
        while (1) {
            if (num > 4 || num < 1) {
                printf("选择错误");
                printf("选择%d号的角色: 1为钱夫人，2为阿土伯，3为金贝贝，4为孙小美", play_num - count + 1);
                scanf("%d", &num);
            } else {
                if (role[num] == 0) {
                    role[num] = 1;
                    p->BlockNUm = 0;
                    p->BombNum = 0;
                    // p->HouseId
                    p->CurPos = 0;
                    p->Money = INITIAL_MONEY;
                    p->Name = role_name[num];
                    p->next = NULL;
                    p->PlayerId = play_num - count + 1;
                    p->Point = 0;
                    p->RobotNum = 0;
                    p->SleepTime = 1;
                    break;
               } else {
                   printf("角色已被选择请选择其他角色:");
                   scanf("%d", &num);
               }
            }
        }
        count --;
    }
    initialize(&game_state->map[0], game_state, play_num);
    system("cls");
    game_start(&game_state->map[0], game_state);
}

/**
 * 获取一个1~6之间的随机数
 */
int get_random_num() {
    int num = rand() % 6;
    if (num == 0) {
        num ++;
    }
    return num;
}

/**
 * 游戏开始
 */

void game_start(MAP_BLOCK *map, GAME *game) {
    while (1) {
        int num = game->play_num;
        short round = 1;
        while (round <= num) {
            if (game->current_player->SleepTime == 1) {
                printf("%s>", game->current_player->Name);
                char command[10];
                scanf("%s", &command);
                char roll[10] = "roll";
                char query[10] = "query";
                if (!strcmp(command, roll)) {
                	map[game->current_player->CurPos].house_flag = get_house_flag(game->current_player->CurPos);
                    short number = get_random_num();
                    printf("您获得的点数为：%d\n",number);
                    game->current_player->CurPos = (game->current_player->CurPos + number) % 70;
                    map[game->current_player->CurPos].house_flag = game->current_player->Name[strlen(game->current_player->Name) - 1];
					// 更新地图
                    if (game->current_player->next) {
                    game->current_player = game->current_player->next;
                    } else {
                        game->current_player = game->player;
                    }
                } else if (!strcmp(command, query)) {
				    printf("你是第%d号玩家，您的角色是%s,您当前所在位置是%d,地图符号为%c \n", game->current_player->PlayerId, game->current_player->Name, game->current_player->CurPos, get_house_flag(game->current_player->CurPos));
					continue;	
				} else {
                    printf("您输入的指令有误；\n");
                    continue;
                }
            } else {
                game->current_player->SleepTime --;
                if (game->current_player->next) {
                    game->current_player = game->current_player->next;
                } else {
                    game->current_player = game->player;
                }
            }
            round ++;
        }
        system("cls");
    }
}
/**
 * 进行初始化
 */
void initialize(MAP_BLOCK *map, GAME *game_state, int play_num) {
	//地图初始化 
	int i;
	for(i = 0;i < 69;i++) {
		map[i].BlockType = 0;
		map[i].HouseLevel = 0;
		map[i].HouseOwnerId = 0;
		map[i].MapValue = 0;
		if(i == 0) {
			map[i].house_flag='S';           // 起始点 
			map[i].HouseType=1;
		} else if((i >= 1 && i <= 13) || (i >= 15 && i <= 27)) {
			map[i].house_flag = '0';         // 空地第一段 
			map[i].HouseType=2;
		} else if(i == 14) {
			map[i].house_flag = 'H';         // 医院 
			map[i].HouseType=3;
		} else if(i == 28) {
			map[i].house_flag = 'T';         // 道具屋 
			map[i].HouseType=4;
		} else if(i >= 29 && i<= 34) {
			map[i].house_flag = '0';        // 空地第二段 
			map[i].HouseType=5;
		}else if(i == 35) {                 // 礼品屋 
			map[i].house_flag = 'G';
			map[i].HouseType=6;
		}else if((i >= 36 && i<= 48) || (i >= 50 && i <= 62)) {
			map[i].house_flag = '0';        // 空地第三段 
			map[i].HouseType=7;
		}else if(i==49) {
			map[i].house_flag = 'P';        // 监狱 
			map[i].HouseType=8;
		}else if(i == 63) {
			map[i].house_flag = 'M';        // 魔法屋 
			map[i].HouseType=9;
		}else {
			map[i].house_flag = '$';        // 矿地（此处还需扩展） 
			map[i].HouseType=10;
		}
		
	} 
}

/**
*根据位置获取房屋符号
*/
char get_house_flag(int i) {
	char flag;
	if(i == 0) {
		flag = 'S';           // 起始点 
	} else if((i >= 1 && i <= 13) || (i >= 15 && i <= 27)) {
		flag = '0';
	} else if(i == 14) {
		flag = 'H';
	} else if(i == 28) {
		flag = 'T';
	} else if(i >= 29 && i<= 34) {
		flag = '0';
	}else if(i == 35) {                 // 礼品屋 
		flag = 'G';
	}else if((i >= 36 && i<= 48) || (i >= 50 && i <= 62)) {
		flag = '0';
	}else if(i==49) {
		flag = 'P';
	}else if(i == 63) {
		flag = 'M';
	}else {
		flag = '$';
	}
	return flag;
}



