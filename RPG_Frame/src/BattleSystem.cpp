#include	"BattleSystem.h"
#include	"PlayerObject.h"
#include	"BattleComponent.h"
#include	"DEFINES.h"
GameFrame::BattleSystem::BattleSystem(Texture* Sence, Game* game, PlayerObject* player):
	mSence(Sence),
	mGame(game),
	mPlayer(player)
{
}

void GameFrame::BattleSystem::Draw(SDL_Renderer* renderer)
{
	//先画背景
	SDL_Rect imageRect{ 0,0,mSence->GetWidth()/2,mSence->GetHeight()/2};
	SDL_Rect dstRect{ 0, 0 ,SCREEN_W,SCREEN_H};
	SDL_RenderCopy(renderer, mSence->GetTexture(), &imageRect, &dstRect);
	imageRect.x = mSence->GetWidth() / 2;
	SDL_RenderCopy(renderer, mSence->GetTexture(), &imageRect, &dstRect);
	imageRect.x = 0;
	imageRect.y = mSence->GetHeight() / 2;
	SDL_RenderCopy(renderer, mSence->GetTexture(), &imageRect, &dstRect);
	imageRect.x = mSence->GetWidth() / 2;
	imageRect.y = mSence->GetHeight() / 2;
	SDL_RenderCopy(renderer, mSence->GetTexture(), &imageRect, &dstRect);
	//再画人物
	auto playertex = mPlayer->GetComponent<BattleComponent>()->GetBattleTexture();

	SDL_Rect imageRect2{ 0, 0, playertex->GetWidth(),playertex->GetHeight()};
	SDL_Rect dstRect2{ 100, 250 ,playertex->GetWidth(),playertex->GetHeight()};

	SDL_RenderCopy(renderer, playertex->GetTexture(), &imageRect2, &dstRect2);
}
