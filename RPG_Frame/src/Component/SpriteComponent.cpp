#include "SpriteComponent.h"
#include	"GameObject.h"


GameFrame::SpriteComponent::SpriteComponent(GameObject* gameobject, int draworder):
	mTexture(nullptr),
	mTexWidth(0),
	mTexHeight(0),
	mDrawOrder(draworder),
	Component(gameobject)
{
}

GameFrame::SpriteComponent::~SpriteComponent()
{
}

void GameFrame::SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (!mTexture)
	{
		return;
	}

	// ��ͼ���������Ƶ�λ��
	SDL_Rect dstrect;
	dstrect.w = static_cast<int>(mTexWidth * mGameObject->GetScale().x);
	dstrect.h = static_cast<int>(mTexHeight * mGameObject->GetScale().y);
	dstrect.x = static_cast<int>(mGameObject->GetPosition().x);
	dstrect.y = static_cast<int>(mGameObject->GetPosition().y);

		int textureW;
		int textureH;
		int x =  mGameObject->GetPosition().x;
		int y =  mGameObject->GetPosition().y;

		SDL_QueryTexture(mTexture, nullptr, nullptr, &textureW, &textureH);

		SDL_Rect imageRect{ 0,0,textureW/3,textureH/4 };

		SDL_Rect dstRect{ x, y,textureW/3,textureH/4 };

		SDL_RenderCopy(renderer, mTexture, &imageRect, &dstRect);

	// ������ͼ��������ת��
	//SDL_RenderCopyEx(renderer, mTexture, nullptr, &dstrect, mGameObject->GetRotation(), nullptr, SDL_FLIP_NONE);

}

void GameFrame::SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// ����ͼ�в�ѯ��ͼ�Ŀ�͸�
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
