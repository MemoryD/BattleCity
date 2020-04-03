#include "tank.h"

Move playOne[5] = {{0, -TANK_SPEED, SDLK_w}, {TANK_SPEED, 0, SDLK_d}, {0, TANK_SPEED, SDLK_s}, {-TANK_SPEED, 0, SDLK_a}, {0,0,SDLK_j}};
Move playTwo[5] = {{0, -TANK_SPEED, SDLK_UP}, {TANK_SPEED, 0, SDLK_RIGHT}, {0, TANK_SPEED, SDLK_DOWN}, {-TANK_SPEED, 0, SDLK_LEFT}, {0,0,SDLK_KP0}};

//���캯�� 
Tank::Tank( SDL_Surface *source, Move *m )
{
	born = load_image( "..\\graphics\\bore.bmp", BLACK_KEY);
	shield = load_image( "..\\graphics\\shield.bmp",BLACK_KEY);
	bang = Mix_LoadWAV( "..\\sound\\bang.wav" );
	
	me = source;
	moveTo = m;
	bornTime = BORN_TIME;															// ����ʱ�� 
	box.x = 0;
	box.y = 0;
	box.w = TANK_SIZE;
	box.h = TANK_SIZE;
	bornClip.y = 0;
	bornClip.w = TILE_SIZE << 1;
	bornClip.h = TILE_SIZE << 1;
	isMove = false;
	isDead = true;
	bullet = new Bullet( box, dir );
}

//�Ƿ�ײ��ǽ 
bool Tank::touch_wall( )const 
{
	if( over_bored( box ) )															// �Ƿ񳬳���Ϸ���� 
	{
		return true;
	}
		
	int begin, end, yy;

	if( dir == UP || dir == DOWN)													// ��鴦��̹����ǰ���ĵط��Ƿ����ϰ� 
	{
		begin = box.x / TILE_SIZE;
		end = ( box.x + box.w ) / TILE_SIZE;
		if( dir == UP )
			yy =  box.y / TILE_SIZE;
		else 
			yy = ( box.y + box.h ) / TILE_SIZE;
			
		for(int i = begin; i <= end; i++)
		{
			int t = tile[yy][i]->get_type();
			if( t != TILE_BLACK && t != TILE_LAWN ) return true;
		}
	}
	else
	{
		begin = box.y / TILE_SIZE;
		end = ( box.y + box.h ) / TILE_SIZE;
		if( dir == LEFT )
			yy = box.x / TILE_SIZE;
		else
			yy = ( box.x + box.w ) / TILE_SIZE;
		for(int i = begin; i <= end; i++)
		{
			int t = tile[i][yy]->get_type();
			if( t != TILE_BLACK && t != TILE_LAWN ) return true;
		}
	}
		
    return false;
}

// �Ƿ�ײ��̹�� 
bool Tank::touch_tank( Tank **tank,int num ) const
{
	for(int i = 0; i < TANK_TWO_NUM; i++)											// ��̹����һ������ײ��� 
	{
																					// �������Լ���̹��δ�� 
		if( i != num && !tank[i]->is_dead( false ) && check_touch( box, tank[i]->get_box() ))
		{
			return true;
		}
	}
	
	return false;
}

// �Ƿ����̹�ˣ�  
int Tank::hit_in(Tank **tank, int num)const
{
	Thing hit = NOTHING;
	int who = -1;
	int begin, end;
																					// �Ѿ����ụ���˺� 
	if( num < 2 )																	// ������̹�ˣ���Ե�̹�˽��м�� 
	{
		begin = 2;
		end = TANK_TWO_NUM;
	}
	else																			// ���ǵ�̹�ˣ������̹�˽��м�� 
	{
		begin = 0;
		end = 2;
	}
	
	for(int i = begin; i < end; i++)
	{
		if( !bullet->is_shot() && !tank[i]->is_dead( false ) && i != num )
		{
			if( !tank[i]->is_born() && check_touch(bullet->get_box(), tank[i]->get_box()) ) //������ 
			{
				change_bullet( true );												// �ı��ӵ���״̬ 
				
				if( i < 2 )															// ��������̹�� 
				{
					if( !tank[i]->is_shield() && tank[i]->is_dead( true ) )			// ����Ƿ��б����� 
					{
						hit = TANK;
						who = i;
						Mix_PlayChannel(-1, bang, 0);
					}
					break;
				} 
				else 																// �����е�̹�ˣ�����Ƿ����� 
				{
					who = i;
					if( tank[i]->is_dead( true ) )
					{
						hit = TANK;
						if( num < 2 ) Mix_PlayChannel(-1, bang, 0);
					}
				}
				break;
			}
																					// ����ӵ��Ƿ��໥��������һ�����ʻ���� 
			if( !tank[i]->bullet_status() && check_touch(bullet->get_box(), tank[i]->get_bullet() ))
			{
				hit = BULLET;
				tank[i]->change_bullet( true );
				break;
			}
		}
	}
	
	bullet->will_hit( hit );
	
	return who;
} 

