#ifndef __MYDEFINE_H 
#define __MYDEFINE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string>

/**************************һЩ�����Ķ���************************************/ 
//���� 
const int SCREEN_WIDTH = 505;												//��Ļ�� 
const int SCREEN_HEIGHT = 416;												//��Ļ�� 
const int SCREEN_BPP = 32;													//�ֱ���

const int FPS = 30;															//֡�� 

const int GAME_WIDTH = 416;													//��Ϸ������ 
const int GAME_HEIGHT = 416;												//��Ϸ����߶� 

const int TOTAL_STAGE = 40;													//�ؿ��� 

//��̹�� 
const int PLAY1_START_X = 130;												//��� 1 �ĳ�ʼλ�� 
const int PLAY1_START_Y = 382;												//
const int PLAY2_START_X = 258;												//��� 2 �ĳ�ʼλ�� 
const int PLAY2_START_Y = 382; 												//

const int ONE_PLAYER = 265;													//��ʼѡ�����Ĳ������ж��ǵ��˻�˫�� 
const int TWO_PLAYER = 297;													//

const int TANK_ONE_NUM = 6;													//������Ϸʱͬһʱ���ڳ��ֵ�̹������(����̹��)
const int TANK_TWO_NUM = 8;													//˫����Ϸʱͬһʱ���ڳ��ֵ�̹������(����̹��)

const int TANK_SIZE = 28;													//̹�˴�С 
const int TANK_SPEED = 1;													//̹���ٶȻ��� 

//��̹�� 
const int ENEMY_TOTAL_NUM = 20;										 		//һ���ؿ��ĵ�̹������ 
const int ENMEY_ATTACK_TIME = 30; 											//��̹�˹�����Ƶ�� 
const int ENEMY_SPECIES = 3;												//��̹������
const int ENEMY_SLOW_SPEED = 3;												//һ���̹�˵��ٶ� �������ٶ�������ٶȻ��� 
const int ENEMY_FAST_SPEED = 5;												//�ȽϿ�ĵ�̹���ٶ� 

//�ӵ� 
const int BULLET_SIZE = 8;													//�ӵ���С 
const int BULLET_SPEED = 4;													//�ӵ��ٶ� 
const int BULLET_ADDSPEED = 2;												//��̹������ʱ���ӵ��ٶȵ����� 

//�������� 
enum Thing{TANK, BULLET, WALL, NOTHING};									//�ӵ����е�Ŀ�� 

struct Move{																//�˶����򣬼�ÿ����������� 
	int x;
	int y;
	int key;																//����� 
};

extern int offset[3];														//��̹�˵ĳ�ʼ X λ�� 
extern SDL_Surface *screen;													// ��Ϸ����ı��棬ȫ�ֱ��� 
// 
const int UP = 0;															//�������� 
const int RIGHT = 1;														//��
const int DOWN = 2;															//�� 
const int LEFT = 3;															//�� 

// 
const int MISC_SIZE = 14;													//���С̹��ͼ���С 
const int NUM_SIZE = 14;													//���ִ�С 

//���¾�Ϊ��ͼ�ϵı�ʶ����ͼ��һ�� Tile ��Ķ�ά���� 
const int TILE_SIZE = 16;													//�ϰ���С 
const int TILE_NUM = 26;													//ÿ�м�ÿ�е��ϰ��� 

const int TILE_BRICK = 0;													//ש�� 
const int TILE_IRON = 1;													//�� 
const int TILE_LAWN = 2;													//��ƺ 
const int TILE_WATER = 3;													//ˮ
const int TILE_BLACK = 9; 													//û���ϰ���������ɫ

//����Ϊ���߽����йصĳ��� 
const int BONUS_WIDTH = 30;													//���߽���ͼ��Ŀ� 
const int BONUS_HEIGHT = 28;												//�� 

const int BONUS_ADDTANK = 0;												//����һ��̹�� 
const int BONUS_TIMESTOP = 1;												//����ʱ��ֹͣ 
const int BONUS_HOME = 2;													//�ܲ��ӹ� 
const int BONUS_BOMB = 3;													//����ȫ�� 
const int BONUS_STAR = 4;													//�Ǽ�+1 
const int BONUS_SHIELD = 5;													//��ʱ�޵� 

const int BONUS_TIME = 600;													//���߽���ʱ�� 
const int BONUS_SHOW_TIME = 400;											//������ʾʱ�� 

const int BORN_TIME = 20;													//����ʱ������˸ʱ�䣬ʱ�䵥λ�� ֡����ͬ 
const int INIT_SHIELD_TIME = 60;											//��ʼ�޵�ʱ��

// 
const int TIME_TO_END = 200; 												//��Ϸ�����Ķ��ʱ��
 
// 
const int BLACK_KEY = 263172;												// ���ֺ�ɫ������ֵ 
const int WHITE_KEY = 16777215;												// ��ɫ������ֵ 

SDL_Surface *load_image( std::string filename ,int key = 0 );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
bool init_SDL();
bool quit_SDL();
bool check_touch( const SDL_Rect &A, const SDL_Rect &B );
bool over_bored( const SDL_Rect &box );
int random( int min, int max );
 
/***************************************************************************/ 
#endif
