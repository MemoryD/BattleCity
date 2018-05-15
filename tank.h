/****************************** ̹����Ķ��� ******************************************/ 
#ifndef _TANK_H_
#define _TANK_H_

#include "MyDefine.h"
#include "bullet.h"

extern Move playOne[5];
extern Move playTwo[5];


/*******************************̹�˻���Ķ���*******************************************/ 

class Tank{
	protected:
		int dir;																	// ̹�˵ķ��� 
		int speed;																	// �ٶ� 
		int bornTime;																// ����ʣ���ʱ�� 
		bool isMove;																// �Ƿ������˶� 
		bool isDead;																// �Ƿ����� 
		SDL_Rect box; 																// λ�ã�Ҳ����ײ���� 
		SDL_Rect bornClip;															// ����ʱ�����Ǽ��� 
		Bullet *bullet;																// �ӵ� 
		Move *moveTo;																// �˶������������ 
		SDL_Surface *me;															// �Լ���ͼ�� 
		SDL_Surface *born;															// ����ʱ������ 
		SDL_Surface *shield;														// ������ 
		Mix_Chunk *bang;															// ������ʱ����Ч 
	public:
		Tank(SDL_Surface *source, Move *m);											// ���캯��������ͼ��ͷ�������ָ�� 
		virtual ~Tank(){};															// ���������� 
		bool touch_wall()const;														// �Ƿ�ײǽ 
		bool touch_tank( Tank **tank,int num ) const;								// �Ƿ�ײ��̹�� 
		void attack(int sp = 2, int iron = -1 )const;								// �������������ӵ� 
		const SDL_Rect& get_box()const;												// ������ײ���� 
		const SDL_Rect& get_bullet()const;											// �����ӵ�����ײ���� 
		bool adjust();																// ����λ�� 
		void do_move( int s, int d );												// �ƶ� 
		void un_move( int s, int d );												// �����ƶ� 
		int hit_in( Tank **tank, int num )const;											// ���ػ���̹�˵��±꣬û�����򷵻�-1 
		bool bullet_status()const;													// �ӵ�״̬���Ƿ���ж��� 
		void change_bullet( bool status )const;										// �ı��ӵ���״̬ 
		bool is_born()const;														// �Ƿ����ڳ��� 
		void die();																	// ��̹���������� 
		virtual void reset(int x, int y){};											// �����麯�����������н���˵�� 
		virtual void show(){};
		virtual void move(Tank **tank, int num){};
		virtual void add_bonus( int t ){};
		virtual bool is_shield()const{};
		virtual void handle_input(const SDL_Event &event){};
		virtual bool is_red(){};
		virtual bool is_dead( bool shot = false ){};
};


/*********************************����Ϊ��̹�˵Ķ���***********************************/ 


class MainTank: public Tank{
	private:
		SDL_Rect clip[4][4];														// ̹�˵�ͼƬ���� 
		int star;																	// ̹�˵��Ǽ� 
		int shieldTime;																// ʣ����޵�ʱ�� 
		Mix_Chunk *fire;															// �������Ч 
	public:
		MainTank( SDL_Surface *source, Move *m );									// ���캯�� 
		~MainTank(); 
		void move( Tank **tank,int num  );											// ̹���ƶ� 
		void show();																// ��ʾ̹�� 
		void handle_input( const SDL_Event &event ); 								// �������� 
		void add_bonus( int t );													// ���ӽ��� 
		bool is_shield()const;														// �Ƿ��б����� 
		bool is_dead(bool shot = false);											// �Ƿ����� 
		void reset(int x, int y);													// ����λ�� 
};

/**********************************����Ϊ��̹�˵Ķ��� **********************************/ 

class EnemyTank:public Tank{
	private:
		int type;																	// ̹�˵����� 
		int blood;																	// ʣ�µ�Ѫ�� 
		bool red;																	// �Ƿ�Ϊ�쳵 
		int redTime;																// ��ʾ��ɫ��ʱ�� 
		SDL_Rect clip[4][4];														// �������� 
	public:
		EnemyTank( SDL_Surface *source, Move *m  );									// ���캯�� 
		~EnemyTank(); 
		void move( Tank **tank, int num );											// ̹���ƶ� 
		void show();																// ̹����ʾ 
		bool is_red();																// �Ƿ�Ϊ��ɫ 
		bool is_dead(bool shot = false);											// �Ƿ����� 
		void reset(int x, int y);													// ���� 
};

#endif
