#include	"SpriteComponent.h"
#include	"GameObject.h"
#include	"Game.h"


GameFrame::SpriteComponent::SpriteComponent(GameObject* gameobject, int draworder):
	mTexture(nullptr),
	mDrawOrder(draworder),
	Component(gameobject)
{
	mGameObject->AddSpriteComponent(this);
}

GameFrame::SpriteComponent::~SpriteComponent()
{
}

void GameFrame::SpriteComponent::Draw(SDL_Renderer* renderer)
{

	// ÌùÍ¼¼´½«±»»æÖÆµÄÎ»ÖÃ

		int textureW;
		int textureH;
		int x =  mGameObject->GetPosition().x;
		int y =  mGameObject->GetPosition().y;

		SDL_QueryTexture(mTextures.begin()->second, nullptr, nullptr, &textureW, &textureH);

		SDL_Rect imageRect{ 0,0,textureW/3,textureH/4 };

		SDL_Rect dstRect{ x, y,textureW/3,textureH/4 };
		
		SDL_RenderCopy(renderer, mTextures.begin()->second, &imageRect, &dstRect);

	// »æÖÆÌùÍ¼£¨¿¼ÂÇÐý×ª£©
	//SDL_RenderCopyEx(renderer, mTexture, nullptr, &dstrect, mGameObject->GetRotation(), nullptr, SDL_FLIP_NONE);

}


void GameFrame::SpriteComponent::LoadTexture(std::string& fileName)
{
	{
		auto iter = mTextures.find(fileName);
		if (iter != mTextures.end()) {
			SDL_DestroyTexture(iter->second);
			mTextures.erase(iter);
		}
		SDL_Texture* tex = mGameObject->GetGame()->GetTexture(fileName);
		mTextures.emplace(fileName, tex);
	}
}
