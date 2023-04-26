#include "Button.h"

GameFrame::Button::Button(const std::string& name, Vector2 pos, Texture* tex, std::function<void()> OnClick):
	mName(name),
	Pos(pos),
	mTexture(tex),
	mFont(nullptr),
	mHeighlighted(false)
{
	mWidth = mTexture->GetWidth();
	mHeight = mTexture->GetHeight()/3;
}

GameFrame::Button::~Button()
{
}

bool GameFrame::Button::ContainsPoint(const Vector2 cur)
{
	mHeighlighted = true;
	if ((cur.x <= Pos.x + mWidth && cur.x >= Pos.x) && (cur.y <= Pos.y + mHeight && cur.y >= Pos.y)) {
		mHeighlighted = true;
		return true;
	}
	else {
		mHeighlighted = false;
		return false;
	}
}

void GameFrame::Button::OnClick()
{
	if (mOnClick) {
		mOnClick();
	}
}

void GameFrame::Button::Draw(SDL_Renderer* renderder)
{
	SDL_Rect imageRect{ 0,0,mWidth,mHeight };
	if (mHeighlighted) {
		imageRect.y = 1*mHeight;
	}

	SDL_Rect dstRect{ Pos.x,Pos.y,mWidth,mHeight };
	SDL_RenderCopy(renderder, mTexture->GetTexture(), &imageRect, &dstRect);
}