// �ƶ������뷽����ٶ� 
void Tank::do_move( int s, int d )
{
	box.x += s * moveTo[d].x;
	box.y += s * moveTo[d].y;
}

// �����ƶ������뷽����ٶ�
void Tank::un_move( int s, int d )
{
	box.x -= s * moveTo[d].x;
	box.y -= s * moveTo[d].y;
}

//�����ӵ��������ٶȺ��Ƿ��ܴ��� 
void Tank::attack( int sp, int iron )const
{
	if( bullet->is_shot() )
		bullet->reset( box, dir, false, iron, sp );
}

//������ײ���� 
const SDL_Rect& Tank::get_box()const
{
	return box;
}

//�����ӵ�����ײ���� 
const SDL_Rect& Tank::get_bullet()const
{
	return bullet->get_box();
}

//�����ӵ���״̬ 
bool Tank::bullet_status()const 
{
	return bullet->is_shot();
}

//�ı��ӵ���״̬ 
void Tank::change_bullet(bool status)const 
{
	bullet->change_status( status );
}

//�Ƿ����ڳ��� 
bool Tank::is_born()const 
{
	return bornTime > 0;
}

//������̹��λ�ã�ʹ���õ����С���δ�Ե�̹��ʹ�� 
bool Tank::adjust()
{
	if( dir == UP || dir == DOWN )
	{
		for(int i = -6; i <= 6; i += 2)
		{
			box.x += i;
			if( !touch_wall() )
			{
				return true;
			}
			box.x -= i;
		}
	}
	else
	{
		for(int i = -6; i <= 6; i += 2)
		{
			box.y += i;
			if( !touch_wall() )
			{
				return true;
			}
			box.y -= i;
		}
	}
}

//��̹����Ϊ���� 
void Tank::die()
{
	isDead = true;
}

/****************************************Main Tank*************************************/

//���캯�� 
MainTank::MainTank( SDL_Surface *source, Move *m ):Tank( source, m )
{
	fire = Mix_LoadWAV( "..\\sound\\fire.wav" );
	
	shieldTime = INIT_SHIELD_TIME;													// ��ʼ������ʱ�� 
	star = 0;																		// ��ʼ�Ǽ�Ϊ 0 
	dir = UP;																		// ��ʼ�������� 
	
	for(int i = 0; i < 4; i++)														// ���� 
	{
		for(int j = 0; j < 4; j++)
		{
			clip[i][j].x = 2 * i * TANK_SIZE;
			clip[i][j].y = j * TANK_SIZE;
			clip[i][j].w = TANK_SIZE;
			clip[i][j].h = TANK_SIZE;
		}
	}
}
//����,�ͷű������Ч 
MainTank::~MainTank()
{
	SDL_FreeSurface( born );
	SDL_FreeSurface( shield );
	Mix_FreeChunk( fire );
	Mix_FreeChunk( bang );
}

//̹���ƶ� 
void MainTank::move( Tank **tank,int num  )
{	
	if( isDead ) return;															// ���Ѿ����������ƶ� 
	
	bullet->move();																	// �ӵ��ƶ� 
	
	if(isMove && bornTime < 0)														// �������ƶ��Ҳ����ڳ��� 
	{
		speed = star + 4;															// �����ٶ� 
		
		for( int i = 1; i <= speed; i++)											// һ�����ߣ�ֱ�������ײǽ 
		{	
			do_move( 1, dir );
			
			if( touch_tank( tank, num ))											// ������̹�ˣ��򳷻� 
			{
				un_move( 1, dir );
				return;
			}
			if( touch_wall() )														// ��û������̹�ˣ���������ǽ 
			{
				if( !adjust() )														// ����̹��λ�� 
				{
					un_move( 1, dir );												// ����������ײǽ���򳷻� 
					return;
				}
			}
		}
	} 
}

