#include "bonus.h"

//���� 
Bonus::Bonus()
{
	me = load_image( "..\\graphics\\bonus.bmp" );
	isShow = false;																// ���ι��첻��ʾ 
	
	born();
	
	for(int i = 0; i < 6; i++)													// ��ʼ������ 
	{
		clip[i].x = i * BONUS_WIDTH;
		clip[i].y = 0;
		clip[i].w = BONUS_WIDTH;
		clip[i].h = BONUS_HEIGHT;
	}
}

//���� 
Bonus::~Bonus()
{
	SDL_FreeSurface( me );
}

//����һ������ 
void Bonus::born()
{
	isShow = true;																// ������ʾ 
	
	type = random( 0, 5 );														// ������� 
	
	showTime = 3;																// ��˸���Ϊ 3 
	
	box.w = BONUS_WIDTH;
	box.h = BONUS_HEIGHT;
	
	box.x = rand() % (GAME_WIDTH - box.w);
	box.y = rand() % (GAME_HEIGHT - box.h);
}

//��ʾ���� 
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
