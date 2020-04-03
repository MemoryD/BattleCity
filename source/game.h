#ifndef _GAME_H_
#define _GAME_H_

#include "MyDefine.h"
#include "tank.h"
#include "tile.h"
#include "Timer.h"
#include "bonus.h"
#include <cstdlib>
#include <ctime> 
#include <queue>
#include <cstdio>

class MyGame{
	private:
		//����Ϊ��Ϸ���õ���һЩ���� 
		Tank *tank[TANK_TWO_NUM];												// ָ��̹�˵�ָ������ 
		int map[TILE_NUM][TILE_NUM];											// ��ͼ���� 
		int enemyNum;															// ��ǰ�ؿ�ʣ��ĵ������� 
		int killNum;															// ��ǰ�ؿ���ɱ�ĵ������� 
		int tankNum;															// ͬʱ���ֵ����̹������ 
		int life_1;																// player1 ��ʣ������ 
		int life_2;																// player2 ��ʣ������ 
		int level;																// ��ǰ�ؿ� 
		bool end;																// ��Ϸ�Ƿ���� 
		bool pause;																// ��Ϸ�Ƿ���ͣ 
		int timeStop;															// ʱ���Ƿ�ֹͣ�� ���� 0 ��ʾֹͣ 
		int bonusShowTime;														// ����ʣ�����ʾʱ�� 
		int homeTime;															// �ܲ��ӹ�ʣ���ʱ�� 
		int endTime;															// �����ʣ���ʱ�� 
		Bonus bonus;															// ���� 
		Timer enemyTime;														// ������˵�ʱ���� �õļ�ʱ�� 
		Timer fps;																// ����֡���õļ�ʱ�� 
		std::string stage[TOTAL_STAGE];											// �ؿ����������� 
		//����Ϊ��Ϸ���õ��ĸ����ز� 
		SDL_Surface *p1;														// player1 ̹�� 
		SDL_Surface *p2;														// player2 ̹�� 
		SDL_Surface *enemy;														// ��̹�� 
		SDL_Surface *misc;														// ���С̹��ͼ�� 
		SDL_Surface *bg;														// ��߱��� 
		SDL_Surface *num;														// ������ʾ������ 
		SDL_Surface *flag;														// ���С���� 
		SDL_Surface *home;														// �ܲ���ӥͼƬ 
		SDL_Surface *over;														// �ܲ�������ʱ��ʾ��ͼƬ 
		SDL_Surface *pase;														// ��ͣʱ��ʾ��ͼƬ 
		SDL_Surface *splash;													// ��ʼ������ʾ��ͼƬ 
		SDL_Surface *explain;													// ��Ϸ˵����ʾ��ͼ�� 
		SDL_Surface *declare;													// ��Ϸ˵�������� 
		SDL_Surface *choose;													// ѡ��ʱ�õ�С̹��ͼ�� 
		SDL_Surface *brand;														// ��ʾ���� 
		SDL_Surface *gg;														// ��Ϸ����ʱ��ʾ�� GAME OVER 
		SDL_Surface *bomb1;														// ը��Ч�� 1 
		SDL_Surface *bomb2;														// ը��Ч�� 2 
		SDL_Surface *st;														// �ؿ��л�ʱ��ʾ��ͼƬ 
		Mix_Music *music;														// ��������
		Mix_Chunk *bom;															// ����ȫ��ʱ����Ч  
		Mix_Chunk *peow;														// ��ý���ʱ����Ч 
		//����Ϊ�õ���ͼƬ�������򣬶�Ӧ�����ͼƬ 
		SDL_Rect miscClip[6];													// 
		SDL_Rect numClip[10];													// 
		SDL_Rect homeClip[2];													//
		SDL_Rect chooseClip;													// ѡ��ͼ��ļ��У����� player1 ��̹�� 
		SDL_Rect homeBox;														// �ܲ���λ�� 
	public:
		MyGame();																// ���캯��
		~MyGame();																// �������� 
		void load_files();														// �����ļ������� 
		void all_clip();														// ͼƬ�Ĳü����� 
		void tank_init()const;													// ̹�˵ĳ�ʼ�� 
		void num_init();														// �����ĳ�ʼ�� 
		bool show_splash();														// ��ʾ��ʼѡ����� 
		void show_game();														// ��ʾ��Ϸ���� 
		void show_other();														// ��ʾ������� 
		void show_num( int x, SDL_Rect &set );									// ��ʾ���� 
		void show_stage();														// ��ʾ�ؿ��л����� 
		void show_end();														// ��ʾ��Ϸ�������� 
		void tank_move();														// ̹�˵��ƶ� 
		void creat_tank();														// ����̹�� 
		void check_attack();													// ������⣬�Ƿ���� 
		void check_end();														// �����Ϸ�Ƿ���� 
		void check_bonus();														// ����Ƿ��ý����Լ����н��� 
		void change_level();													// �л��ؿ� 
		void enemy_attack()const;												// ���˽��й��� 
		void handle_input( const SDL_Event &event );							// �������� 
		void control_fps();														// ����֡�� 
		void gameRun();															// ��Ϸ��Ҫ���к��� 
		bool is_end();															// �Ƿ���� 
};

#endif
