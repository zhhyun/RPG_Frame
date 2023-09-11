#ifndef __Button__
#define __Button__
#include	"Math2.h"
#include	<SDL.h>
#include	<string>
#include	<functional>
#include	"Texture.h"
#include	"GameObject.h"
#include	"Game.h"
#include	"Control.h"
	
#define SLOT_SIDE_LENGTH 27

namespace GameFrame {
	//应该注册创建者，button控件和创建者绑定在一起
	class Button : public Control{
	public:
		enum class ButtonState {
			None,
			Press,
			Select
		};
		Button(const std::string& name,
			const std::string& TexName,//texName is used for searching tex
			Vector2 pos,
			GameObject* gameobject,
			std::function<void()> OnClick);

		~Button();
		virtual bool ContainsPoint(const Vector2 cur);
		void OnClick();
		virtual void Draw(SDL_Renderer* renderder);
		void SetmHeighlighted(ButtonState is) { mHeighlighted = is; };

	protected:
		std::function<void()> mOnClick;//回调函数
		std::string mName;
		Texture* mTexture;
		class Font* mFont;//字体可选
		int mHeight;
		int mWidth;
		ButtonState mHeighlighted;//如果鼠标放在上面，则标记高亮
	};


	class menuSlot : public Button{
	public:
		menuSlot(const std::string& name,
			const std::string& TexName,
			Vector2 pos,
			GameObject* gameobject,
			std::function<void()> OnClick);
		menuSlot(GameObject* gameobject);

		bool ContainsPoint(const Vector2 cur) override;
		void Draw(SDL_Renderer* renderder) override;
		void update() override;

		void SetEquip(Equipments* equip) {
			ReadyEquip = equip;
		};

		bool UninstallEquip() {
			if (!ReadyEquip) {
				return false;
			}
			else {
				ReadyEquip = nullptr;
				return true;
			}
		}

		void SetOnclickFunc(std::function<void()> OnClick) {
			mOnClick = OnClick;
		}

	private:
		Equipments* ReadyEquip;
	};
}

#endif __Button__
