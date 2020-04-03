#ifndef BONUS_H_
#define BONUS_H_

#include "MyDefine.h"

class Bonus{
	private:
		int type;																// 奖励的类型 
		int showTime;															// 闪烁显示的间隔时间 
		bool isShow;															// 是否正在显示 
		SDL_Surface *me;														// 指向自己的表面 
		SDL_Rect box;															// 位置，也是碰撞盒子 
		SDL_Rect clip[6];														// 图片的剪切 
	public:
		Bonus();																// 构造 
		~Bonus();
		void born();															// 产生一个奖励 
		void show();															// 显示奖励 
		int get_type()const;													// 返回奖励类型 
		const SDL_Rect& get_box()const;											// 返回碰撞盒子 
		void change( bool s );													// 改变状态，即是否显示 
};

#endif
