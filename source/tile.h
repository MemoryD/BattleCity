#ifndef _TILES_H_
#define _TILES_H_

#include "MyDefine.h"
//#include "share.h"
#include <fstream>

//障碍类 
class Tile{
	private:
		int type;																// 障碍类型，详见常量定义 
		SDL_Surface *tile;														// 指向自己的图像 
		SDL_Rect box;															// 位置。也是碰撞盒子 
		SDL_Rect clip;															// 图片剪切 
	public:
		Tile(int x, int y, int t = TILE_BLACK);									// 构造函数，传入类型和坐标 
		~Tile();																//  
		void show();															// 显示 
		const SDL_Rect& get_box()const;											// 返回碰撞盒子 
		int get_type()const;													// 返回类型 
		void change_type( int t );												// 改变障碍的类型 
};

extern Tile *tile[TILE_NUM][TILE_NUM];

//初始化地图 
void init_map();

//读入地图，地图是全局变量 
void read_map( std::string filename );

//删除地图 
void delete_map();

#endif
