#include "game.h"

int main( int argc, char *args[] )
{
//	freopen("bug.txt", "w", stdout);												// ���ڵ��ԣ��ɺ��� 
	srand( unsigned(time(0)));														// ������������� 
	
	init_SDL();																			// ��ʼ�� SDL �ĸ������� 
	init_map();
	
	SDL_Event event;																// ��������¼� 
	bool quit = false;																// �Ƿ��˳���Ϸ 
	
	while( !quit )																	// ��û���˳���Ϸ 
	{
		MyGame myTank;																// ������Ϸ 
		
		if( !myTank.show_splash() )													// ������Ϸѡ��ʱ�˳���Ϸ 
		{
			break;																	// ���˳� 
		}
		
		while( !myTank.is_end() )													// ����Ϸû�н��� 
		{
			if( SDL_PollEvent( &event ))											// ���д�������¼� 
			{
				myTank.handle_input( event );										// �������� 
				if( event.type == SDL_QUIT )										// ��������� 
				{
					quit = true;													// ���˳� 
					break;
				}
			}
			
			myTank.gameRun();														// ������Ϸ 
		
		}
		if(!quit)																	// ���Ƿǲ�����ڵ��˳�ѭ�� 
			myTank.show_end();														// ��ʾ�������� 
	}
	
	delete_map();
	quit_SDL();																		// �˳� SDL 
	
	return 0;
}
