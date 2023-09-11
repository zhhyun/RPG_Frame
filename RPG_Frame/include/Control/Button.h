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
	//Ӧ��ע�ᴴ���ߣ�button�ؼ��ʹ����߰���һ��
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
		std::function<void()> mOnClick;//�ص�����
		std::string mName;
		Texture* mTexture;
		class Font* mFont;//�����ѡ
		int mHeight;
		int mWidth;
		ButtonState mHeighlighted;//������������棬���Ǹ���
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
