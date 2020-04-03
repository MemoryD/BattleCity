#ifndef _GAME_H_
#define _GAME_H_

#include "MyDefine.h"
#include "tank.h"
#include "tile.h"
#include "Timer.h"
#include "bonus.h"
#include <cstdlib>
#include <ctime> 
#include <queue>
#include <cstdio>

class MyGame{
	private:
		//以下为游戏中用到的一些变量 
		Tank *tank[TANK_TWO_NUM];												// 指向坦克的指针数组 
		int map[TILE_NUM][TILE_NUM];											// 地图数组 
		int enemyNum;															// 当前关卡剩余的敌人数量 
		int killNum;															// 当前关卡击杀的敌人数量 
		int tankNum;															// 同时出现的最多坦克总数 
		int life_1;																// player1 的剩余生命 
		int life_2;																// player2 的剩余生命 
		int level;																// 当前关卡 
		bool end;																// 游戏是否结束 
		bool pause;																// 游戏是否暂停 
		int timeStop;															// 时间是否停止， 大于 0 表示停止 
		int bonusShowTime;														// 奖励剩余的显示时间 
		int homeTime;															// 总部加固剩余的时间 
		int endTime;															// 离结束剩余的时间 
		Bonus bonus;															// 奖励 
		Timer enemyTime;														// 创造敌人的时间间隔 用的计时器 
		Timer fps;																// 控制帧率用的计时器 
		std::string stage[TOTAL_STAGE];											// 关卡的名称数组 
		//以下为游戏中用到的各种素材 
		SDL_Surface *p1;														// player1 坦克 
		SDL_Surface *p2;														// player2 坦克 
		SDL_Surface *enemy;														// 敌坦克 
		SDL_Surface *misc;														// 侧边小坦克图标 
		SDL_Surface *bg;														// 侧边背景 
		SDL_Surface *num;														// 各种显示的数字 
		SDL_Surface *flag;														// 侧边小旗帜 
		SDL_Surface *home;														// 总部的鹰图片 
		SDL_Surface *over;														// 总部被打破时显示的图片 
		SDL_Surface *pase;														// 暂停时显示的图片 
		SDL_Surface *splash;													// 初始界面显示的图片 
		SDL_Surface *explain;													// 游戏说明显示的图标 
		SDL_Surface *declare;													// 游戏说明的内容 
		SDL_Surface *choose;													// 选择时用的小坦克图标 
		SDL_Surface *brand;														// 显示作者 
		SDL_Surface *gg;														// 游戏结束时显示的 GAME OVER 
		SDL_Surface *bomb1;														// 炸弹效果 1 
		SDL_Surface *bomb2;														// 炸弹效果 2 
		SDL_Surface *st;														// 关卡切换时显示的图片 
		Mix_Music *music;														// 开场音乐
		Mix_Chunk *bom;															// 敌人全灭时的音效  
		Mix_Chunk *peow;														// 获得奖励时的音效 
		//以下为用到的图片剪切区域，对应上面的图片 
		SDL_Rect miscClip[6];													// 
		SDL_Rect numClip[10];													// 
		SDL_Rect homeClip[2];													//
		SDL_Rect chooseClip;													// 选择图标的剪切，就是 player1 的坦克 
		SDL_Rect homeBox;														// 总部的位置 
	public:
		MyGame();																// 构造函数
		~MyGame();																// 析构函数 
		void load_files();														// 各种文件的载入 
		void all_clip();														// 图片的裁剪区域 
		void tank_init()const;													// 坦克的初始化 
		void num_init();														// 变量的初始化 
		bool show_splash();														// 显示初始选择界面 
		void show_game();														// 显示游戏界面 
		void show_other();														// 显示侧边区域 
		void show_num( int x, SDL_Rect &set );									// 显示数字 
		void show_stage();														// 显示关卡切换画面 
		void show_end();														// 显示游戏结束画面 
		void tank_move();														// 坦克的移动 
		void creat_tank();														// 创造坦克 
		void check_attack();													// 攻击检测，是否击中 
		void check_end();														// 检测游戏是否结束 
		void check_bonus();														// 检查是否获得奖励以及进行奖励 
		void change_level();													// 切换关卡 
		void enemy_attack()const;												// 敌人进行攻击 
		void handle_input( const SDL_Event &event );							// 处理输入 
		void control_fps();														// 控制帧率 
		void gameRun();															// 游戏主要运行函数 
		bool is_end();															// 是否结束 
};

#endif
