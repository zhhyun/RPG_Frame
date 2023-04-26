#include "Dialogbox.h"
#include "Game.h"
#include "DEFINES.h"

GameFrame::Dialogbox::Dialogbox(Game* game, const std::string& fileName, const std::string& portrait, class Font* font) :
	Portrait(nullptr),
	CurrText(0),
	CurrTextTex(nullptr),
	mTextFont(font),
	ScreenUi(game, fileName)
{
	Portrait = new Texture("portrait"); 
	Portrait->CreateFromTexture(mGame->GetTexture(portrait));
	keyOccup = UiKeyOccupy::EFull;
	Width = mTexture->GetWidth();
	Height = mTexture->GetHeight();
}

GameFrame::Dialogbox::~Dialogbox()
{
}

void GameFrame::Dialogbox::HandKeyPress(int key)
{
	if (key != SDLK_RETURN)
		return;
	else {
		if (mTexts.size() > CurrText) {
			NextText();
		}
		else {
			close();
		}
	}
}

void GameFrame::Dialogbox::NextText()
{
	CurrText++;
	CurrTextTex  = mTextFont->RenderText( mTexts[CurrText] , 255,255,255,14);
}

void GameFrame::Dialogbox::Draw(SDL_Renderer* renderer)
{
	SDL_Rect imageRect1{ 191,1899,668,1064 };
	SDL_Rect dstRect1{ 0,200 , 334,532 };
	SDL_RenderCopy(renderer, Portrait->GetTexture(), &imageRect1, &dstRect1);

	SDL_Rect imageRect{ 0,0,Width,Height };
	SDL_Rect dstRect{ mPos.x+120,SCREEN_H - 300 ,Width,Height };
	SDL_RenderCopy(renderer, mTexture->GetTexture(), &imageRect, &dstRect);
	if (!mTexts.empty()) {
		SDL_Rect imageRect2{ 0,0,CurrTextTex->GetWidth(),CurrTextTex->GetHeight()};
		SDL_Rect dstRect2{ mPos.x + 150,SCREEN_H - 280 ,CurrTextTex->GetWidth(),CurrTextTex->GetHeight() };
		SDL_RenderCopy(renderer, CurrTextTex->GetTexture(), &imageRect2, &dstRect2);
	}	
}

void GameFrame::Dialogbox::AddText(const std::string& text)
{
	if (mTexts.empty()) {
		CurrTextTex = mTextFont->RenderText(text, 255, 105, 180, 36);
	}
	mTexts.emplace_back(text);
}
