#include "bullet.h"

Move bulletTo[4] = {{0, -BULLET_SPEED, UP}, {BULLET_SPEED, 0, RIGHT}, {0, BULLET_SPEED, DOWN}, {-BULLET_SPEED, 0, LEFT}};

//构造函数 
Bullet::Bullet( const SDL_Rect &b, int d )
{
	myself = load_image( "graphics\\bullet.bmp",BLACK_KEY );
	explode1 = load_image( "graphics\\explode1.bmp" );
	explode2 = load_image( "graphics\\explode2.bmp" ,BLACK_KEY);
	hit = Mix_LoadWAV( "sound\\hit.wav" );
	
	speed = 2;																	// 默认速度为 2 
	isShot = true;																// 刚构造时默认不显示 
	shotIron = false;															// 默认不能打铁 
	bombTime = 0;																//  
	box.w = BULLET_SIZE + 2;
	box.h = BULLET_SIZE + 2;
	
	reset( b, d , true);														// 重置一些参数 
	
	clip[0].x = 0;																// 根据图片剪切 
	clip[1].x = BULLET_SIZE - 1;
	clip[2].x = 2 * BULLET_SIZE;
	clip[3].x = 3 * BULLET_SIZE - 1;
	
	for(int i = 0; i < 4; i++)
	{
		clip[i].y = 0;
		clip[i].w = BULLET_SIZE;
		clip[i].h = BULLET_SIZE;
	}
}

//析构 
Bullet::~Bullet()
{
	SDL_FreeSurface( myself );
	SDL_FreeSurface( explode1 );
	SDL_FreeSurface( explode2 );
	Mix_FreeChunk( hit );
}

//重置位置，传入 位置，方向，是否显示，是否能打铁，以及速度 
void Bullet::reset( const SDL_Rect &b, int d, bool s, int iron, int sp )
{
	isShot = s;
	dir =  d;
	thing = NOTHING;
	speed = sp;
	shotIron = iron;
	switch( d )																	//根据位置和方向调整位置 
	{
		case UP:{
			box.x = b.x + ( b.w - BULLET_SIZE ) / 2;
			box.y = b.y;
			break;
		}
		case DOWN:{
			box.x = b.x + ( b.w - BULLET_SIZE ) / 2;
			box.y = b.y + b.h - BULLET_SIZE;
			break;
		}
		case RIGHT:{
			box.x = b.x + b.w - BULLET_SIZE;
			box.y = b.y + ( b.h - BULLET_SIZE ) / 2;
			break;
		}
		case LEFT:{
			box.x = b.x;
			box.y = b.y + ( b.h - BULLET_SIZE ) / 2;
			break;
		}
	}
}

//碰撞检测，是否撞墙 
bool Bullet::collision()
{	
	bool flag = false;
	int x, y, begin, end;

	switch( dir )																// 根据方向选择方案 
	{																			// 遍历 移动前位置到移动后位置 之间的区域， 
		case UP:{																// 检测是否有障碍，若有，则立即停止 
			x = in_bored( box.x / TILE_SIZE );
			y = in_bored( ( box.x + box.w ) / TILE_SIZE );
			begin = in_bored( (box.y - speed * bulletTo[dir].y) / TILE_SIZE );
			end = in_bored( box.y / TILE_SIZE );
			for(int i = begin; i >= end ; i--)
			{
				if( hit_tile(i, x) ) flag = true;
				if( hit_tile(i, y) ) flag = true;
				if( flag )
					return flag;
			}
			break;
		}
		case DOWN:{
			x = in_bored( box.x / TILE_SIZE );
			y = in_bored( ( box.x + box.w ) / TILE_SIZE );
			begin = in_bored( (box.y - speed * bulletTo[dir].y) / TILE_SIZE );
			end = in_bored( box.y / TILE_SIZE );
			for(int i = begin; i <= end; i++)
			{
				if( hit_tile(i, x) ) flag = true;
				if( hit_tile(i, y) ) flag = true;
				if( flag )
					return flag;
			}
			break;
		}
		case LEFT:{
			x = in_bored( box.y / TILE_SIZE );
			y = in_bored( ( box.y + box.h ) / TILE_SIZE );
			begin = in_bored( (box.x - speed * bulletTo[dir].x) / TILE_SIZE );
			end = in_bored( box.x / TILE_SIZE );
			for(int i = begin; i >= end; i--)
			{
				if( hit_tile(x, i) ) flag = true;
				if( hit_tile(y, i) ) flag = true;
				if( flag )
					return flag;
			}
			break;
		}
		case RIGHT:{
			x = in_bored( box.y / TILE_SIZE );
			y = in_bored( ( box.y + box.h ) / TILE_SIZE );
			begin =  in_bored( (box.x - speed * bulletTo[dir].x) / TILE_SIZE );
			end = in_bored( box.x / TILE_SIZE );
			for(int i = begin; i <= end; i++)
			{
				if( hit_tile(x, i) ) flag = true;
				if( hit_tile(y, i) ) flag = true;
				if( flag )
					return flag;
			}
			break;
		}
	}
	
	if( over_bored( box ) )														// 是否越界 
	{																			// 若是，则退回以显示爆炸效果 
		box.x -= speed * bulletTo[dir].x >> 1 ;
		box.y -= speed * bulletTo[dir].y >> 1;
		if( shotIron >= 0 )														// 若是主坦克的子弹撞墙，则播放音效 
				Mix_PlayChannel( -1, hit, 0);
		return true;
	}
	
	return false;
}

