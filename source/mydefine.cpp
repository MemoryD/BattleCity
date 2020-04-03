/*********************������************************/ 
#include "MyDefine.h"
SDL_Surface *screen = NULL;
int offset[3] = {2, 194, 385};												//��̹�˵ĳ�ʼ X λ�� 												// ��Ϸ����ı��棬ȫ�ֱ��� 
//����ͼƬ�������ļ��� �� �ؼ�ɫ���ؼ�ɫ��Ҫ���εı���ɫ��Ĭ��Ϊ 0 
SDL_Surface *load_image( std::string filename ,int key )
{
    SDL_Surface* loadedImage = NULL;

    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );

        SDL_FreeSurface( loadedImage );

        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, key );
        }
    }

    return optimizedImage;
}

//Ӧ�ñ��棬�������꣬Դ���棬Ŀ����棬�Լ�Դ����ļ��� 
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    SDL_Rect off;

    off.x = x;
    off.y = y;

    SDL_BlitSurface( source, clip, destination, &off );
}

//��ʼ��SDL���Լ���չ�Ĳ��� 
bool init_SDL()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
	
	SDL_WM_SetCaption( "BattleCity", NULL );
    SDL_WM_SetIcon(SDL_LoadBMP("..\\graphics\\tank_ico.bmp"), NULL);
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL )
    {
        return false;
    }
	
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    return true;
}

//�˳�SDL 
bool quit_SDL()
{
	Mix_CloseAudio();
	
	SDL_Quit();
}

//��ײ��⣬����������ײ���� 
bool check_touch( const SDL_Rect &A, const SDL_Rect &B )
{
    if( A.y + A.h <= B.y )
    {
        return false;
    }

    if( A.y >= B.y + B.h )
    {
        return false;
    }

    if( A.x + A.w <= B.x )
    {
        return false;
    }

    if( A.x >= B.x + B.w )
    {
        return false;
    }

    return true;	
} 

//�Ƿ񳬳���Ϸ�߽磬����һ����ײ���� 
bool over_bored( const SDL_Rect &box )
{
	if( box.x <= 0 || box.x + box.w >= GAME_WIDTH || box.y <= 0 || box.y + box.h >= GAME_HEIGHT )
	{
		return true;
	}
	return false;
}

//����һ�� min �� max ֮���������������߽� 
int random( int min, int max )
{
	return rand() % ( max - min + 1 ) + min;
} 

