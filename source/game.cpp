#include "game.h"

//文件载入以及各种变量初始化 
MyGame::MyGame()
{
	load_files();
	all_clip();
	
	tank[0] = new MainTank(p1, playOne);										// player1 的坦克 
	tank[1] = new MainTank(p2, playTwo);										// player2 的坦克 
	for(int i = 2; i < TANK_TWO_NUM; i++)										// 敌坦克初始化
	{
		tank[i] = new EnemyTank(enemy, playOne);
	}
	
	level = 0;																	// 初始关卡
	life_1 = 10;																// player1 的生命 
	life_2 = 10;																// player2 的生命 
	end = false;																// 未结束 
	tankNum = TANK_TWO_NUM;														// 默认为双人模式，后期选择再修改 
	
	num_init();																	// 变量初始化 
	
	tank_init();																// 坦克初始化 
}


//各种文件的载入 
void MyGame::load_files()
{
	p1 = load_image( "..\\graphics\\player1.bmp" );
	p2 = load_image( "..\\graphics\\player2.bmp" );
	enemy = load_image( "..\\graphics\\enemy.bmp", BLACK_KEY );
	misc = load_image( "..\\graphics\\misc.bmp", WHITE_KEY );
	bg = load_image( "..\\graphics\\bg.png" );
	num = load_image( "..\\graphics\\num.bmp", WHITE_KEY);
	flag = load_image( "..\\graphics\\flag.bmp", WHITE_KEY);
	home = load_image( "..\\graphics\\tile.bmp" );
	over = load_image( "..\\graphics\\gg.png" );
	pase = load_image( "..\\graphics\\Pause.png" );
	splash = load_image( "..\\graphics\\splash.bmp" );
	explain = load_image( "..\\graphics\\shuoming.png" );
	declare = load_image( "..\\graphics\\declare.png" ); 
	st = load_image( "..\\graphics\\Stage.png", WHITE_KEY);
	choose = load_image( "..\\graphics\\player1.bmp" );
	brand = load_image( "..\\graphics\\brand.png" );
	gg = load_image( "..\\graphics\\gameover.bmp" );
	bomb1 = load_image( "..\\graphics\\explode1.bmp");
	bomb2 = load_image( "..\\graphics\\explode2.bmp");
	bom =  Mix_LoadWAV( "..\\sound\\bang.wav" );
	music = Mix_LoadMUS( "..\\sound\\start.wav" );
	peow = Mix_LoadWAV( "..\\sound\\Peow.wav" );
				
	int x = 0;
	for(char i = '0'; i < TOTAL_STAGE / 10 + '0'; i++)							// 初始化地图文件名 
	{
		for(char j = '0'; j <= '9'; j++)
		{
			stage[x] += "..\\map\\level";
			stage[x] += i;
			stage[x] += j;
			stage[x] += ".map";
			x++;
		}
	}
}

//图片裁剪区域初始化 
void MyGame::all_clip()
{
	chooseClip.x = 0;
	chooseClip.y = TANK_SIZE;
	chooseClip.w = TANK_SIZE;
	chooseClip.h = TANK_SIZE;

	homeBox.x = 6 * TILE_SIZE << 1;
	homeBox.y = 12 * TILE_SIZE << 1;
	homeBox.w = TILE_SIZE << 1;
	homeBox.h = TILE_SIZE << 1;
	
	for(int i = 0; i < 10; i++)
	{
		if( i < 6 )
		{
			miscClip[i].x = i * MISC_SIZE;
			miscClip[i].y = 0;
			miscClip[i].w = MISC_SIZE;
			miscClip[i].h = MISC_SIZE;
		}
		
		if( i == 5 || i == 6 )
		{
			homeClip[i - 5].x = i * TILE_SIZE << 1;
			homeClip[i - 5].y = 0;
			homeClip[i - 5].w = TILE_SIZE << 1;
			homeClip[i - 5].h = TILE_SIZE << 1;
		}
		
		numClip[i].x = i * NUM_SIZE;
		numClip[i].y = 0;
		numClip[i].w = NUM_SIZE;
		numClip[i].h = NUM_SIZE;
	}
}


