#include "game.h"

//�ļ������Լ����ֱ�����ʼ�� 
MyGame::MyGame()
{
	load_files();
	all_clip();
	
	tank[0] = new MainTank(p1, playOne);										// player1 ��̹�� 
	tank[1] = new MainTank(p2, playTwo);										// player2 ��̹�� 
	for(int i = 2; i < TANK_TWO_NUM; i++)										// ��̹�˳�ʼ��
	{
		tank[i] = new EnemyTank(enemy, playOne);
	}
	
	level = 0;																	// ��ʼ�ؿ�
	life_1 = 10;																// player1 ������ 
	life_2 = 10;																// player2 ������ 
	end = false;																// δ���� 
	tankNum = TANK_TWO_NUM;														// Ĭ��Ϊ˫��ģʽ������ѡ�����޸� 
	
	num_init();																	// ������ʼ�� 
	
	tank_init();																// ̹�˳�ʼ�� 
}


//�����ļ������� 
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
	for(char i = '0'; i < TOTAL_STAGE / 10 + '0'; i++)							// ��ʼ����ͼ�ļ��� 
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

//ͼƬ�ü������ʼ�� 
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


//̹�˳�ʼ������̹�����ڳ�ʼλ�ã���̹��ȫ���������� 
void MyGame::tank_init()const 
{
	if( life_1 > 0 )
		tank[0]->reset(PLAY1_START_X, PLAY1_START_Y);								// ��̹��λ�ó�ʼ�� 
	if( life_2 > 0 )
		tank[1]->reset(PLAY2_START_X, PLAY2_START_Y);								// 
	
	for(int i = 2; i < tankNum; i++)												// ��̹�˳�ʼ����ȫ��Ϊ����״̬ 
	{
		tank[i]->die();
	}
}

//��ֵ��ʼ�� 
void MyGame::num_init()
{
	level++;																		// �ؿ���һ 
	enemyNum = ENEMY_TOTAL_NUM;														// �ؿ��ĵ�������															// 
	killNum = 0;																	// ��ɱ�ĵ�������  
	pause = false;																	// 
	endTime = TIME_TO_END;															// ��Ϸ�����Ļ���ʱ�� 
	timeStop = -1;																	// ʱ����ͣ�Ľ���ʱ�� 
	bonusShowTime = -1;																// ������ʾ��ʣ��ʱ�� 
	homeTime = -1;																	// �ܲ�������ʣ��ʱ�� 
	bonus.change( false );															// �Ƿ���ʾ���� 
	read_map( stage[level % TOTAL_STAGE] );											// ��ȡ��ͼ 
}

//�����������ͷ�̹�˺ͱ��� 
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

//��ʾ��Ϸ��ʼѡ���� 
bool MyGame::show_splash()
{			
	int y = ONE_PLAYER;
	int sy = 319;
	SDL_Event event;
	bool enter = false;																//�Ƿ��������Ϸ 
	bool press = false;																//�Ƿ�����Ч���� 
	bool mouse = false;
	
	while( !enter )																	//��û�н�����Ϸ 
	{ 
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );	//�����ú�ɫ
		apply_surface(62, 97 + sy, splash, screen);									//��ʾ���棬û����֮ǰΪ���� 
		if( press || sy <= 0 )														//��������Ч��������ʾѡ��ͼ������� 
		{
			apply_surface( 0, 0, explain, screen);
			apply_surface(150, y, choose, screen, &chooseClip);						//ѡ��ͼ�� 
			apply_surface( 87, 340, brand, screen );								//���� 
			if( mouse )
				 apply_surface( 0, 30, declare, screen);							// ��ʾ��Ϸ˵�� 
		}
		
		if( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_KEYDOWN )
			{
				if( event.key.keysym.sym == SDLK_f )								//���� F 
				{
					if( !press )													//�̶���ʾ 
					{
						press = true;
						sy = 0;
					}
					else if( y == ONE_PLAYER )										//�ı�ѡ��ͼ���λ�� 
						y = TWO_PLAYER;
					else 
						y = ONE_PLAYER;
				}
				if( event.key.keysym.sym == SDLK_h )								//���� H 
				{
					if( !press )													//�̶���ʾ 
					{
						press = true;
						sy = 0;
					}
					else 
					{
						if( y == ONE_PLAYER )										//��Ϊ����ģʽ 
						{
							tank[1]->die();											// player2 ��������״̬ 
							life_2 = -1;											// ������Ϊ���� 
							tankNum = TANK_ONE_NUM;									// �ı�̹������ 
						}	
						enter = true;												// ������Ϸ 
					} 
				}	
			}
			else if( event.type == SDL_QUIT )											//��������ڣ��˳�ѭ���� ������Ϸʧ�� 
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
		if( !press && sy >= 0 )														//��������ı��� 
			sy--;
		if( sy <= 0 )
			press = true;
			
		SDL_Flip( screen );															//ˢ�»��� 
		SDL_Delay( 6 );																//�ӳ٣����ƹ����ٶ� 
	}
	
	show_stage();																	//��ʾ�ؿ� 
	Mix_PlayMusic( music, 1 );														//���ſ������� 
	
	return true;
}


