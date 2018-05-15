#ifndef __MYDEFINE_H 
#define __MYDEFINE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string>

/**************************一些常量的定义************************************/ 
//界面 
const int SCREEN_WIDTH = 505;												//屏幕宽 
const int SCREEN_HEIGHT = 416;												//屏幕高 
const int SCREEN_BPP = 32;													//分辨率

const int FPS = 30;															//帧率 

const int GAME_WIDTH = 416;													//游戏界面宽度 
const int GAME_HEIGHT = 416;												//游戏界面高度 

const int TOTAL_STAGE = 40;													//关卡数 

//主坦克 
const int PLAY1_START_X = 130;												//玩家 1 的初始位置 
const int PLAY1_START_Y = 382;												//
const int PLAY2_START_X = 258;												//玩家 2 的初始位置 
const int PLAY2_START_Y = 382; 												//

const int ONE_PLAYER = 265;													//初始选择界面的参数，判定是单人或双人 
const int TWO_PLAYER = 297;													//

const int TANK_ONE_NUM = 6;													//单人游戏时同一时间内出现的坦克数量(含主坦克)
const int TANK_TWO_NUM = 8;													//双人游戏时同一时间内出现的坦克数量(含主坦克)

const int TANK_SIZE = 28;													//坦克大小 
const int TANK_SPEED = 1;													//坦克速度基数 

//敌坦克 
const int ENEMY_TOTAL_NUM = 20;										 		//一个关卡的敌坦克数量 
const int ENMEY_ATTACK_TIME = 30; 											//敌坦克攻击的频率 
const int ENEMY_SPECIES = 3;												//敌坦克种类
const int ENEMY_SLOW_SPEED = 3;												//一般敌坦克的速度 ，最终速度需乘于速度基数 
const int ENEMY_FAST_SPEED = 5;												//比较快的敌坦克速度 

//子弹 
const int BULLET_SIZE = 8;													//子弹大小 
const int BULLET_SPEED = 4;													//子弹速度 
const int BULLET_ADDSPEED = 2;												//主坦克升级时，子弹速度的增量 

//数据类型 
enum Thing{TANK, BULLET, WALL, NOTHING};									//子弹击中的目标 

struct Move{																//运动方向，及每个方向的增量 
	int x;
	int y;
	int key;																//方向键 
};

extern int offset[3];														//敌坦克的初始 X 位置 
extern SDL_Surface *screen;													// 游戏界面的表面，全局变量 
// 
const int UP = 0;															//方向往上 
const int RIGHT = 1;														//右
const int DOWN = 2;															//下 
const int LEFT = 3;															//左 

// 
const int MISC_SIZE = 14;													//侧边小坦克图标大小 
const int NUM_SIZE = 14;													//数字大小 

//以下均为地图上的标识，地图是一个 Tile 类的二维数组 
const int TILE_SIZE = 16;													//障碍大小 
const int TILE_NUM = 26;													//每行及每列的障碍物 

const int TILE_BRICK = 0;													//砖块 
const int TILE_IRON = 1;													//铁 
const int TILE_LAWN = 2;													//草坪 
const int TILE_WATER = 3;													//水
const int TILE_BLACK = 9; 													//没有障碍，背景黑色

//以下为道具奖励有关的常量 
const int BONUS_WIDTH = 30;													//道具奖励图标的宽 
const int BONUS_HEIGHT = 28;												//高 

const int BONUS_ADDTANK = 0;												//奖励一辆坦克 
const int BONUS_TIMESTOP = 1;												//敌人时间停止 
const int BONUS_HOME = 2;													//总部加固 
const int BONUS_BOMB = 3;													//敌人全灭 
const int BONUS_STAR = 4;													//星级+1 
const int BONUS_SHIELD = 5;													//暂时无敌 

const int BONUS_TIME = 600;													//道具奖励时间 
const int BONUS_SHOW_TIME = 400;											//道具显示时间 

const int BORN_TIME = 20;													//出生时星星闪烁时间，时间单位是 帧，下同 
const int INIT_SHIELD_TIME = 60;											//初始无敌时间

// 
const int TIME_TO_END = 200; 												//游戏结束的额缓冲时间
 
// 
const int BLACK_KEY = 263172;												// 部分黑色背景的值 
const int WHITE_KEY = 16777215;												// 白色背景的值 

SDL_Surface *load_image( std::string filename ,int key = 0 );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
bool init_SDL();
bool quit_SDL();
bool check_touch( const SDL_Rect &A, const SDL_Rect &B );
bool over_bored( const SDL_Rect &box );
int random( int min, int max );
 
/***************************************************************************/ 
#endif