//坦克初始化，主坦克置于初始位置，敌坦克全部置于死亡 
void MyGame::tank_init()const 
{
	if( life_1 > 0 )
		tank[0]->reset(PLAY1_START_X, PLAY1_START_Y);								// 主坦克位置初始化 
	if( life_2 > 0 )
		tank[1]->reset(PLAY2_START_X, PLAY2_START_Y);								// 
	
	for(int i = 2; i < tankNum; i++)												// 敌坦克初始化，全部为死亡状态 
	{
		tank[i]->die();
	}
}

//数值初始化 
void MyGame::num_init()
{
	level++;																		// 关卡加一 
	enemyNum = ENEMY_TOTAL_NUM;														// 关卡的敌人总数															// 
	killNum = 0;																	// 击杀的敌人数量  
	pause = false;																	// 
	endTime = TIME_TO_END;															// 游戏结束的缓冲时间 
	timeStop = -1;																	// 时间暂停的奖励时间 
	bonusShowTime = -1;																// 奖励显示的剩余时间 
	homeTime = -1;																	// 总部变铁的剩余时间 
	bonus.change( false );															// 是否显示奖励 
	read_map( stage[level % TOTAL_STAGE] );											// 读取地图 
}

//析构函数，释放坦克和表面 
MyGame::~MyGame()
{
	for(int i = 0; i < TANK_TWO_NUM; i++)
	{
		delete tank[i];
	} 
	
	SDL_FreeSurface( p1 );
	SDL_FreeSurface( p2 );
	SDL_FreeSurface( enemy );
	SDL_FreeSurface( misc );
	SDL_FreeSurface( bg );
	SDL_FreeSurface( num );
	SDL_FreeSurface( flag );
	SDL_FreeSurface( home );
	SDL_FreeSurface( over );
	SDL_FreeSurface( pase );
	SDL_FreeSurface( splash );
	SDL_FreeSurface( explain );
	SDL_FreeSurface( declare );
	SDL_FreeSurface( st );
	SDL_FreeSurface( choose );
	SDL_FreeSurface( brand );
	SDL_FreeSurface( gg );
	SDL_FreeSurface( bomb1 );
	SDL_FreeSurface( bomb2 );
	
	Mix_FreeChunk( bom );
	Mix_FreeChunk( peow );
	Mix_FreeMusic( music );
}