// 传入即将击中的东西，以显示相应的效果 
bool Bullet::will_hit(Thing hit)
{
	if( hit == TANK )															// 若击中坦克，显示爆炸效果 
	{
		bombTime = 4;
		bbox.x = box.x - 10;
		bbox.y = box.y - 10;
		thing = TANK;
		isShot = true;
	}
	else if( hit == BULLET )													// 与子弹抵消 
	{
		isShot = true;
	}
}

//子弹移动 
void Bullet::move()
{
	if( !isShot )																// 若已死，则不显示 
	{
		box.x += speed * bulletTo[dir].x;
		box.y += speed * bulletTo[dir].y;
		if( collision() ) 														// 撞墙，则显示爆炸效果 
		{
			bombTime = 3;
			thing = WALL;
			isShot = true;
			return;
		}
	}
}

// 显示子弹 
void Bullet::show()
{
	if(!isShot)																	// 显示子弹本身 
		SDL_BlitSurface( myself, &clip[dir], screen, &box );
		
	if( thing ==  WALL )														// 显示爆炸效果 
	{
		bbox.x = box.x - 10;
		bbox.y = box.y - 10;
		if( bombTime > 0)
		{
			SDL_BlitSurface( explode1, NULL, screen, &bbox );
			bombTime--;
		}
	}
	else if( thing == TANK )
	{
		if( bombTime > 2 )
		{
			bbox.x = box.x - 10;
			bbox.y = box.y - 10;
			SDL_BlitSurface( explode1, NULL, screen, &bbox );
			bombTime--;
		}
		else if( bombTime > 0 )
		{
			bbox.x = box.x - 28;
			bbox.y = box.y - 28;
			SDL_BlitSurface( explode2, NULL, screen, &bbox );
			bombTime--;
		}
	}
}

//是否击中障碍 
bool Bullet::hit_tile(int x, int y)const 
{
	int t = tile[x][y]->get_type();
	if( t == TILE_BRICK || t == TILE_IRON )
	{
		if( t == TILE_BRICK ) tile[x][y]->change_type( TILE_BLACK );			// 砖块可以直接打掉 
		if( t == TILE_IRON && shotIron == 3 ) tile[x][y]->change_type( TILE_BLACK ); // 铁块需要三星坦克才能打掉 
		return true;
	}
	
	return false;
}

//改变子弹状态 
void Bullet::change_status( bool status )
{
	isShot = status;
}

//是否击中了东西。即是否死亡 
bool Bullet::is_shot()const 
{
	return isShot;
}

//获得碰撞盒子 
const SDL_Rect& Bullet::get_box()const 
{
	return box;
}

//保证 x 在游戏界面范围内 
int Bullet::in_bored( int x )const 
{
	if( x < 0 ) x = 0;
	if( x >= TILE_NUM ) x = TILE_NUM - 1;
	return x;
} 
