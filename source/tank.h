/****************************** 坦克类的定义 ******************************************/ 
#ifndef _TANK_H_
#define _TANK_H_

#include "MyDefine.h"
#include "bullet.h"

extern Move playOne[5];
extern Move playTwo[5];


/*******************************坦克基类的定义*******************************************/ 

class Tank{
	protected:
		int dir;																	// 坦克的方向 
		int speed;																	// 速度 
		int bornTime;																// 出生剩余的时间 
		bool isMove;																// 是否正在运动 
		bool isDead;																// 是否死亡 
		SDL_Rect box; 																// 位置，也是碰撞盒子 
		SDL_Rect bornClip;															// 出生时的星星剪切 
		Bullet *bullet;																// 子弹 
		Move *moveTo;																// 运动各方向的增量 
		SDL_Surface *me;															// 自己的图像 
		SDL_Surface *born;															// 出生时的星星 
		SDL_Surface *shield;														// 防护罩 
		Mix_Chunk *bang;															// 被打死时的音效 
	public:
		Tank(SDL_Surface *source, Move *m);											// 构造函数，传入图像和方向增量指针 
		virtual ~Tank(){};															// 虚析构函数 
		bool touch_wall()const;														// 是否撞墙 
		bool touch_tank( Tank **tank,int num ) const;								// 是否撞到坦克 
		void attack(int sp = 2, int iron = -1 )const;								// 攻击，即发射子弹 
		const SDL_Rect& get_box()const;												// 返回碰撞盒子 
		const SDL_Rect& get_bullet()const;											// 返回子弹的碰撞盒子 
		bool adjust();																// 调整位置 
		void do_move( int s, int d );												// 移动 
		void un_move( int s, int d );												// 撤销移动 
		int hit_in( Tank **tank, int num )const;											// 返回击中坦克的下标，没击中则返回-1 
		bool bullet_status()const;													// 子弹状态，是否击中东西 
		void change_bullet( bool status )const;										// 改变子弹的状态 
		bool is_born()const;														// 是否正在出生 
		void die();																	// 将坦克置于死亡 
		virtual void reset(int x, int y){};											// 以下虚函数在派生类中进行说明 
		virtual void show(){};
		virtual void move(Tank **tank, int num){};
		virtual void add_bonus( int t ){};
		virtual bool is_shield()const{};
		virtual void handle_input(const SDL_Event &event){};
		virtual bool is_red(){};
		virtual bool is_dead( bool shot = false ){};
};


/*********************************以下为主坦克的定义***********************************/ 


class MainTank: public Tank{
	private:
		SDL_Rect clip[4][4];														// 坦克的图片剪切 
		int star;																	// 坦克的星级 
		int shieldTime;																// 剩余的无敌时间 
		Mix_Chunk *fire;															// 开火的音效 
	public:
		MainTank( SDL_Surface *source, Move *m );									// 构造函数 
		~MainTank(); 
		void move( Tank **tank,int num  );											// 坦克移动 
		void show();																// 显示坦克 
		void handle_input( const SDL_Event &event ); 								// 处理输入 
		void add_bonus( int t );													// 增加奖励 
		bool is_shield()const;														// 是否有保护罩 
		bool is_dead(bool shot = false);											// 是否死亡 
		void reset(int x, int y);													// 重置位置 
};

/**********************************以下为敌坦克的定义 **********************************/ 

class EnemyTank:public Tank{
	private:
		int type;																	// 坦克的类型 
		int blood;																	// 剩下的血量 
		bool red;																	// 是否为红车 
		int redTime;																// 显示红色的时间 
		SDL_Rect clip[4][4];														// 剪切区域 
	public:
		EnemyTank( SDL_Surface *source, Move *m  );									// 构造函数 
		~EnemyTank(); 
		void move( Tank **tank, int num );											// 坦克移动 
		void show();																// 坦克显示 
		bool is_red();																// 是否为红色 
		bool is_dead(bool shot = false);											// 是否死亡 
		void reset(int x, int y);													// 重生 
};

#endif