//显示游戏初始选择画面 
bool MyGame::show_splash()
{			
	int y = ONE_PLAYER;
	int sy = 319;
	SDL_Event event;
	bool enter = false;																//是否进入了游戏 
	bool press = false;																//是否按了有效按键 
	bool mouse = false;
	
	while( !enter )																	//当没有进入游戏 
	{ 
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );	//背景置黑色
		apply_surface(62, 97 + sy, splash, screen);									//显示界面，没按下之前为滚动 
		if( press || sy <= 0 )														//若按了有效按键，显示选择图标和作者 
		{
			apply_surface( 0, 0, explain, screen);
			apply_surface(150, y, choose, screen, &chooseClip);						//选择图标 
			apply_surface( 87, 340, brand, screen );								//作者 
			if( mouse )
				 apply_surface( 0, 30, declare, screen);							// 显示游戏说明 
		}
		
		if( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_KEYDOWN )
			{
				if( event.key.keysym.sym == SDLK_f )								//按下 F 
				{
					if( !press )													//固定显示 
					{
						press = true;
						sy = 0;
					}
					else if( y == ONE_PLAYER )										//改变选择图标的位置 
						y = TWO_PLAYER;
					else 
						y = ONE_PLAYER;
				}
				if( event.key.keysym.sym == SDLK_h )								//按下 H 
				{
					if( !press )													//固定显示 
					{
						press = true;
						sy = 0;
					}
					else 
					{
						if( y == ONE_PLAYER )										//若为单人模式 
						{
							tank[1]->die();											// player2 置于死亡状态 
							life_2 = -1;											// 生命置为负数 
							tankNum = TANK_ONE_NUM;									// 改变坦克总数 
						}	
						enter = true;												// 进入游戏 
					} 
				}	
			}
			else if( event.type == SDL_QUIT )											//若叉掉窗口，退出循环， 进入游戏失败 
			{
				end = true;
				return false;
			}
			else if( event.type == SDL_MOUSEMOTION )
			{
				int x = event.motion.x;
        		int y = event.motion.y;
        		if( ( x >= 0 ) && ( x < explain->w ) && ( y >= 0 ) && ( y < explain->h ) )
		        {
		        	mouse = true;   
		        }
		        else
		        {
		        	mouse = false;
				}
			}
		}
		if( !press && sy >= 0 )														//湖面滚动的变量 
			sy--;
		if( sy <= 0 )
			press = true;
			
		SDL_Flip( screen );															//刷新画面 
		SDL_Delay( 6 );																//延迟，控制滚动速度 
	}
	
	show_stage();																	//显示关卡 
	Mix_PlayMusic( music, 1 );														//播放开场音乐 
	
	return true;
}


//显示游戏画面 
void MyGame::show_game()
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) ); // 背景置为黑色 
	
	for(int i = 0; i < tankNum; i++)												
	{
		if( !tank[i]->is_dead( false ) )											// 若坦克非死亡 
			tank[i]->show();														// 则显示 
	}
	
	for(int i = 0; i < TILE_NUM; i++)												// 显示障碍 
	{
		for(int j = 0; j < TILE_NUM; j++)
	 	{
	 		tile[i][j]->show();
		}
	}
	
	if( !end )																		// 若游戏还没结束 
	{
		SDL_BlitSurface( home, &homeClip[0], screen, &homeBox );					// 显示总部 
	}
	else																			// 否则 
	{																				// 滚动显示 GAME OVER 
		if( endTime > 80 )
			apply_surface( 162, endTime * 2, over, screen);
		else
			apply_surface( 162, 160, over, screen);
			
		SDL_BlitSurface( home, &homeClip[1], screen, &homeBox );					// 显示被打坏的总部 
	}
	
	if(bonusShowTime > 0)															// 如果有奖励 
	{
		bonus.show();																// 显示奖励 
		bonusShowTime--;															// 奖励时间减少 
	}
}

//显示侧边栏 
void MyGame::show_other()
{
	SDL_Rect set;
	set.x = 440;
	set.y = 10;
	
	apply_surface(416, 0, bg, screen);												// 侧边的背景图 
	
	for(int i = 0; i < enemyNum; i++)												// 显示剩余的敌坦克数 
	{
		if( i % 2 == 0 )
		{
			set.y += 16;
			set.x = 440;
		}
		else
		{
			set.x += 16;
		}
		
		SDL_BlitSurface( misc, &miscClip[0], screen, &set);
	}
	
	set.x = 440;																	// 显示 player1 剩余的生命 
	set.y = 230;
	
	SDL_BlitSurface( misc, &miscClip[2], screen, &set);
	set.x += 16;
	SDL_BlitSurface( misc, &miscClip[3], screen, &set);
	
	set.x = 440;
	set.y += 16;
	SDL_BlitSurface( misc, &miscClip[1], screen, &set);
	set.x += 16;
	
	show_num( life_1, set );
	
	if( life_2 >= 0 )																// 显示 player2 剩余的生命
	{
		set.y += 32;
		set.x = 440;
		
		SDL_BlitSurface( misc, &miscClip[4], screen, &set);
		set.x += 16;
		SDL_BlitSurface( misc, &miscClip[5], screen, &set);
		
		set.x = 440;
		set.y += 16;
		SDL_BlitSurface( misc, &miscClip[1], screen, &set);
		set.x += 16;
		
		int t = life_2;
		
		show_num( life_2, set );
	}
	
	set.x = 440;																	// 显示当前的关卡数 
	set.y = 328;
	
	SDL_BlitSurface( flag, NULL, screen, &set);
	
	set.y += 32;
	set.x += 16;
	
	show_num( level, set );  
	
	SDL_Flip( screen );
}

