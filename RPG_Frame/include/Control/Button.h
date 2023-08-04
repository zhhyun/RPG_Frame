#ifndef __Button__
#define __Button__
#include	"Math2.h"
#include	<SDL.h>
#include	<string>
#include	<functional>
#include	"Texture.h"

namespace GameFrame {
	class Button {
	public:
		enum class ButtonState {
			None,
			Press,
			Select
		};
		Button(const std::string& name,
			Vector2 pos,
			Texture* tex,
			/*class Font* font,*/
			std::function<void()> OnClick);
		~Button();
		bool ContainsPoint(const Vector2 cur);
		void OnClick();
		void Draw(SDL_Renderer* renderder);
		void SetmHeighlighted(ButtonState is) { mHeighlighted = is; };

	private:
		std::function<void()> mOnClick;//�ص�����
		std::string mName;
		Vector2 Pos;
		Texture* mTexture;
		class Font* mFont;//�����ѡ
		int mHeight;
		int mWidth;
		ButtonState mHeighlighted;//������������棬���Ǹ���
	};
}

#endif __Button__
