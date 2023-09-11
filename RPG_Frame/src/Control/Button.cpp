#include "Button.h"
#include "ScreenUi.h"
#include "Floating_Box.h"
#include "SpriteComponent.h"

GameFrame::Button::Button(const std::string& name, const std::string& TexName, Vector2 pos, GameObject* gameobject, std::function<void()> OnClick):
	mName(name),
	mFont(nullptr),
	mHeighlighted(ButtonState::None),
	mOnClick(OnClick),
	Control(gameobject, pos)
{
	mTexture = new Texture(name,BindObject->GetGame()->GetTexture(TexName));
	mWidth = mTexture->GetWidth();
	mHeight = mTexture->GetHeight()/3;
}

GameFrame::Button::~Button()
{
}

bool GameFrame::Button::ContainsPoint(const Vector2 cur)
{
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
		imageRect.y = 1 * mHeight;
	}
	else if (mHeighlighted == ButtonState::Press) {
		imageRect.y = 2 * mHeight;
	}
	SDL_Rect dstRect{ ObjectPosion.x,ObjectPosion.y,mWidth,mHeight };
	SDL_RenderCopy(renderder, mTexture->GetTexture(), &imageRect, &dstRect);
}

GameFrame::menuSlot::menuSlot(const std::string& name, const std::string& TexName, Vector2 pos, GameObject* gameobject, std::function<void()> OnClick):
	ReadyEquip(nullptr),
	Button(name,TexName,pos,gameobject,OnClick)
{
}

GameFrame::menuSlot::menuSlot(GameObject* gameobject):
	ReadyEquip(nullptr),
	Button("slot", (std::string)"defaultSlot", Vector2(42, 236), gameobject, 
		[this]() {
			//���slot����һ��С��������ʾ���еĿ�װ��װ��
			//auto boxui = new ScreenUi(BindObject->GetGame(), "PauseMenu");


		})
{
}

bool GameFrame::menuSlot::ContainsPoint(const Vector2 cur)
{
	if (!ReadyEquip) {
		if ((cur.x <= ObjectPosion.x + mWidth && cur.x >= ObjectPosion.x) && (cur.y <= ObjectPosion.y + mHeight && cur.y >= ObjectPosion.y)) {
			mHeighlighted = ButtonState::Select;
			return true;
		}
		else {
			mHeighlighted = ButtonState::None;
			return false;
		}
	}
	else {
		//��slot�Աߴ���һ����Ϣ����ʾװ����Ϣ
	}
}

void GameFrame::menuSlot::Draw(SDL_Renderer* renderder)
{
	//���slot�Ѿ�����������ʾ�󶨶�������
	//���slotû�о�������ִ��Ĭ�ϻ�ͼ����
	if (ReadyEquip) {
		SDL_Rect imageRect = ReadyEquip->GetRectFromTex(); 
		SDL_Rect dstRect{ ObjectPosion.x,ObjectPosion.y,mWidth,mHeight };
		SDL_RenderCopy(renderder, ReadyEquip->GetEquipTex(), &imageRect, &dstRect);
	}
	else {
		/*���º�����buttonԭ����*/
		SDL_Rect imageRect{ 0,0,mWidth,mHeight };
		if (mHeighlighted == ButtonState::Select) {
			imageRect.y = 1 * mHeight;
		}
		else if (mHeighlighted == ButtonState::Press) {
			imageRect.y = 2 * mHeight;
		}
		SDL_Rect dstRect{ ObjectPosion.x,ObjectPosion.y,mWidth,mHeight };
		SDL_RenderCopy(renderder, mTexture->GetTexture(), &imageRect, &dstRect);
	}
}

void GameFrame::menuSlot::update()
{
	
}
