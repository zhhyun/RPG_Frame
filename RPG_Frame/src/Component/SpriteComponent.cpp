#include	"SpriteComponent.h"
#include	"GameObject.h"
#include	"Game.h"


GameFrame::SpriteComponent::SpriteComponent(GameObject* gameobject, int draworder):
	mTexture(nullptr),
	mDrawOrder(draworder),
	Component(gameobject)
{
	mOwner->AddSpriteComponent(this);
}

GameFrame::SpriteComponent::~SpriteComponent()
{
}

void GameFrame::SpriteComponent::Draw(SDL_Renderer* renderer)
{

	// ÌùÍ¼¼´½«±»»æÖÆµÄÎ»ÖÃ

		int textureW;
		int textureH;
		int x =  mOwner->GetPosition().x;
		int y =  mOwner->GetPosition().y;

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
		SDL_Texture* tex = mOwner->GetGame()->GetTexture(fileName);
		mTextures.emplace(fileName, tex);
	}
}

SDL_Texture* GameFrame::SpriteComponent::GetTexture(std::string& fileName)
{
	return mTextures.find(fileName)->second;
}
