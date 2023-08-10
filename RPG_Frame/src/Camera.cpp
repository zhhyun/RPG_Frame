#include "Camera.h"

GameFrame::Camera::Camera(Game* game):
	mGame(game)
{
	shot = new SDL_Rect();
	//�������ʼλ��,����û�и��¹����λ��
	shot->x = mGame->GetPlayer()->GetPosition().x - 0.5 * (shot->w - mGame->GetPlayer()->GetW());
	shot->y = mGame->GetPlayer()->GetPosition().y - 0.5 * (shot->w - mGame->GetPlayer()->GetH());
	shot->w = (int)SCREEN_W;
	shot->h = (int)SCREEN_H;
	imageSrc = *shot;
	PreImageSrc = imageSrc;
}

void GameFrame::Camera::UpdateCameraRect()
{
	MapObject* map = mGame->GetPlayer()->GetMapObject();
	PreImageSrc = imageSrc;
	//��������궼����map�е�����
	int tmpX = imageSrc.x;
	int tmpY = imageSrc.y;

	imageSrc.x = mGame->GetPlayer()->GetPosition().x + PreImageSrc.x - 0.5 * (shot->w - mGame->GetPlayer()->GetW());
	imageSrc.y = mGame->GetPlayer()->GetPosition().y + PreImageSrc.y - 0.5 * (shot->h - mGame->GetPlayer()->GetH());

	if (imageSrc.x < 0) {
		imageSrc.x = 0;
	}
	if (imageSrc.y < 0) {
		imageSrc.y = 0;
	}
	if (imageSrc.x + shot->w > map->MapW) {
		imageSrc.x = map->MapW - shot->w;
	}
	if (imageSrc.y + shot->h > map->MapH) {
		imageSrc.y = map->MapH - shot->h;
	}
}

