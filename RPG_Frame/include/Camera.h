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
		SDL_Rect*	shot;//镜头区域,默认大小是窗口大小,位置为（0，0）
		SDL_Rect	FollowMoveShot;//跟随人物移动的镜头范围
		SDL_Rect	PreImageSrc;//上一次的镜头矩形
		SDL_Rect	imageSrc;
		Game*		mGame;

		void UpdateCameraRect();//由地图组件调用，返回的是摄像机在地图中的范围矩形
	};
}
#endif __Camera__