#include "tile.h"
Tile *tile[TILE_NUM][TILE_NUM];													// 障碍数组表示地图，是全局变量 

//构造函数 
Tile::Tile( int x, int y, int t )
{
	tile = load_image( "graphics\\tile.bmp" ,BLACK_KEY);
	type = t;
	box.x = x;
	box.y = y;
	box.w = TILE_SIZE;
	box.h = TILE_SIZE;
	clip.x = 2 * type * TILE_SIZE;
	clip.y = 0;
	clip.w = TILE_SIZE;
	clip.h = TILE_SIZE;
	 
} 

Tile::~Tile()
{
	SDL_FreeSurface( tile );
}

const SDL_Rect& Tile::get_box()const 
{
	return box;
} 

int Tile::get_type()const 
{
	return type;
}

//改变障碍类型，剪切也要改变 
void Tile::change_type( int t )
{
	type = t;
	clip.x = 2 * type * TILE_SIZE;
	clip.y = 0;
	clip.w = TILE_SIZE;
	clip.h = TILE_SIZE;
}

void Tile::show()
{
	SDL_BlitSurface(tile, &clip, screen, &box);
}

//初始化地图 
void init_map()
{
	for(int i = 0; i < TILE_NUM; i++)
	{
		for(int j = 0; j < TILE_NUM; j++)
	 	{
	 		tile[i][j] = new Tile(j * TILE_SIZE, i * TILE_SIZE);
		}
	}
}

//读入地图，地图是全局变量 
void read_map( std::string filename )
{
	std::ifstream map( filename.c_str() );
	
	for(int i = 0; i < TILE_NUM; i++)
	{
		for(int j = 0; j < TILE_NUM; j++)
	 	{
	 		int tileType = TILE_BLACK;
	 		
	 		map >> tileType;
	 		
	 		tile[i][j]->change_type( tileType );
		}
	}
}

//删除地图 
void delete_map()
{
	for(int i = 0; i < TILE_NUM; i++)
	{
		for(int j = 0; j < TILE_NUM; j++)
	 	{
	 		delete tile[i][j];
		}
	}
}
