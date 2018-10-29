#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INITIAL_MONEY 10000  // ��ʼ��Ǯ


/*
*ÿ����ͼ��Ľṹ�嶨��
*/

typedef struct MAP_BLOCK_ {
    int HouseOwnerId;   //��������Id
    char house_flag;    //���ݱ�ʾ
    int HouseLevel;     //���ݵȼ�
    int HouseType;      //��������
    int MapValue;       //��ǰ�ؿ��ֵ
    int BlockType;      //��������
}MAP_BLOCK;

/*
*ÿ����ҵĽṹ�嶨��
*/
typedef struct PLAYER_ {
    int PlayerId;   //�û�ID
    char *Name;  //�û�����
    int CurPos;     //��ǰλ��
    int *HouseId;   //���·���λ��
    int BombNum;    //ը������
    int RobotNum;   //������������
    int BlockNUm;   //·������
    int SleepTime;  //��������
    int Money;      //���ƶ��ʲ�
    int Point;      //����
    struct PLAYER_ *next; // ��һ�����
    // �̶��ʲ�����
}PLAYER;

/*
*��Ϸ״̬�ļ�¼
*/
typedef struct GAME_ {
    int play_num; //�������
    PLAYER *current_player; //��ǰ���
    PLAYER *player;     // ָ����ҵ�ָ��
    char path[50];      // �浵·��
    MAP_BLOCK map[70];  // ��ͼ
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
        printf("���Ƿ�Ҫ�ָ�֮ǰ��Ϸ���ȣ�y or n  ");
        return_back = getchar();
        if (return_back != 'y' && return_back != 'n') {
            // ���ָ����ȴ���
            system("cls");            
            continue;
        } else{
        	break;
		} 
        
    }
    printf("���������������2-4�ˣ�:");
    scanf("%d", &play_num);
    while (1) {
        if (play_num >= 2 && play_num <= 4) {
            game_state->play_num = play_num;
            break;
        }
        printf("\n�������������������������");
        scanf("%d", &play_num);
    }
    int count = play_num;
    int role[4] = {0,0,0,0};
    char role_name[5][10] = {"0", "Ǯ����Q", "������A", "�𱴱�J", "��С��S"};
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
        printf("ѡ��%d�ŵĽ�ɫ: 1ΪǮ���ˣ�2Ϊ��������3Ϊ�𱴱���4Ϊ��С��", play_num - count + 1);
        short num;
        scanf("%d", &num);
        while (1) {
            if (num > 4 || num < 1) {
                printf("ѡ�����");
                printf("ѡ��%d�ŵĽ�ɫ: 1ΪǮ���ˣ�2Ϊ��������3Ϊ�𱴱���4Ϊ��С��", play_num - count + 1);
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
                   printf("��ɫ�ѱ�ѡ����ѡ��������ɫ:");
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
 * ��ȡһ��1~6֮��������
 */
int get_random_num() {
    int num = rand() % 6;
    if (num == 0) {
        num ++;
    }
    return num;
}

/**
 * ��Ϸ��ʼ
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
                    printf("����õĵ���Ϊ��%d\n",number);
                    game->current_player->CurPos = (game->current_player->CurPos + number) % 70;
                    map[game->current_player->CurPos].house_flag = game->current_player->Name[strlen(game->current_player->Name) - 1];
					// ���µ�ͼ
                    if (game->current_player->next) {
                    game->current_player = game->current_player->next;
                    } else {
                        game->current_player = game->player;
                    }
                } else if (!strcmp(command, query)) {
				    printf("���ǵ�%d����ң����Ľ�ɫ��%s,����ǰ����λ����%d,��ͼ����Ϊ%c \n", game->current_player->PlayerId, game->current_player->Name, game->current_player->CurPos, get_house_flag(game->current_player->CurPos));
					continue;	
				} else {
                    printf("�������ָ������\n");
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
 * ���г�ʼ��
 */
void initialize(MAP_BLOCK *map, GAME *game_state, int play_num) {
	//��ͼ��ʼ�� 
	int i;
	for(i = 0;i < 69;i++) {
		map[i].BlockType = 0;
		map[i].HouseLevel = 0;
		map[i].HouseOwnerId = 0;
		map[i].MapValue = 0;
		if(i == 0) {
			map[i].house_flag='S';           // ��ʼ�� 
			map[i].HouseType=1;
		} else if((i >= 1 && i <= 13) || (i >= 15 && i <= 27)) {
			map[i].house_flag = '0';         // �յص�һ�� 
			map[i].HouseType=2;
		} else if(i == 14) {
			map[i].house_flag = 'H';         // ҽԺ 
			map[i].HouseType=3;
		} else if(i == 28) {
			map[i].house_flag = 'T';         // ������ 
			map[i].HouseType=4;
		} else if(i >= 29 && i<= 34) {
			map[i].house_flag = '0';        // �յصڶ��� 
			map[i].HouseType=5;
		}else if(i == 35) {                 // ��Ʒ�� 
			map[i].house_flag = 'G';
			map[i].HouseType=6;
		}else if((i >= 36 && i<= 48) || (i >= 50 && i <= 62)) {
			map[i].house_flag = '0';        // �յص����� 
			map[i].HouseType=7;
		}else if(i==49) {
			map[i].house_flag = 'P';        // ���� 
			map[i].HouseType=8;
		}else if(i == 63) {
			map[i].house_flag = 'M';        // ħ���� 
			map[i].HouseType=9;
		}else {
			map[i].house_flag = '$';        // ��أ��˴�������չ�� 
			map[i].HouseType=10;
		}
		
	} 
}

/**
*����λ�û�ȡ���ݷ���
*/
char get_house_flag(int i) {
	char flag;
	if(i == 0) {
		flag = 'S';           // ��ʼ�� 
	} else if((i >= 1 && i <= 13) || (i >= 15 && i <= 27)) {
		flag = '0';
	} else if(i == 14) {
		flag = 'H';
	} else if(i == 28) {
		flag = 'T';
	} else if(i >= 29 && i<= 34) {
		flag = '0';
	}else if(i == 35) {                 // ��Ʒ�� 
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



