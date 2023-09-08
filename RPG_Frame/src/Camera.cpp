#include "Camera.h"
#include "Game.h"

GameFrame::Camera::Camera(Game* game):
	mGame(game)
{
	shot = new SDL_Rect();
	//摄像机初始位置
	shot->x = mGame->GetPlayer()->GetPosition().x - 0.5 * (shot->w - mGame->GetPlayer()->GetW());
	shot->y = mGame->GetPlayer()->GetPosition().y - 0.5 * (shot->w - mGame->GetPlayer()->GetH());
	shot->w = (int)SCREEN_W;
	shot->h = (int)SCREEN_H;
	imageSrc = *shot;
	PreImageSrc = imageSrc;
}

void GameFrame::Camera::UpdateCameraRect()
{
	Sence* sence = mGame->GetPlayer()->GetMapObject();
	PreImageSrc = imageSrc;
	//这里的坐标都是在map中的坐标，即绝对坐标,PlayerObject的坐标也是地图坐标
	int tmpX = imageSrc.x;
	int tmpY = imageSrc.y;

	imageSrc.x = mGame->GetPlayer()->GetPosition().x /*+ PreImageSrc.x*/ - 0.5 * (shot->w - mGame->GetPlayer()->GetW());
	imageSrc.y = mGame->GetPlayer()->GetPosition().y /*+ PreImageSrc.y */- 0.5 * (shot->h - mGame->GetPlayer()->GetH());

	if (imageSrc.x < 0) {
		imageSrc.x = 0;
	}
	if (imageSrc.y < 0) {
		imageSrc.y = 0;
	}
	if (imageSrc.x + shot->w > sence->MapW) {
		imageSrc.x = sence->MapW - shot->w;
	}
	if (imageSrc.y + shot->h > sence->MapH) {
		imageSrc.y = sence->MapH - shot->h;
	}



	//如果地图比窗口小，则需要调整镜头为地图范围
	//如果地图比窗口大，则镜头范围取窗口范围
	if (SCREEN_W > sence->MapW) {
		imageSrc.w = sence->MapW;
		imageSrc.x = 0;
	}
	else {
		imageSrc.w = SCREEN_W;
	}
	if (SCREEN_H > sence->MapH) {
		imageSrc.h = sence->MapH;
		imageSrc.y = 0;
	}
	else {
		imageSrc.h = SCREEN_H;
	}	
}