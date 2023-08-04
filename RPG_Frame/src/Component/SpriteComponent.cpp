#include	"SpriteComponent.h"
#include	"GameObject.h"
#include	"Game.h"
#include	"Texture.h"


GameFrame::SpriteComponent::SpriteComponent(GameObject* gameobject, int draworder):
	mTexture(nullptr),
	mDrawOrder(draworder),
	DrawTexWH(0,0),
	imageDst(0,0),
	Component(gameobject)
{
	mOwner->AddSpriteComponent(this);
}

GameFrame::SpriteComponent::~SpriteComponent()
{
}

void GameFrame::SpriteComponent::Draw(SDL_Renderer* renderer)
{
	int x =  mOwner->GetPosition().x;
	int y =  mOwner->GetPosition().y;

	SDL_Rect imageRect{ imageDst.x, imageDst.y, DrawTexWH.x, DrawTexWH.y };

	SDL_Rect dstRect{ x, y, DrawTexWH.x, DrawTexWH.y };
		
	SDL_RenderCopy(renderer, mTexture->GetTexture(), &imageRect, &dstRect);
}


void GameFrame::SpriteComponent::LoadTexture(std::string& fileName)
{
	{
		if (mTexture != NULL) {
			//Çå¿Õ
		}

		Texture* tex = new Texture;
		tex->CreateFromTexture(	mOwner->GetGame()->GetTexture(fileName));
		mTexture = tex;
		DrawTexWH.x = mTexture->GetWidth();
		DrawTexWH.y = mTexture->GetHeight();
	}
}

