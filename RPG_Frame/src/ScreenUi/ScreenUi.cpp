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
		//ע�����ͼ���жϣ�������Ҫ����
		for (auto iter : mButtons) {
			if (iter->ContainsPoint(mouse->GetMousePos())) {
				if (mouse->GetIsPress() != PressState::None) {
					//�������ڰ�ť���Ұ���
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