//显示数字，传入要显示的数字和最高位的坐标，最多三位数 
void MyGame::show_num( int x, SDL_Rect &set )
{
	int t = x;
	if(t >= 10)
	{
		if(t >= 100)
		{
			SDL_BlitSurface( num, &numClip[t / 100], screen, &set);
			set.x += 16;
			t %= 100;
		}
		SDL_BlitSurface( num, &numClip[t / 10], screen, &set);
		set.x += 16;
		t %= 10; 
	}
	SDL_BlitSurface( num, &numClip[t], screen, &set);
} 
 
//显示结束的画面 
void MyGame::show_end()
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );
	
	apply_surface(126, 128, gg, screen);
	SDL_Flip( screen );
	
	SDL_Delay( 3000 );																// 显示三秒钟 
}

//坦克移动 
void MyGame::tank_move()
{
	for(int i = 0; i < TANK_TWO_NUM; i++)
	{
		if( !tank[i]->is_dead( false ) )											// 若坦克未死亡，则移动 
		{
			if( i >= 2 && timeStop > 0) return;										// 若奖励时间停止，则敌坦克不动 
			tank[i]->move(tank, i);
		}
	}
} 

// 创造坦克 
void MyGame::creat_tank()
{
	if( tank[0]->is_dead( false ) && life_1 > 0 )									// 若玩家坦克死亡且还有生命，则重置位置 
	{
		tank[0]->reset(PLAY1_START_X, PLAY1_START_Y);
		life_1--;
	}
	if( tank[1]->is_dead( false ) && life_2 > 0)
	{
		tank[1]->reset(PLAY2_START_X, PLAY2_START_Y);
		life_2--;
	}
				
	if( enemyNum <= 0 ) return;														// 若没有敌人，则退出 
	
	for(int i = 2; i < tankNum; i++)
	{
		if( tank[i]->is_dead( false ) )												// 若敌人死亡 
		{
			if(!enemyTime.is_started()) enemyTime.start();							// 若计时器未启动， 则启动 
			if( enemyTime.get_ticks() < 2000 ) return;								// 若时间小于 2 秒， 退出 
																					// 否则 
			SDL_Rect set = {0, 2, TANK_SIZE, TANK_SIZE};							 
			
			set.x = offset[rand() % 3];												// 随机选择一个位置 
			
			bool flg = true; 
			int col = set.x / TILE_SIZE;											 
			for(int p = col; p <= col + 1; p++)										// 检查此位置有没有障碍
			{
				for(int q = 0; q <= 1; q++)
				{
					if( tile[q][p]->get_type() != TILE_BLACK ) 
						flg = false;
				}
			}
			
			bool flag = true;
			for(int j = 0; j < TANK_TWO_NUM; j++)									// 检测此位置有没有坦克 
			{
				if( !tank[j]->is_dead( false ) && check_touch( set, tank[j]->get_box() ) )
				{
					flg = false;
					break;
				}
			}
			
			if( !flg ) break;														// 若有障碍或坦克，则退出 
																					// 否则 
			tank[i]->reset( set.x, 2 );												// 生成一辆坦克 
			
			enemyNum--;																// 敌人数量减少 
			enemyTime.stop();														// 定时器停止 
		}		
	}
} 

