#include	"ScreenUi.h"
#include	"Game.h"
#include	"DEFINES.h"
#include	"Button.h"
#include	"Cursor.h"

GameFrame::ScreenUi::ScreenUi(Game* game, const std::string& fileName):
	mGame(game),
	mPos(0,0),
	mTexture(nullptr),
	keyOccup(UiKeyOccupy::ENone),
	mState(UiState::EActive)
{
	LoadTexture(fileName);
	mGame->PushUI(this);
}

GameFrame::ScreenUi::~ScreenUi()
{
}

void GameFrame::ScreenUi::close()
{
	mState = UiState::EClosing;
}

void GameFrame::ScreenUi::update()
{
	Cursor* mouse = mGame->GetCursor();
	if (!mButtons.empty()) {
		for (auto iter : mButtons) {
			iter->ContainsPoint(mouse->GetMousePos());
		}
	}
}

void GameFrame::ScreenUi::Draw(SDL_Renderer* renderer)
{

}

void GameFrame::ScreenUi::LoadTexture(const std::string& fileName)
{
	mTexture = new Texture("PauseMenu");
	mTexture->CreateFromTexture(mGame->GetTexture(fileName));
}
