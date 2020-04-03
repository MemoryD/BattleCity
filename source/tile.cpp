#include "tile.h"
Tile *tile[TILE_NUM][TILE_NUM];													// �ϰ������ʾ��ͼ����ȫ�ֱ��� 

//���캯�� 
Tile::Tile( int x, int y, int t )
{
	tile = load_image( "..\\graphics\\tile.bmp" ,BLACK_KEY);
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

//�ı��ϰ����ͣ�����ҲҪ�ı� 
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

//��ʼ����ͼ 
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

//�����ͼ����ͼ��ȫ�ֱ��� 
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

//ɾ����ͼ 
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
