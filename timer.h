/*********��ʱ��***************/ 

#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"

class Timer{
	private:
		int startTicks;															// ��ʱ��ʼʱ��ʱ�� 
		int pausedTicks;														// ��ͣʱ��ʱ�� 
		bool paused;															// �Ƿ���ͣ 
		bool started;															// �Ƿ�ʼ��ʱ 
	public:
		Timer();																// ���캯�� 
		void start();															// ��ʼ��ʱ 
		void stop();															// ֹͣ��ʱ 
		void pause();															// ��ͣ��ʱ 
		void unpause();															// �ָ���ʱ 
		int get_ticks();														// ��ü�ʱ��ʼ�����ڹ��˶���ʱ�� 
		bool is_started();														// �Ƿ�ʼ 
		bool is_paused();														// �Ƿ���ͣ 
};

#endif
