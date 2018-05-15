#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include<cstdio>
#include <set>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *map = NULL;
SDL_Surface *screen = NULL;

std::set<int> tile[5];

SDL_Surface *load_image( std::string filename )
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
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    return optimizedImage;
}

Uint32 get_pixel32( int x, int y, SDL_Surface *surface )
{
    Uint32 *pixels = (Uint32 *)surface->pixels;

    return pixels[ ( y * surface->w ) + x ];
}

bool init()
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
	
    SDL_WM_SetCaption( "read map", NULL );

    return true;
}


bool load_files()
{
    tile[0].insert(8355711);
	tile[0].insert(11211520);
	tile[0].insert(15163155);
	
	tile[1].insert(8355711);
	tile[1].insert(12566463);
	tile[1].insert(16316664);
	
	tile[2].insert(0);
	tile[2].insert(23296);
	tile[2].insert(30720);
	tile[2].insert(12122136);
	
	tile[3].insert(22776);
	tile[3].insert(65535);
	tile[3].insert(12566463);
	
	tile[4].insert(0);

    return true;
}

void clean_up()
{
    SDL_FreeSurface( map );

    SDL_Quit();
}

int main(int argc, char *args[])
{
	init();
	
//	load_files();
	
	std::set<int> s;
	std::set<int>::iterator it;
	map = load_image( "graphics\\misc.bmp");				//写要读取的图片 
	freopen("graphics\\color.txt", "a", stdout);			//生成的地图文件 
	
	for(int i = 2; i < map->w; i++)
	{	
		for(int j = 2; j < map->h; j++)
		{
			Uint32 t = get_pixel32( i, j, map );
		
			s.insert( t );		
		}
	}	
				
	for( it = s.begin(); it != s.end(); it++)
	{
		printf("%d\n", *it);
	}
	clean_up();
	
	return 0;
} 