//��ʾ��Ϸ���� 
void MyGame::show_game()
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) ); // ������Ϊ��ɫ 
	
	for(int i = 0; i < tankNum; i++)												
	{
		if( !tank[i]->is_dead( false ) )											// ��̹�˷����� 
			tank[i]->show();														// ����ʾ 
	}
	
	for(int i = 0; i < TILE_NUM; i++)												// ��ʾ�ϰ� 
	{
		for(int j = 0; j < TILE_NUM; j++)
	 	{
	 		tile[i][j]->show();
		}
	}
	
	if( !end )																		// ����Ϸ��û���� 
	{
		SDL_BlitSurface( home, &homeClip[0], screen, &homeBox );					// ��ʾ�ܲ� 
	}
	else																			// ���� 
	{																				// ������ʾ GAME OVER 
		if( endTime > 80 )
			apply_surface( 162, endTime * 2, over, screen);
		else
			apply_surface( 162, 160, over, screen);
			
		SDL_BlitSurface( home, &homeClip[1], screen, &homeBox );					// ��ʾ���򻵵��ܲ� 
	}
	
	if(bonusShowTime > 0)															// ����н��� 
	{
		bonus.show();																// ��ʾ���� 
		bonusShowTime--;															// ����ʱ����� 
	}
}

//��ʾ����� 
void MyGame::show_other()
{
	SDL_Rect set;
	set.x = 440;
	set.y = 10;
	
	apply_surface(416, 0, bg, screen);												// ��ߵı���ͼ 
	
	for(int i = 0; i < enemyNum; i++)												// ��ʾʣ��ĵ�̹���� 
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
	
	set.x = 440;																	// ��ʾ player1 ʣ������� 
	set.y = 230;
	
	SDL_BlitSurface( misc, &miscClip[2], screen, &set);
	set.x += 16;
	SDL_BlitSurface( misc, &miscClip[3], screen, &set);
	
	set.x = 440;
	set.y += 16;
	SDL_BlitSurface( misc, &miscClip[1], screen, &set);
	set.x += 16;
	
	show_num( life_1, set );
	
	if( life_2 >= 0 )																// ��ʾ player2 ʣ�������
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
	
	set.x = 440;																	// ��ʾ��ǰ�Ĺؿ��� 
	set.y = 328;
	
	SDL_BlitSurface( flag, NULL, screen, &set);
	
	set.y += 32;
	set.x += 16;
	
	show_num( level, set );  
	
	SDL_Flip( screen );
}

//��ʾ���֣�����Ҫ��ʾ�����ֺ����λ�����꣬�����λ�� 
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
 
//��ʾ�����Ļ��� 
void MyGame::show_end()
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );
	
	apply_surface(126, 128, gg, screen);
	SDL_Flip( screen );
	
	SDL_Delay( 3000 );																// ��ʾ������ 
}

//̹���ƶ� 
void MyGame::tank_move()
{
	for(int i = 0; i < TANK_TWO_NUM; i++)
	{
		if( !tank[i]->is_dead( false ) )											// ��̹��δ���������ƶ� 
		{
			if( i >= 2 && timeStop > 0) return;										// ������ʱ��ֹͣ�����̹�˲��� 
			tank[i]->move(tank, i);
		}
	}
} 

