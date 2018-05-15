#include "tank.h"

Move playOne[5] = {{0, -TANK_SPEED, SDLK_w}, {TANK_SPEED, 0, SDLK_d}, {0, TANK_SPEED, SDLK_s}, {-TANK_SPEED, 0, SDLK_a}, {0,0,SDLK_j}};
Move playTwo[5] = {{0, -TANK_SPEED, SDLK_UP}, {TANK_SPEED, 0, SDLK_RIGHT}, {0, TANK_SPEED, SDLK_DOWN}, {-TANK_SPEED, 0, SDLK_LEFT}, {0,0,SDLK_KP0}};

//构造函数 
Tank::Tank( SDL_Surface *source, Move *m )
{
	born = load_image( "graphics\\bore.bmp", BLACK_KEY);
	shield = load_image( "graphics\\shield.bmp",BLACK_KEY);
	bang = Mix_LoadWAV( "sound\\bang.wav" );
	
	me = source;
	moveTo = m;
	bornTime = BORN_TIME;															// 出生时间 
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

//是否撞到墙 
bool Tank::touch_wall( )const 
{
	if( over_bored( box ) )															// 是否超出游戏界面 
	{
		return true;
	}
		
	int begin, end, yy;

	if( dir == UP || dir == DOWN)													// 检查处在坦克正前方的地方是否有障碍 
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

// 是否撞到坦克 
bool Tank::touch_tank( Tank **tank,int num ) const
{
	for(int i = 0; i < TANK_TWO_NUM; i++)											// 对坦克逐一进行碰撞检测 
	{
																					// 若不是自己且坦克未死 
		if( i != num && !tank[i]->is_dead( false ) && check_touch( box, tank[i]->get_box() ))
		{
			return true;
		}
	}
	
	return false;
}

// 是否击中坦克，  
int Tank::hit_in(Tank **tank, int num)const
{
	Thing hit = NOTHING;
	int who = -1;
	int begin, end;
																					// 友军不会互相伤害 
	if( num < 2 )																	// 若是主坦克，则对敌坦克进行检测 
	{
		begin = 2;
		end = TANK_TWO_NUM;
	}
	else																			// 若是敌坦克，则对主坦克进行检测 
	{
		begin = 0;
		end = 2;
	}
	
	for(int i = begin; i < end; i++)
	{
		if( !bullet->is_shot() && !tank[i]->is_dead( false ) && i != num )
		{
			if( !tank[i]->is_born() && check_touch(bullet->get_box(), tank[i]->get_box()) ) //若击中 
			{
				change_bullet( true );												// 改变子弹的状态 
				
				if( i < 2 )															// 若击中主坦克 
				{
					if( !tank[i]->is_shield() && tank[i]->is_dead( true ) )			// 检查是否有保护罩 
					{
						hit = TANK;
						who = i;
						Mix_PlayChannel(-1, bang, 0);
					}
					break;
				} 
				else 																// 若击中敌坦克，检测是否死亡 
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
																					// 检测子弹是否相互抵消，有一定几率会抵消 
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

// 移动，传入方向和速度 
void Tank::do_move( int s, int d )
{
	box.x += s * moveTo[d].x;
	box.y += s * moveTo[d].y;
}

// 撤销移动，传入方向和速度
void Tank::un_move( int s, int d )
{
	box.x -= s * moveTo[d].x;
	box.y -= s * moveTo[d].y;
}

//发射子弹，传入速度和是否能打铁 
void Tank::attack( int sp, int iron )const
{
	if( bullet->is_shot() )
		bullet->reset( box, dir, false, iron, sp );
}

//返回碰撞盒子 
const SDL_Rect& Tank::get_box()const
{
	return box;
}

//返回子弹的碰撞盒子 
const SDL_Rect& Tank::get_bullet()const
{
	return bullet->get_box();
}

//返回子弹的状态 
bool Tank::bullet_status()const 
{
	return bullet->is_shot();
}

//改变子弹的状态 
void Tank::change_bullet(bool status)const 
{
	bullet->change_status( status );
}

//是否正在出生 
bool Tank::is_born()const 
{
	return bornTime > 0;
}

//调整主坦克位置，使更好的钻进小缝里，未对敌坦克使用 
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

//将坦克置为死亡 
void Tank::die()
{
	isDead = true;
}

/****************************************Main Tank*************************************/

//构造函数 
MainTank::MainTank( SDL_Surface *source, Move *m ):Tank( source, m )
{
	fire = Mix_LoadWAV( "sound\\fire.wav" );
	
	shieldTime = INIT_SHIELD_TIME;													// 初始保护罩时间 
	star = 0;																		// 初始星级为 0 
	dir = UP;																		// 初始方向向上 
	
	for(int i = 0; i < 4; i++)														// 剪切 
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
//析构,释放表面和音效 
MainTank::~MainTank()
{
	SDL_FreeSurface( born );
	SDL_FreeSurface( shield );
	Mix_FreeChunk( fire );
	Mix_FreeChunk( bang );
}

//坦克移动 
void MainTank::move( Tank **tank,int num  )
{	
	if( isDead ) return;															// 若已经死亡，则不移动 
	
	bullet->move();																	// 子弹移动 
	
	if(isMove && bornTime < 0)														// 若正在移动且不是在出生 
	{
		speed = star + 4;															// 重置速度 
		
		for( int i = 1; i <= speed; i++)											// 一步步走，直到走完或撞墙 
		{	
			do_move( 1, dir );
			
			if( touch_tank( tank, num ))											// 若碰到坦克，则撤回 
			{
				un_move( 1, dir );
				return;
			}
			if( touch_wall() )														// 若没有碰到坦克，但是碰到墙 
			{
				if( !adjust() )														// 调整坦克位置 
				{
					un_move( 1, dir );												// 若调整后还是撞墙，则撤回 
					return;
				}
			}
		}
	} 
}

//显示坦克 
void MainTank::show()
{	
	if( isDead ) return;															// 若已经死亡，则不显示 
	
	if(bornTime >= 0)																// 若正在出生 
	{
		bornClip.x = 32 * (4 - (bornTime + 4) / 5);
		SDL_BlitSurface( born, &bornClip, screen, &box );							// 显示星星 
		bornTime--;
	}
	else																			// 否则 
	{
		if(shieldTime >= 0)															// 若有保护罩 
		{
			bornClip.x = 0;
			bornClip.y = ( shieldTime % 2 ) * 32;
			SDL_Rect temp;
			temp.x = box.x - 2;
			temp.y = box.y - 2;
			temp.w = 2 * TILE_SIZE;
			temp.h = 2 * TILE_SIZE;
			SDL_BlitSurface( shield, &bornClip, screen, &temp );					// 显示保护罩 
			shieldTime--;
		}
		bullet->show();																// 显示子弹 
		SDL_BlitSurface( me, &clip[star][dir], screen, &box );						// 显示坦克 
	}
		
}

//处理输入 
void MainTank::handle_input( const SDL_Event &event )
{
	if( isDead ) return;															// 若死亡，则不处理 
	
	for(int i = 0; i <= 4; i++)
	{
		if( moveTo[i].key == event.key.keysym.sym )
		{
			if( i < 4 )
			{
				if( event.type == SDL_KEYDOWN )										// 按下方向键 
				{
					dir = i;														// 方向改变 
					isMove = true;
				}
				else if( event.type == SDL_KEYUP )									// 松开，运动停止 
				{
	    			isMove = false;
				}
			}
			else if( bullet->is_shot() && event.type == SDL_KEYDOWN && 4 == i )		// 按下攻击键 
			{
				attack( star + 2 , star );											// 攻击 
				Mix_PlayChannel(-1, fire, 0);
			}
		}
	}
}

//增加奖励 
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

//是否有保护罩 
bool MainTank::is_shield()const 
{
	return shieldTime >= 0;
}

//重置 
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

//是否死亡，若参数为 true， 则返回被击中一下后是否死亡 
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

//构造函数 
EnemyTank::EnemyTank(SDL_Surface *source, Move *m ):Tank(source, m)
{
	reset(2, 2);
}

//析构 
EnemyTank::~EnemyTank()
{
	SDL_FreeSurface( born );
	SDL_FreeSurface( shield );
	Mix_FreeChunk( bang );
}

//重置，所有参数都重置 
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
	type = random( 0, 2 );															// 类型随机 
	blood = 1;
	speed = ENEMY_SLOW_SPEED;
	if( type == 2 )																	// 若为重型坦克，血量随机 
	{
		blood = random( 1, 3 ); 
	}
	if( type == 1 )																	// 快车的速度加快 
	{
		speed = ENEMY_FAST_SPEED;
	}
	if( random( 0, 3) == 0 )														// 一定的慨率为红车 
	{
		red = true;
		redTime = 5;
	}
	else
	{
		red = false;
		redTime = -1;
	}
	for(int i = 0; i < 4; i++)														// 根据类型剪切图片 
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

//坦克移动，随机运动 
void EnemyTank::move( Tank** tank, int num )
{
	bullet->move();
	
	if( bornTime > 0 || isDead ) return;											// 若正在出生或者已经死亡，则不移动 
	
	int d =  random(-12, 3);														// 有一定的几率改变方向 
	
	if( d < -10 )																	// 向下的概率更大 
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
	
	if( random( 0, 8 ) == 0 ) isMove = false;										// 有一定的几率停止运动 
		
	if( d >= 0 && !isMove )
		td = d;
	
	for(int i = 1; i <= speed; i++)													// 一步步运动 
	{
		do_move( 1, td );
		if( touch_wall() || touch_tank(tank, num) )
		{
			un_move( 1, td );
			isMove = false;
			if( random(0, 5) == 0 )													// 撞墙时有一定的几率改变方向 
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

//显示坦克 
void EnemyTank::show()
{
	if( blood <= 0 || isDead ) return;												// 若死亡，则不运动 
	if(bornTime >= 0)																// 若正在出生则显示星星 
	{
		bornClip.x = 32 * (4 - (bornTime + 4) / 5);
		SDL_BlitSurface( born, &bornClip, screen, &box );
		bornTime--;
	}
	else																			// 否则 
	{
		bullet->show();																// 显示子弹 
		if( red )																	// 如果是红车，显示红色 
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

//是否红色，只能提供一次查询，查询完则不再红 
bool EnemyTank::is_red()
{
	if( red )
	{
		red = false;
		return true;
	}
	return false;
}

//是否死亡，若传入 true，则返回被打中一下后是否死亡 
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
