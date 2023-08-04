#include "Camera.h"

GameFrame::Camera::Camera(Game* game):
	mGame(game)
{
	shot.x = mGame->GetPlayer()->GetPosition().x - 0.5 * (shot.w - mGame->GetPlayer()->GetW());
	shot.y = mGame->GetPlayer()->GetPosition().y - 0.5 * (shot.w - mGame->GetPlayer()->GetH());
	shot.w = (int)SCREEN_W;
	shot.h = (int)SCREEN_H;
	imageSrc = new SDL_Rect();
}

const SDL_Rect* GameFrame::Camera::GetImageRect(MapObject* map)
{
	//这里的坐标都是在map中的坐标
	imageSrc->x = mGame->GetPlayer()->GetPosition().x - 0.5 * (shot.w - mGame->GetPlayer()->GetW());
	imageSrc->y = mGame->GetPlayer()->GetPosition().y - 0.5 * (shot.w - mGame->GetPlayer()->GetH());
	if (imageSrc->x < 0) {
		imageSrc->x = 0;
	}
	if (imageSrc->y < 0) {
		imageSrc->y = 0;
	}
	if (imageSrc->x + shot.w > map->MapW) {
		imageSrc->x = map->MapW - shot.w;
	}
	if (imageSrc->y + shot.h > map->MapH) {
		imageSrc->y = map->MapH - shot.h;
	}
	imageSrc->w = shot.w;
	imageSrc->h = shot.h;
	return imageSrc;
}
