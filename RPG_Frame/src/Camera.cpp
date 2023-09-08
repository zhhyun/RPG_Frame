#include "Camera.h"
#include "Game.h"

GameFrame::Camera::Camera(Game* game):
	mGame(game)
{
	shot = new SDL_Rect();
	//�������ʼλ��
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
	//��������궼����map�е����꣬����������,PlayerObject������Ҳ�ǵ�ͼ����
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



	//�����ͼ�ȴ���С������Ҫ������ͷΪ��ͼ��Χ
	//�����ͼ�ȴ��ڴ���ͷ��Χȡ���ڷ�Χ
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