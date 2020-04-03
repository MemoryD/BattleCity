#include "Timer.h"

//���� 
Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

//��ʼ��ʱ 
void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();												// ��õ�ǰʱ�� 
}

//ֹͣ��ʱ 
void Timer::stop()
{
	started = false;
	paused = false;
}

//��ü�ʱ��ʼ�����ڹ��˶೤ʱ�� 
int Timer::get_ticks()
{
	if( started == true )														// ���ѿ�ʼ��ʱ 
	{
		if( paused == true )													// ����ͣ��������ͣʱ��ʱ�� 
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;									// ���򷵻ص�ǰʱ�俪ʼʱʱ�� 
		}
	}
	
	return 0;
}

//��ͣ��ʱ 
void Timer::pause()
{
	if( ( started == true ) && ( paused == false ) )
	{
		paused = true;
		
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

//�ָ���ʱ 
void Timer::unpause()
{
	if( paused == true )
	{
		paused = false;
		
		startTicks = SDL_GetTicks() - pausedTicks;
		
		pausedTicks = 0;
	}
}

bool Timer::is_started()
{
    return started;    
}
 
bool Timer::is_paused()
{
    return paused;    
}
