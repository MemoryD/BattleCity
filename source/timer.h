/*********计时器***************/ 

#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"

class Timer{
	private:
		int startTicks;															// 计时开始时的时间 
		int pausedTicks;														// 暂停时的时间 
		bool paused;															// 是否暂停 
		bool started;															// 是否开始计时 
	public:
		Timer();																// 构造函数 
		void start();															// 开始计时 
		void stop();															// 停止计时 
		void pause();															// 暂停计时 
		void unpause();															// 恢复计时 
		int get_ticks();														// 获得计时开始到现在过了多少时间 
		bool is_started();														// 是否开始 
		bool is_paused();														// 是否暂停 
};

#endif
