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
		const SDL_Rect* GetImageRect(MapObject *map) ;//由地图组件调用，返回的是摄像机在地图中的范围矩形

	private:
		SDL_Rect	shot;//镜头区域,默认大小是窗口大小,位置为（0，0）
		//SDL_Rect	FollowMoveShot;//跟随人物移动的镜头范围
		//Vector2		relaVec;//镜头在地图中的相对坐标
		SDL_Rect*	imageSrc;
		Game*		mGame;
	};
}
#endif __Camera__