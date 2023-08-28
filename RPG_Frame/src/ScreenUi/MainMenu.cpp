#include "MainMenu.h"

GameFrame::MainMenu::MainMenu(Game* game) :
	ScreenUi(game, MainBoard)
{
	ObjectPosion.x = 200;
	ObjectPosion.y = 200;
}

void GameFrame::MainMenu::Draw(SDL_Renderer* renderer)
{
	DrawHeroData(renderer);
}

void GameFrame::MainMenu::DrawHeroData(SDL_Renderer* renderer)
{
	auto player = mGame->GetPlayer();

}