//��ʾ̹�� 
void MainTank::show()
{	
	if( isDead ) return;															// ���Ѿ�����������ʾ 
	
	if(bornTime >= 0)																// �����ڳ��� 
	{
		bornClip.x = 32 * (4 - (bornTime + 4) / 5);
		SDL_BlitSurface( born, &bornClip, screen, &box );							// ��ʾ���� 
		bornTime--;
	}
	else																			// ���� 
	{
		if(shieldTime >= 0)															// ���б����� 
		{
			bornClip.x = 0;
			bornClip.y = ( shieldTime % 2 ) * 32;
			SDL_Rect temp;
			temp.x = box.x - 2;
			temp.y = box.y - 2;
			temp.w = 2 * TILE_SIZE;
			temp.h = 2 * TILE_SIZE;
			SDL_BlitSurface( shield, &bornClip, screen, &temp );					// ��ʾ������ 
			shieldTime--;
		}
		bullet->show();																// ��ʾ�ӵ� 
		SDL_BlitSurface( me, &clip[star][dir], screen, &box );						// ��ʾ̹�� 
	}
		
}

//�������� 
void MainTank::handle_input( const SDL_Event &event )
{
	if( isDead ) return;															// ���������򲻴��� 
	
	for(int i = 0; i <= 4; i++)
	{
		if( moveTo[i].key == event.key.keysym.sym )
		{
			if( i < 4 )
			{
				if( event.type == SDL_KEYDOWN )										// ���·���� 
				{
					dir = i;														// ����ı� 
					isMove = true;
				}
				else if( event.type == SDL_KEYUP )									// �ɿ����˶�ֹͣ 
				{
	    			isMove = false;
				}
			}
			else if( bullet->is_shot() && event.type == SDL_KEYDOWN && 4 == i )		// ���¹����� 
			{
				attack( star + 2 , star );											// ���� 
				Mix_PlayChannel(-1, fire, 0);
			}
		}
	}
}

//���ӽ��� 
void MainTank::add_bonus( int t )
{
	if( t == BONUS_STAR )
	{
		if( star < 3 ) star++;
	}
	else if( t == BONUS_SHIELD )
	{
		shieldTime = BONUS_TIME;
	}
}

//�Ƿ��б����� 
bool MainTank::is_shield()const 
{
	return shieldTime >= 0;
}

//���� 
void MainTank::reset(int x, int y)
{
	box.x = x;
	box.y = y;
	isDead = false;
	bornTime = BORN_TIME;
	isMove = false;
	shieldTime = INIT_SHIELD_TIME;
	dir = UP;
}

//�Ƿ�������������Ϊ true�� �򷵻ر�����һ�º��Ƿ����� 
bool MainTank::is_dead( bool shot )
{
	if( shot )
	{
		if( star == 3 )
		{
			--star;
			return false;
		}
		else
		{
			star = 0;
			isDead = true;
			return true;
		}
	}
	return isDead;
}

/*******************************************Enemy Tank*****************************/

//���캯�� 
EnemyTank::EnemyTank(SDL_Surface *source, Move *m ):Tank(source, m)
{
	reset(2, 2);
}

//���� 
EnemyTank::~EnemyTank()
{
	SDL_FreeSurface( born );
	SDL_FreeSurface( shield );
	Mix_FreeChunk( bang );
}

