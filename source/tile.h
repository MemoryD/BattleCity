#ifndef _TILES_H_
#define _TILES_H_

#include "MyDefine.h"
//#include "share.h"
#include <fstream>

//�ϰ��� 
class Tile{
	private:
		int type;																// �ϰ����ͣ������������ 
		SDL_Surface *tile;														// ָ���Լ���ͼ�� 
		SDL_Rect box;															// λ�á�Ҳ����ײ���� 
		SDL_Rect clip;															// ͼƬ���� 
	public:
		Tile(int x, int y, int t = TILE_BLACK);									// ���캯�����������ͺ����� 
		~Tile();																//  
		void show();															// ��ʾ 
		const SDL_Rect& get_box()const;											// ������ײ���� 
		int get_type()const;													// �������� 
		void change_type( int t );												// �ı��ϰ������� 
};

extern Tile *tile[TILE_NUM][TILE_NUM];

//��ʼ����ͼ 
void init_map();

//�����ͼ����ͼ��ȫ�ֱ��� 
void read_map( std::string filename );

//ɾ����ͼ 
void delete_map();

#endif
