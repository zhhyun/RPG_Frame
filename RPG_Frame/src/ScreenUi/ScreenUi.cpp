#include	"ScreenUi.h"
#include	"Game.h"
#include	"DEFINES.h"
#include	"Button.h"
#include	"Cursor.h"

GameFrame::ScreenUi::ScreenUi(Game* game, const std::string& filePath):
	mTexture(nullptr),
	keyOccup(UiKeyOccupy::ENone),
	GameObject(game)
{
	LoadTexture(filePath);
	mGame->PushUI(this);
}

GameFrame::ScreenUi::~ScreenUi()
{
}

void GameFrame::ScreenUi::close()
{
	mState = State::EDead;
}

void GameFrame::ScreenUi::update()
{
	Cursor* mouse = mGame->GetCursor();
	if (!mButtons.empty()) {
		//注意叠加图层判断，这里需要补充
		for (auto iter : mButtons) {
			if (iter->ContainsPoint(mouse->GetMousePos())) {
				if (mouse->GetIsPress() != PressState::None) {
					//如果鼠标在按钮上且按下
					iter->SetmHeighlighted(Button::ButtonState::Press);
					iter->OnClick();
				}
			}
		}
	}
}

void GameFrame::ScreenUi::Draw(SDL_Renderer* renderer)
{

}

void GameFrame::ScreenUi::LoadTexture(const std::string& NameInGame)
{
	mTexture = new Texture(NameInGame.c_str());
	mTexture->CreateFromTexture(mGame->GetTexture(NameInGame));
}
