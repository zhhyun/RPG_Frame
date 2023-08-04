#ifndef __Camera__
#define __Camera__
#include "Game.h"
#include "PlayerObject.h"
#include "DEFINES.h"
#include "MapObject.h"

namespace GameFrame {
	class Camera {
	public:
		Camera(Game* game);
		~Camera() {};

		//void InitShot() { shot = {0,0, (int)SCREEN_W,(int)SCREEN_H }; };
		void InitFollowShot() {};
		const SDL_Rect* GetImageRect(MapObject *map) ;//�ɵ�ͼ������ã����ص���������ڵ�ͼ�еķ�Χ����

	private:
		SDL_Rect	shot;//��ͷ����,Ĭ�ϴ�С�Ǵ��ڴ�С,λ��Ϊ��0��0��
		//SDL_Rect	FollowMoveShot;//���������ƶ��ľ�ͷ��Χ
		//Vector2		relaVec;//��ͷ�ڵ�ͼ�е��������
		SDL_Rect*	imageSrc;
		Game*		mGame;
	};
}
#endif __Camera__