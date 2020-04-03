#include "bullet.h"

Move bulletTo[4] = {{0, -BULLET_SPEED, UP}, {BULLET_SPEED, 0, RIGHT}, {0, BULLET_SPEED, DOWN}, {-BULLET_SPEED, 0, LEFT}};

//���캯�� 
Bullet::Bullet( const SDL_Rect &b, int d )
{
	myself = load_image( "..\\graphics\\bullet.bmp",BLACK_KEY );
	explode1 = load_image( "..\\graphics\\explode1.bmp" );
	explode2 = load_image( "..\\graphics\\explode2.bmp" ,BLACK_KEY);
	hit = Mix_LoadWAV( "..\\sound\\hit.wav" );
	
	speed = 2;																	// Ĭ���ٶ�Ϊ 2 
	isShot = true;																// �չ���ʱĬ�ϲ���ʾ 
	shotIron = false;															// Ĭ�ϲ��ܴ��� 
	bombTime = 0;																//  
	box.w = BULLET_SIZE + 2;
	box.h = BULLET_SIZE + 2;
	
	reset( b, d , true);														// ����һЩ���� 
	
	clip[0].x = 0;																// ����ͼƬ���� 
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

//���� 
Bullet::~Bullet()
{
	SDL_FreeSurface( myself );
	SDL_FreeSurface( explode1 );
	SDL_FreeSurface( explode2 );
	Mix_FreeChunk( hit );
}

//����λ�ã����� λ�ã������Ƿ���ʾ���Ƿ��ܴ������Լ��ٶ� 
void Bullet::reset( const SDL_Rect &b, int d, bool s, int iron, int sp )
{
	isShot = s;
	dir =  d;
	thing = NOTHING;
	speed = sp;
	shotIron = iron;
	switch( d )																	//����λ�úͷ������λ�� 
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

//��ײ��⣬�Ƿ�ײǽ 
bool Bullet::collision()
{	
	bool flag = false;
	int x, y, begin, end;

	switch( dir )																// ���ݷ���ѡ�񷽰� 
	{																			// ���� �ƶ�ǰλ�õ��ƶ���λ�� ֮������� 
		case UP:{																// ����Ƿ����ϰ������У�������ֹͣ 
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
	
	if( over_bored( box ) )														// �Ƿ�Խ�� 
	{																			// ���ǣ����˻�����ʾ��ըЧ�� 
		box.x -= speed * bulletTo[dir].x >> 1 ;
		box.y -= speed * bulletTo[dir].y >> 1;
		if( shotIron >= 0 )														// ������̹�˵��ӵ�ײǽ���򲥷���Ч 
				Mix_PlayChannel( -1, hit, 0);
		return true;
	}
	
	return false;
}

// ���뼴�����еĶ���������ʾ��Ӧ��Ч�� 
bool Bullet::will_hit(Thing hit)
{
	if( hit == TANK )															// ������̹�ˣ���ʾ��ըЧ�� 
	{
		bombTime = 4;
		bbox.x = box.x - 10;
		bbox.y = box.y - 10;
		thing = TANK;
		isShot = true;
	}
	else if( hit == BULLET )													// ���ӵ����� 
	{
		isShot = true;
	}
}

//�ӵ��ƶ� 
void Bullet::move()
{
	if( !isShot )																// ������������ʾ 
	{
		box.x += speed * bulletTo[dir].x;
		box.y += speed * bulletTo[dir].y;
		if( collision() ) 														// ײǽ������ʾ��ըЧ�� 
		{
			bombTime = 3;
			thing = WALL;
			isShot = true;
			return;
		}
	}
}

// ��ʾ�ӵ� 
void Bullet::show()
{
	if(!isShot)																	// ��ʾ�ӵ����� 
		SDL_BlitSurface( myself, &clip[dir], screen, &box );
		
	if( thing ==  WALL )														// ��ʾ��ըЧ�� 
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

//�Ƿ�����ϰ� 
bool Bullet::hit_tile(int x, int y)const 
{
	int t = tile[x][y]->get_type();
	if( t == TILE_BRICK || t == TILE_IRON )
	{
		if( t == TILE_BRICK ) tile[x][y]->change_type( TILE_BLACK );			// ש�����ֱ�Ӵ�� 
		if( t == TILE_IRON && shotIron == 3 ) tile[x][y]->change_type( TILE_BLACK ); // ������Ҫ����̹�˲��ܴ�� 
		return true;
	}
	
	return false;
}

//�ı��ӵ�״̬ 
void Bullet::change_status( bool status )
{
	isShot = status;
}

//�Ƿ�����˶��������Ƿ����� 
bool Bullet::is_shot()const 
{
	return isShot;
}

//�����ײ���� 
const SDL_Rect& Bullet::get_box()const 
{
	return box;
}

//��֤ x ����Ϸ���淶Χ�� 
int Bullet::in_bored( int x )const 
{
	if( x < 0 ) x = 0;
	if( x >= TILE_NUM ) x = TILE_NUM - 1;
	return x;
} 
