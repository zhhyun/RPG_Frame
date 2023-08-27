#include "Button.h"

GameFrame::Button::Button(const std::string& name, Vector2 pos, Texture* tex, std::function<void()> OnClick):
	mName(name),
	ObjectPosion(pos),
	mTexture(tex),
	mFont(nullptr),
	mHeighlighted(ButtonState::None),
	mOnClick(OnClick)
{
	mWidth = mTexture->GetWidth();
	mHeight = mTexture->GetHeight()/3;
}

GameFrame::Button::~Button()
{
}

bool GameFrame::Button::ContainsPoint(const Vector2 cur)
{
	//mHeighlighted = ButtonState::None;
	if ((cur.x <= ObjectPosion.x + mWidth && cur.x >= ObjectPosion.x) && (cur.y <= ObjectPosion.y + mHeight && cur.y >= ObjectPosion.y)) {
		mHeighlighted = ButtonState::Select;
		return true;
	}
	else {
		mHeighlighted = ButtonState::None;
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
	if (mHeighlighted == ButtonState::Select) {
		imageRect.y = 1*mHeight;
	}
	else if (mHeighlighted == ButtonState::Press) {
		imageRect.y = 2 * mHeight;
	}
	SDL_Rect dstRect{ ObjectPosion.x,ObjectPosion.y,mWidth,mHeight };
	SDL_RenderCopy(renderder, mTexture->GetTexture(), &imageRect, &dstRect);
}
