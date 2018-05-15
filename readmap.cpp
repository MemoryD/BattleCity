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
std::string stage[50];
std::string level[50];

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
	int x = 0; 
	for(char i = '0'; i <'4'; i++)
	{
		for(char j = '0'; j <= '9'; j++)
		{
			stage[x] += "Stage\\stage";
			stage[x] += i;
			stage[x] += j;
			stage[x] += ".png";
			level[x] += "map\\level";
			level[x] += i;
			level[x] += j;
			level[x] += ".map";
			x++;
		}
	}
	
	tile[0].insert(7895160);
	tile[0].insert(8933432);
	tile[0].insert(9990200);
	tile[0].insert(10498048);
	tile[0].insert(11554816);
	tile[0].insert(12611584);
	
	tile[1].insert(7895160);
	tile[1].insert(10000536);
	tile[1].insert(11053224);
	tile[1].insert(12105912);
	tile[1].insert(14211288);
	tile[1].insert(16316664);
	
	tile[2].insert(0);
	tile[2].insert(1585184);
	tile[2].insert(3170336);
	tile[2].insert(3170352);
	tile[2].insert(3170368);
	tile[2].insert(3696640);
	tile[2].insert(4747264);
	tile[2].insert(4751408);
	tile[2].insert(6332448);
	tile[2].insert(6858752);
	tile[2].insert(7383040);
	tile[2].insert(7913488);
	tile[2].insert(8439808);
	tile[2].insert(10020864);
	
	tile[3].insert(4210936);
	tile[3].insert(5794032);
	tile[3].insert(7379184);
	tile[3].insert(10549488);
	
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
	
	load_files();
	
	
	for(int p = 1; p <= 33; p++)
	{
		map = load_image( stage[p] );				//写要读取的图片 
		freopen(level[p].c_str(), "w", stdout);			//生成的地图文件 
		for(int i = 3; i < 410; i += 16)
		{
			for(int j = 3; j < 410; j += 16)
			{
				std::set<int> s;
				std::set<int>::iterator it;
				
				for(int x = j; x < j + 10; x++)
				{
					for(int y = i; y < i + 10; y++)
					{
						Uint32 t = get_pixel32( x, y, map );
	//					printf("%d\n",t); 
						s.insert( t );
					}
				}
				
				if( s.size() == 1 && s.find( 0 ) != s.end() )
				{
					printf("%d ",9);
				}
				else
				{
					bool flag = true;
					for(int p = 0; p <= 3; p++)
					{
						int color = 0;
						for( it = s.begin(); it != s.end(); it++)
						{
							if( tile[p].find( *it ) != tile[p].end() )
							{
								color++;
							}
						}
						
						if( color > 2 )
						{
							printf("%d ",p);
							flag = false;
							break;
						}
					}
					
					if( flag )
					{
						printf("%d ", 9);
					}
				}
					
			}
			printf("\n");
		}
	}
		
				
	clean_up();
	
	return 0;
} 
