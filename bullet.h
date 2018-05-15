/********************* �ӵ���Ķ��� *********************************/ 
#ifndef _BULLET_H_
#define _BULLET_H_

//#include "share.h" 
#include "tile.h"
#include "MyDefine.h"

class Bullet{
	private:
		bool isShot;															// �Ƿ������ʲô 
		int dir;																// �˶�����
		int speed;																// �ӵ��ٶ�
		int bombTime;															// ��ը��Ч������ʱ�� 
		int shotIron;															// �Ƿ��ܴ��� 
		Thing thing;															// ������ʲô���� 
		SDL_Rect box;															// λ�ã�Ҳ����ײ���� 
		SDL_Rect bbox;															// ��ըЧ����λ�� 
		SDL_Rect clip[4];														// ����  
		SDL_Surface *explode1;													// ��ըЧ�� 1 
		SDL_Surface *explode2;													// ��ըЧ�� 2 
		SDL_Surface *myself;													// �Լ���ͼ�� 
		Mix_Chunk *hit;															// ���е���Ч 
	public:
		Bullet( const SDL_Rect &b, int d );										// ���캯��������λ�úͷ��� 
		~Bullet(); 
		void show();															// ��ʾ 
		bool collision();														// ����Ƿ�ײ��ǽ					
		void reset( const SDL_Rect &b, int d, bool s, int iron = -1, int sp = 2);// ���� 
		bool is_shot()const;													// ���� isShot 
		void move();															// �ƶ�λ�� 
		bool will_hit(Thing hit);												// ��������ʲô 
		const SDL_Rect& get_box()const;											// ������ײ���� 
		void change_status( bool status );										// �ı��ӵ�״̬�����Ƿ����ʲô 
		bool hit_tile(int x, int y)const;										// �Ƿ�����ϰ� 
		int in_bored( int x )const;												// ���� x ����Ϸ������ 
};

#endif 