//���ã����в��������� 
void EnemyTank::reset(int x, int y)
{
	box.x = x;
	box.y = y;
	box.w = TANK_SIZE;
	box.h = TANK_SIZE;
	isDead = false;
	bornTime = BORN_TIME;
	isMove = false;
	dir = DOWN;															
	type = random( 0, 2 );															// ������� 
	blood = 1;
	speed = ENEMY_SLOW_SPEED;
	if( type == 2 )																	// ��Ϊ����̹�ˣ�Ѫ����� 
	{
		blood = random( 1, 3 ); 
	}
	if( type == 1 )																	// �쳵���ٶȼӿ� 
	{
		speed = ENEMY_FAST_SPEED;
	}
	if( random( 0, 3) == 0 )														// һ���Ŀ���Ϊ�쳵 
	{
		red = true;
		redTime = 5;
	}
	else
	{
		red = false;
		redTime = -1;
	}
	for(int i = 0; i < 4; i++)														// �������ͼ���ͼƬ 
	{
		if( type < 2 )
		{
			clip[1][i].x = ( 4 * type ) * TANK_SIZE;
			clip[1][i].y = i * TANK_SIZE;
			clip[1][i].w = TANK_SIZE;
			clip[1][i].h = TANK_SIZE;
			clip[0][i].x = ( 4 * type + 2 ) * TANK_SIZE;
			clip[0][i].y = i * TANK_SIZE;
			clip[0][i].w = TANK_SIZE;
			clip[0][i].h = TANK_SIZE;
		}
		else if( type = 2 )
		{
			for(int j = 0; j < 4; j++)
			{
				clip[j][i].x =  2 * ( 4 - j - 1 ) * TANK_SIZE;
				clip[j][i].y = ( i + 4 ) * TANK_SIZE;
				clip[j][i].w = TANK_SIZE;
				clip[j][i].h = TANK_SIZE;
			}
		}
	}
}

//̹���ƶ�������˶� 
void EnemyTank::move( Tank** tank, int num )
{
	bullet->move();
	
	if( bornTime > 0 || isDead ) return;											// �����ڳ��������Ѿ����������ƶ� 
	
	int d =  random(-12, 3);														// ��һ���ļ��ʸı䷽�� 
	
	if( d < -10 )																	// ���µĸ��ʸ��� 
		d = DOWN;
		
	if( box.y > 350 && random(0, 4) == 0 )
	{
		if( box.x < 190 )
		{
			d = RIGHT;
		}
		else
		{
			d = LEFT;
		}
	} 
	
	int td = dir;
	
	if( random( 0, 8 ) == 0 ) isMove = false;										// ��һ���ļ���ֹͣ�˶� 
		
	if( d >= 0 && !isMove )
		td = d;
	
	for(int i = 1; i <= speed; i++)													// һ�����˶� 
	{
		do_move( 1, td );
		if( touch_wall() || touch_tank(tank, num) )
		{
			un_move( 1, td );
			isMove = false;
			if( random(0, 5) == 0 )													// ײǽʱ��һ���ļ��ʸı䷽�� 
				dir = random( 0,3 );
			if( random( 0,5 ) == 0 )
				attack();
			return;
		}
		else
		{
			isMove = true;
			dir = td;
		}
	}
}

//��ʾ̹�� 
void EnemyTank::show()
{
	if( blood <= 0 || isDead ) return;												// �����������˶� 
	if(bornTime >= 0)																// �����ڳ�������ʾ���� 
	{
		bornClip.x = 32 * (4 - (bornTime + 4) / 5);
		SDL_BlitSurface( born, &bornClip, screen, &box );
		bornTime--;
	}
	else																			// ���� 
	{
		bullet->show();																// ��ʾ�ӵ� 
		if( red )																	// ����Ǻ쳵����ʾ��ɫ 
		{
			if(redTime > 0)
				SDL_BlitSurface( me, &clip[blood][dir], screen, &box );
			else
				SDL_BlitSurface( me, &clip[0][dir], screen, &box );
			redTime--;
			if( redTime == -5 ) redTime = 5;
		}
		else
			SDL_BlitSurface( me, &clip[blood][dir], screen, &box );
	}
}

//�Ƿ��ɫ��ֻ���ṩһ�β�ѯ����ѯ�����ٺ� 
bool EnemyTank::is_red()
{
	if( red )
	{
		red = false;
		return true;
	}
	return false;
}

//�Ƿ������������� true���򷵻ر�����һ�º��Ƿ����� 
bool EnemyTank::is_dead( bool shot )
{
	if( shot ) 
	{
		--blood;
		if( blood <= 0 ) 
			isDead = true;
	}
	
	return isDead;
}