// 敌人攻击 
void MyGame::enemy_attack()const 
{
	for(int i = 2; i < tankNum; i++)
	{
		if( !tank[i]->is_dead( false ) )											// 若没有死亡，不是正在出生，时间没有暂停 
		{
			if( rand() % ENMEY_ATTACK_TIME == 0 && !tank[i]->is_born() && timeStop <= 0)// 有一定的几率攻击 
			{
				tank[i]->attack();
			}
		}
	}
}

//处理输入 
void MyGame::handle_input(const SDL_Event &event )
{
	if( !tank[0]->is_dead( false ) )												// 若主坦克没有死亡，则处理输入 
		tank[0]->handle_input( event );
	if( !tank[1]->is_dead( false ) )
		tank[1]->handle_input( event );
		
	if( event.type == SDL_QUIT )													// 若叉掉窗口，则游戏结束 
	{
		end = true;
	}
	else if( event.type == SDL_KEYDOWN )
	{
		if( event.key.keysym.sym == SDLK_h )										// 按下 H, 则暂停 
		{
			pause = !pause;
			if( pause )																// 若暂停，显示暂停图片 
			{
				apply_surface( 146, 187, pase, screen );
				SDL_Flip( screen );
			}
		}																			// 以下为金手指 
		else if( event.key.keysym.sym == SDLK_KP7 )									// 按下 7,相当于吃一个星星 
		{
			if( !tank[0]->is_dead( false ))
				tank[0]->add_bonus( BONUS_STAR );
			if( !tank[1]->is_dead( false ))
				tank[1]->add_bonus( BONUS_STAR );
		}
		else if( event.key.keysym.sym == SDLK_KP8 )									// 按下 8,相当于吃了防护罩 
		{
			if( !tank[0]->is_dead( false ))
				tank[0]->add_bonus( BONUS_SHIELD );
			if( !tank[1]->is_dead( false ))
				tank[1]->add_bonus( BONUS_SHIELD );
		}	
	}
}

//检查攻击，哪些坦克被击中
void MyGame::check_attack()
{
	std::queue<int> q;																// 用一条队列保存被击中的坦克 
	for(int i = 0; i < tankNum; i++)
	{
		if( !tank[i]->is_dead( false ) )											// 若坦克未死亡 
		{
			int t = tank[i]->hit_in(tank, i);										// 检查被其击中的坦克,返回-1则未击中
			 
			if( 0 == t || 1 == t )													// 若被击中的是主坦克
			{
				if( tank[t]->is_dead( false ) )										// 死亡 
					q.push(t);														// 则入队 
			}
			if( t >= 2 )															// 若被击中的是敌坦克 
			{
				if( tank[t]->is_red() )												// 若是红车 
				{
					bonus.born();													// 生成奖励 
					bonusShowTime = BONUS_SHOW_TIME;
				}
				if( tank[t]->is_dead(false) )										// 若死亡 
				{
					killNum++;														//击杀数量 +1 
					q.push(t);
				}
			}
		}
	}
	while( !q.empty() )
	{
		int t = q.front();
		tank[t]->die();																// 将被打死的坦克置为死亡 
		q.pop();
	}
}

