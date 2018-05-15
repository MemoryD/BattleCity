#ifndef BONUS_H_
#define BONUS_H_

#include "MyDefine.h"

class Bonus{
	private:
		int type;																// ���������� 
		int showTime;															// ��˸��ʾ�ļ��ʱ�� 
		bool isShow;															// �Ƿ�������ʾ 
		SDL_Surface *me;														// ָ���Լ��ı��� 
		SDL_Rect box;															// λ�ã�Ҳ����ײ���� 
		SDL_Rect clip[6];														// ͼƬ�ļ��� 
	public:
		Bonus();																// ���� 
		~Bonus();
		void born();															// ����һ������ 
		void show();															// ��ʾ���� 
		int get_type()const;													// ���ؽ������� 
		const SDL_Rect& get_box()const;											// ������ײ���� 
		void change( bool s );													// �ı�״̬�����Ƿ���ʾ 
};

#endif
