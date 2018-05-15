/********************* 子弹类的定义 *********************************/ 
#ifndef _BULLET_H_
#define _BULLET_H_

//#include "share.h" 
#include "tile.h"
#include "MyDefine.h"

class Bullet{
	private:
		bool isShot;															// 是否击中了什么 
		int dir;																// 运动方向
		int speed;																// 子弹速度
		int bombTime;															// 爆炸的效果持续时间 
		int shotIron;															// 是否能打铁 
		Thing thing;															// 击中了什么东西 
		SDL_Rect box;															// 位置，也是碰撞盒子 
		SDL_Rect bbox;															// 爆炸效果的位置 
		SDL_Rect clip[4];														// 剪切  
		SDL_Surface *explode1;													// 爆炸效果 1 
		SDL_Surface *explode2;													// 爆炸效果 2 
		SDL_Surface *myself;													// 自己的图像 
		Mix_Chunk *hit;															// 击中的音效 
	public:
		Bullet( const SDL_Rect &b, int d );										// 构造函数，传入位置和方向 
		~Bullet(); 
		void show();															// 显示 
		bool collision();														// 检测是否撞到墙					
		void reset( const SDL_Rect &b, int d, bool s, int iron = -1, int sp = 2);// 重置 
		bool is_shot()const;													// 返回 isShot 
		void move();															// 移动位置 
		bool will_hit(Thing hit);												// 即将击中什么 
		const SDL_Rect& get_box()const;											// 返回碰撞盒子 
		void change_status( bool status );										// 改变子弹状态，即是否击中什么 
		bool hit_tile(int x, int y)const;										// 是否击中障碍 
		int in_bored( int x )const;												// 保持 x 在游戏界面内 
};

#endif 