//检查是否吃到奖励 
void MyGame::check_bonus()
{
	for(int i = 0; i < 2; i++)
	{
		if( bonusShowTime > 5 && !tank[i]->is_dead( false ) && check_touch( tank[i]->get_box(), bonus.get_box() ) )
		{
			Mix_PlayChannel( -1, peow, 0 );
			bonusShowTime = 5;
			switch( bonus.get_type() )												// 若吃到，检查类型 
			{
				case BONUS_ADDTANK:{												// 坦克数量 +1 
					if( 0 == i) life_1++;
					else life_2++;
					break;
				}
				case BONUS_TIMESTOP:{												// 时间暂停 
					timeStop = BONUS_TIME;
					break;
				}
				case BONUS_HOME:{													// 总部加固 
					homeTime = BONUS_TIME;
					for(int i = 23; i < 26; i++)
					{
						for(int j = 11; j < 15; j++)
						{
							tile[i][j]->change_type( TILE_IRON );
						}
					}
					break;
				}
				case BONUS_BOMB:{													// 敌人全灭 
					for(int j = 2; j < TANK_TWO_NUM; j++)
					{
						if( !tank[j]->is_dead( false ) ) killNum++;
					}
					
					Mix_PlayChannel(-1, bom, 0);									// 以下为敌人全灭时的爆炸效果，有卡顿 
					int x = 5;
					while( x-- >= 0)
					{
						for(int j = 2; j < TANK_TWO_NUM; j++)
						{
							if( tank[j]->is_dead( false ) ) continue;
							SDL_Rect b = tank[j]->get_box();
							if( x >= 3 )
							{
								SDL_BlitSurface( bomb1, NULL, screen, &b);
							}
							else if( x > 0 )
							{
								SDL_BlitSurface( bomb2, NULL, screen, &b);
							}
							else
							{
								tank[j]->die();
							}
							SDL_Flip(screen);
						}
						SDL_Delay( 30 );
					}
						
					break;
				}
				case BONUS_STAR:{													// 星星 +1 
					tank[i]->add_bonus( BONUS_STAR );
					break;
				}
				case BONUS_SHIELD:{													// 保护罩 
					tank[i]->add_bonus( BONUS_SHIELD );
					break;
				}
			}
		}
	}
	
	if( homeTime >= 0 )																// 若总部处于加固状态 
	{
		homeTime--;																	// 时间减少 
		if( homeTime < 0 )															// 若加固时间结束 
		{
			for(int i = 23; i < 26; i++)											// 变成砖墙 
			{
				for(int j = 11; j < 15; j++)
				{
					tile[i][j]->change_type( TILE_BRICK );
				}
			}
		}
	}
}

//检查游戏是否结束 
void MyGame::check_end()
{
	if( end )																		// 若结束，进入结束缓冲期 
	{
		endTime--;
		return;	
	}
	
	if( life_1 < 0 && life_2 < 0)													// 当玩家生命全部用光，则结束 
	{
		end = true;
		return ;
	}
	
	for(int i = 0; i < tankNum; i++)												// 若总部被打破，则结束 
	{
		if( !tank[i]->is_dead( false ) )
		{
			if(check_touch( tank[i]->get_bullet(), homeBox ))
			{
				end = true;
				return;
			}
		}
	}
}

//显示过关画面 
void MyGame::show_stage()
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 126, 126, 126 ) );
	apply_surface( 160, 180, st, screen );
	
	SDL_Rect set; 
	set.x = 285;
	set.y = 196;
	
	show_num( level, set );															// 显示当前关卡数 
	
	SDL_Flip(screen);
	
	SDL_Delay( 3000 );
}

// 关卡切换 
void MyGame::change_level()
{
	if( killNum >= ENEMY_TOTAL_NUM )
		killNum++;
		
	if( killNum == 200 )
	{	
		num_init(); 
		
		tank_init();
			
		show_stage();
	}
}



//控制帧率 
void MyGame::control_fps()
{
	if( fps.get_ticks() < 1000 / FPS )
    {
        SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() );
    }
}

//游戏是否结束 
bool MyGame::is_end()
{
	if( timeStop > 0 ) timeStop--;													// 若时间暂停，则暂停时间减少 
	fps.start();																	// 控制帧率的计时器启动
	 
	return endTime < 0;																// 结束缓冲时间结束，则游戏结束 
}

//游戏运行的主函数 
void MyGame::gameRun()
{	
	if( !pause )																	// 若游戏没有暂停，则运行 
	{
		creat_tank();
		enemy_attack();
		tank_move();
		check_attack();
		check_bonus();
		check_end();
		change_level();
		show_game();
		show_other();
	}
	
	control_fps();																	// 控制帧率函数不受暂停影响 
}