// ����̹�� 
void MyGame::creat_tank()
{
	if( tank[0]->is_dead( false ) && life_1 > 0 )									// �����̹�������һ���������������λ�� 
	{
		tank[0]->reset(PLAY1_START_X, PLAY1_START_Y);
		life_1--;
	}
	if( tank[1]->is_dead( false ) && life_2 > 0)
	{
		tank[1]->reset(PLAY2_START_X, PLAY2_START_Y);
		life_2--;
	}
				
	if( enemyNum <= 0 ) return;														// ��û�е��ˣ����˳� 
	
	for(int i = 2; i < tankNum; i++)
	{
		if( tank[i]->is_dead( false ) )												// ���������� 
		{
			if(!enemyTime.is_started()) enemyTime.start();							// ����ʱ��δ������ ������ 
			if( enemyTime.get_ticks() < 2000 ) return;								// ��ʱ��С�� 2 �룬 �˳� 
																					// ���� 
			SDL_Rect set = {0, 2, TANK_SIZE, TANK_SIZE};							 
			
			set.x = offset[rand() % 3];												// ���ѡ��һ��λ�� 
			
			bool flg = true; 
			int col = set.x / TILE_SIZE;											 
			for(int p = col; p <= col + 1; p++)										// ����λ����û���ϰ�
			{
				for(int q = 0; q <= 1; q++)
				{
					if( tile[q][p]->get_type() != TILE_BLACK ) 
						flg = false;
				}
			}
			
			bool flag = true;
			for(int j = 0; j < TANK_TWO_NUM; j++)									// ����λ����û��̹�� 
			{
				if( !tank[j]->is_dead( false ) && check_touch( set, tank[j]->get_box() ) )
				{
					flg = false;
					break;
				}
			}
			
			if( !flg ) break;														// �����ϰ���̹�ˣ����˳� 
																					// ���� 
			tank[i]->reset( set.x, 2 );												// ����һ��̹�� 
			
			enemyNum--;																// ������������ 
			enemyTime.stop();														// ��ʱ��ֹͣ 
		}		
	}
} 

// ���˹��� 
void MyGame::enemy_attack()const 
{
	for(int i = 2; i < tankNum; i++)
	{
		if( !tank[i]->is_dead( false ) )											// ��û���������������ڳ�����ʱ��û����ͣ 
		{
			if( rand() % ENMEY_ATTACK_TIME == 0 && !tank[i]->is_born() && timeStop <= 0)// ��һ���ļ��ʹ��� 
			{
				tank[i]->attack();
			}
		}
	}
}

//�������� 
void MyGame::handle_input(const SDL_Event &event )
{
	if( !tank[0]->is_dead( false ) )												// ����̹��û���������������� 
		tank[0]->handle_input( event );
	if( !tank[1]->is_dead( false ) )
		tank[1]->handle_input( event );
		
	if( event.type == SDL_QUIT )													// ��������ڣ�����Ϸ���� 
	{
		end = true;
	}
	else if( event.type == SDL_KEYDOWN )
	{
		if( event.key.keysym.sym == SDLK_h )										// ���� H, ����ͣ 
		{
			pause = !pause;
			if( pause )																// ����ͣ����ʾ��ͣͼƬ 
			{
				apply_surface( 146, 187, pase, screen );
				SDL_Flip( screen );
			}
		}																			// ����Ϊ����ָ 
		else if( event.key.keysym.sym == SDLK_KP7 )									// ���� 7,�൱�ڳ�һ������ 
		{
			if( !tank[0]->is_dead( false ))
				tank[0]->add_bonus( BONUS_STAR );
			if( !tank[1]->is_dead( false ))
				tank[1]->add_bonus( BONUS_STAR );
		}
		else if( event.key.keysym.sym == SDLK_KP8 )									// ���� 8,�൱�ڳ��˷����� 
		{
			if( !tank[0]->is_dead( false ))
				tank[0]->add_bonus( BONUS_SHIELD );
			if( !tank[1]->is_dead( false ))
				tank[1]->add_bonus( BONUS_SHIELD );
		}	
	}
}

