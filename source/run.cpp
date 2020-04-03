#include "game.h"

int main( int argc, char *args[] )
{
//	freopen("bug.txt", "w", stdout);												// 用于调试，可忽略 
	srand( unsigned(time(0)));														// 随机函数的种子 
	
	init_SDL();																			// 初始化 SDL 的各个部件 
	init_map();
	
	SDL_Event event;																// 待处理的事件 
	bool quit = false;																// 是否退出游戏 
	
	while( !quit )																	// 若没有退出游戏 
	{
		MyGame myTank;																// 创造游戏 
		
		if( !myTank.show_splash() )													// 若在游戏选择时退出游戏 
		{
			break;																	// 则退出 
		}
		
		while( !myTank.is_end() )													// 若游戏没有结束 
		{
			if( SDL_PollEvent( &event ))											// 若有待处理的事件 
			{
				myTank.handle_input( event );										// 处理输入 
				if( event.type == SDL_QUIT )										// 若叉掉窗口 
				{
					quit = true;													// 则退出 
					break;
				}
			}
			
			myTank.gameRun();														// 运行游戏 
		
		}
		if(!quit)																	// 若是非叉掉窗口的退出循环 
			myTank.show_end();														// 显示结束画面 
	}
	
	delete_map();
	quit_SDL();																		// 退出 SDL 
	
	return 0;
}
