#include	"PauseMenu.h"
#include	"InputSystem.h"
#include	"Game.h"
#include	"DEFINES.h"
#include	"Button.h"


GameFrame::PauseMenu::PauseMenu(Game* game, const std::string& fileName):
	ScreenUi(game, fileName)
{
	mGame->SetGameState(Game::GameState::EPause);
	keyOccup = UiKeyOccupy::EFull;
	Width = mTexture->GetWidth();
	Height = mTexture->GetHeight();
	ObjectPosion.x = SCREEN_W / 2 - Width / 2;
	ObjectPosion.y = SCREEN_H / 2 - Height / 2;
	
	Texture* tex = new Texture("ResumeButton");
	tex->CreateFromTexture(mGame->GetTexture("Button"));

	Vector2 vec;
	vec.x = SCREEN_W / 2 - tex->GetWidth() / 2;
	vec.y = ObjectPosion.y + 70;

	AddButton("Resume", vec, tex, [this]() {
		mGame->SetGameState(Game::GameState::EActive);
		close();
		});
}

GameFrame::PauseMenu::~PauseMenu()
{
}

void GameFrame::PauseMenu::Draw(SDL_Renderer* renderer)
{
	SDL_Rect imageRect{ 0,0,Width,Height };
	SDL_Rect dstRect{ ObjectPosion.x,ObjectPosion.y,Width,Height };
	SDL_RenderCopy(renderer, mTexture->GetTexture(), &imageRect, &dstRect);

	if (!mButtons.empty()) {
		for (auto iter : mButtons) {
			iter->Draw(renderer);
		}
	}
}

void GameFrame::PauseMenu::HandKeyPress(int key)
{
	if (key == SDLK_SPACE) {
		mGame->SetGameState(Game::GameState::EActive);
		close();
	}
}

void GameFrame::PauseMenu::AddButton(const std::string& name, Vector2 pos, Texture* tex, std::function<void()> OnClick)
{
	/*Button* b = new Button(name,this, pos, tex, OnClick);
	mButtons.emplace_back(b);*/
}