//��鹥������Щ̹�˱�����
void MyGame::check_attack()
{
	std::queue<int> q;																// ��һ�����б��汻���е�̹�� 
	for(int i = 0; i < tankNum; i++)
	{
		if( !tank[i]->is_dead( false ) )											// ��̹��δ���� 
		{
			int t = tank[i]->hit_in(tank, i);										// ��鱻����е�̹��,����-1��δ����
			 
			if( 0 == t || 1 == t )													// �������е�����̹��
			{
				if( tank[t]->is_dead( false ) )										// ���� 
					q.push(t);														// ����� 
			}
			if( t >= 2 )															// �������е��ǵ�̹�� 
			{
				if( tank[t]->is_red() )												// ���Ǻ쳵 
				{
					bonus.born();													// ���ɽ��� 
					bonusShowTime = BONUS_SHOW_TIME;
				}
				if( tank[t]->is_dead(false) )										// ������ 
				{
					killNum++;														//��ɱ���� +1 
					q.push(t);
				}
			}
		}
	}
	while( !q.empty() )
	{
		int t = q.front();
		tank[t]->die();																// ����������̹����Ϊ���� 
		q.pop();
	}
}

//����Ƿ�Ե����� 
void MyGame::check_bonus()
{
	for(int i = 0; i < 2; i++)
	{
		if( bonusShowTime > 5 && !tank[i]->is_dead( false ) && check_touch( tank[i]->get_box(), bonus.get_box() ) )
		{
			Mix_PlayChannel( -1, peow, 0 );
			bonusShowTime = 5;
			switch( bonus.get_type() )												// ���Ե���������� 
			{
				case BONUS_ADDTANK:{												// ̹������ +1 
					if( 0 == i) life_1++;
					else life_2++;
					break;
				}
				case BONUS_TIMESTOP:{												// ʱ����ͣ 
					timeStop = BONUS_TIME;
					break;
				}
				case BONUS_HOME:{													// �ܲ��ӹ� 
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
				case BONUS_BOMB:{													// ����ȫ�� 
					for(int j = 2; j < TANK_TWO_NUM; j++)
					{
						if( !tank[j]->is_dead( false ) ) killNum++;
					}
					
					Mix_PlayChannel(-1, bom, 0);									// ����Ϊ����ȫ��ʱ�ı�ըЧ�����п��� 
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
				case BONUS_STAR:{													// ���� +1 
					tank[i]->add_bonus( BONUS_STAR );
					break;
				}
				case BONUS_SHIELD:{													// ������ 
					tank[i]->add_bonus( BONUS_SHIELD );
					break;
				}
			}
		}
	}
	
	if( homeTime >= 0 )																// ���ܲ����ڼӹ�״̬ 
	{
		homeTime--;																	// ʱ����� 
		if( homeTime < 0 )															// ���ӹ�ʱ����� 
		{
			for(int i = 23; i < 26; i++)											// ���שǽ 
			{
				for(int j = 11; j < 15; j++)
				{
					tile[i][j]->change_type( TILE_BRICK );
				}
			}
		}
	}
}

//�����Ϸ�Ƿ���� 
void MyGame::check_end()
{
	if( end )																		// ��������������������� 
	{
		endTime--;
		return;	
	}
	
	if( life_1 < 0 && life_2 < 0)													// ���������ȫ���ù⣬����� 
	{
		end = true;
		return ;
	}
	
	for(int i = 0; i < tankNum; i++)												// ���ܲ������ƣ������ 
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

//��ʾ���ػ��� 
void MyGame::show_stage()
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 126, 126, 126 ) );
	apply_surface( 160, 180, st, screen );
	
	SDL_Rect set; 
	set.x = 285;
	set.y = 196;
	
	show_num( level, set );															// ��ʾ��ǰ�ؿ��� 
	
	SDL_Flip(screen);
	
	SDL_Delay( 3000 );
}

// �ؿ��л� 
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



//����֡�� 
void MyGame::control_fps()
{
	if( fps.get_ticks() < 1000 / FPS )
    {
        SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() );
    }
}

//��Ϸ�Ƿ���� 
bool MyGame::is_end()
{
	if( timeStop > 0 ) timeStop--;													// ��ʱ����ͣ������ͣʱ����� 
	fps.start();																	// ����֡�ʵļ�ʱ������
	 
	return endTime < 0;																// ��������ʱ�����������Ϸ���� 
}

//��Ϸ���е������� 
void MyGame::gameRun()
{	
	if( !pause )																	// ����Ϸû����ͣ�������� 
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
	
	control_fps();																	// ����֡�ʺ���������ͣӰ�� 
}
