#include "MainMenu.h"
#include "Cursor.h"
GameFrame::MainMenu::MainMenu(Game* game) :
	ScreenUi(game, MainBoard)
{
	mFont = mGame->GetFont("QingNiaoHuaGuang");
	ObjectPosion.x = 200;
	ObjectPosion.y = 20;
	Width = mTexture->GetWidth();
	Height = mTexture->GetHeight();
	BindPlayer = mGame->GetPlayer();
	menuSlot* slot1 = new menuSlot(this);
	menuSlot* slot2 = new menuSlot(this);
	menuSlot* slot3 = new menuSlot(this);
	menuSlot* slot4 = new menuSlot(this);
	AddButton(slot1);
}


void GameFrame::MainMenu::AddButton(Button* button)
{
	mButtons.emplace_back(button);
}

void GameFrame::MainMenu::Draw(SDL_Renderer* renderer)
{
	SDL_Rect imageRect{ 0,0,Width,Height };
	SDL_Rect dstRect{ ObjectPosion.x,ObjectPosion.y,Width,Height };
	SDL_RenderCopy(renderer, mTexture->GetTexture(), &imageRect, &dstRect);

	if (!mButtons.empty()) {
		for (auto iter : mButtons) {
			iter->Draw(renderer);
		}
	}
	DrawHeroData(renderer);
	DrawHeroName(renderer);
	DrawHpBar(renderer);
	DrawLvBar(renderer);
	DrawMpBar(renderer);
}

void GameFrame::MainMenu::update()
{
	Cursor* mouse = mGame->GetCursor();	
	auto playerEquip = BindPlayer->GetreadyEquip();

	if (playerEquip.slot1) {
		dynamic_cast<menuSlot*>(mButtons[0])->SetEquip(playerEquip.slot1);
	}
	/*if (playerEquip.slot2) {
		dynamic_cast<menuSlot*>(mButtons[1])->SetEquip(playerEquip.slot2);
	}
	if (playerEquip.slot3) {
		dynamic_cast<menuSlot*>(mButtons[2])->SetEquip(playerEquip.slot3);
	}*/

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

void GameFrame::MainMenu::DrawHeroData(SDL_Renderer* renderer)
{
	std::string AckSTR = std::to_string(BindPlayer->GetACK());
	Texture* tex = mFont->RenderText(AckSTR, Black, 30);
	SDL_Rect dstRect{ ObjectPosion.x + 120,ObjectPosion.y + 130,tex->GetWidth(),tex->GetHeight()};
	SDL_Rect srcRect = tex->GetTextureRect();
	SDL_RenderCopy(renderer,tex->GetTexture(), &srcRect, &dstRect);

	std::string DefSTR = std::to_string(BindPlayer->GetDEF());
	Texture* deftex = mFont->RenderText(DefSTR, Black, 30);
	SDL_Rect dstRect2{ ObjectPosion.x + 120 + 180,ObjectPosion.y + 130,deftex->GetWidth(),deftex->GetHeight() };
	SDL_Rect srcRect2 = deftex->GetTextureRect();
	SDL_RenderCopy(renderer, deftex->GetTexture(), &srcRect2, &dstRect2);
}

void GameFrame::MainMenu::DrawHeroName(SDL_Renderer* renderer)
{
	std::string PlayerName = BindPlayer->GetActorName();
	Texture* tex = mFont->RenderText(PlayerName, Orange, 30);
	SDL_Rect dstRect{ ObjectPosion.x + 50,ObjectPosion.y + 10,tex->GetWidth(),tex->GetHeight() };
	SDL_Rect srcRect = tex->GetTextureRect();
	SDL_RenderCopy(renderer, tex->GetTexture(), &srcRect, &dstRect);
}

void GameFrame::MainMenu::DrawHpBar(SDL_Renderer* renderer)
{
}

void GameFrame::MainMenu::DrawMpBar(SDL_Renderer* renderer)
{
}

void GameFrame::MainMenu::DrawLvBar(SDL_Renderer* renderer)
{
}

void GameFrame::MainMenu::HandKeyPress(int key)
{
	if (key == SDLK_SPACE)
		close();
}
