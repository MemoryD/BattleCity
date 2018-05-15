#include "bonus.h"

//构造 
Bonus::Bonus()
{
	me = load_image( "graphics\\bonus.bmp" );
	isShow = false;																// 初次构造不显示 
	
	born();
	
	for(int i = 0; i < 6; i++)													// 初始化剪切 
	{
		clip[i].x = i * BONUS_WIDTH;
		clip[i].y = 0;
		clip[i].w = BONUS_WIDTH;
		clip[i].h = BONUS_HEIGHT;
	}
}

//析构 
Bonus::~Bonus()
{
	SDL_FreeSurface( me );
}

//产生一个奖励 
void Bonus::born()
{
	isShow = true;																// 正在显示 
	
	type = random( 0, 5 );														// 类型随机 
	
	showTime = 3;																// 闪烁间隔为 3 
	
	box.w = BONUS_WIDTH;
	box.h = BONUS_HEIGHT;
	
	box.x = rand() % (GAME_WIDTH - box.w);
	box.y = rand() % (GAME_HEIGHT - box.h);
}

//显示奖励 
void Bonus::show()
{
	if( !isShow ) return;
	if(showTime > 0)
	{
		SDL_BlitSurface( me, &clip[type], screen, &box);
	}
	showTime--;
	if(showTime == -3) showTime = 3;
}

// 
const SDL_Rect& Bonus::get_box()const
{
	return box;
}

// 
int Bonus::get_type()const
{
	return type;
}

void Bonus::change( bool s )
{
	isShow = s;
}
