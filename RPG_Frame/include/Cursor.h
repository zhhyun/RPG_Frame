#ifndef  __Cursor__
#define __Cursor__
#include	<SDL.h>
#include	"InputSystem.h"
#include	"Math2.h"
#include	"Texture.h"
#include	"DEFINES.h"
namespace GameFrame {
	enum class PressState {
		None,
		PLeft,
		PRight,
		PMidle
	};
	class Cursor {
	public:
		Cursor(Texture* cur) :
			MouseTex(cur),
			mMousePos(SCREEN_W/2,SCREEN_H/2),
			mPressState(PressState::None)
		{  };
		~Cursor(){};
		Vector2 GetMousePos() { return mMousePos; };
		void SetMousePos(Vector2 pos) { mMousePos = pos; };
		void SetIsPress(PressState i) { mPressState = i; };
		PressState GetIsPress() { return mPressState; };
		void Draw(SDL_Renderer* renderder) {
			SDL_Rect imagerect = { 0,0,MouseTex->GetWidth(),MouseTex->GetHeight() };
			SDL_Rect rect = { mMousePos.x,mMousePos.y,MouseTex->GetWidth(),MouseTex->GetHeight() };
			SDL_RenderCopy(renderder, MouseTex->GetTexture(), &imagerect, &rect);
		};

	private:
		Vector2 mMousePos;
		Texture* MouseTex;
		PressState mPressState;
	};

}

#endif __Cursor__