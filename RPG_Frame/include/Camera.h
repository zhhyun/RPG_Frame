#ifndef __Camera__
#define __Camera__
#include "PlayerObject.h"
#include "DEFINES.h"
#include "MapObject.h"

namespace GameFrame {
	class Game;
	class Camera {
	public:
		Camera(Game* game);
		~Camera() {};

		void InitFollowShot() {};
		const SDL_Rect GetImageRect() { return imageSrc; };
		const SDL_Rect GetPreImageRect() { return PreImageSrc; };
		void Update() { UpdateCameraRect(); };

	private:
		SDL_Rect*	shot;//��ͷ����,Ĭ�ϴ�С�Ǵ��ڴ�С,λ��Ϊ��0��0��
		SDL_Rect	FollowMoveShot;//���������ƶ��ľ�ͷ��Χ
		SDL_Rect	PreImageSrc;//��һ�εľ�ͷ����
		SDL_Rect	imageSrc;
		Game*		mGame;

		void UpdateCameraRect();//�ɵ�ͼ������ã����ص���������ڵ�ͼ�еķ�Χ����
	};
}
#endif __Camera__