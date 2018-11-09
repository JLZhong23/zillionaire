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
