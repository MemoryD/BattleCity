/*********************共享函数************************/ 
#include "MyDefine.h"
SDL_Surface *screen = NULL;
int offset[3] = {2, 194, 385};												//敌坦克的初始 X 位置 												// 游戏界面的表面，全局变量 
//载入图片，传入文件名 和 关键色，关键色即要屏蔽的背景色，默认为 0 
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

//应用表面，传入坐标，源表面，目标表面，以及源表面的剪切 
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    SDL_Rect off;

    off.x = x;
    off.y = y;

    SDL_BlitSurface( source, clip, destination, &off );
}

//初始化SDL，以及扩展的部件 
bool init_SDL()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL )
    {
        return false;
    }
	
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }
    
    SDL_WM_SetCaption( "BattleCity", NULL );

    return true;
}

//退出SDL 
bool quit_SDL()
{
	Mix_CloseAudio();
	
	SDL_Quit();
}

//碰撞检测，传入两个碰撞盒子 
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

//是否超出游戏边界，传入一个碰撞盒子 
bool over_bored( const SDL_Rect &box )
{
	if( box.x <= 0 || box.x + box.w >= GAME_WIDTH || box.y <= 0 || box.y + box.h >= GAME_HEIGHT )
	{
		return true;
	}
	return false;
}

//返回一个 min 和 max 之间的随机数，包含边界 
int random( int min, int max )
{
	return rand() % ( max - min + 1 ) + min;
} 

