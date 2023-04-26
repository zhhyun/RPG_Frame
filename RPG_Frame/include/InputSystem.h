#ifndef  __InputSystem__
#define __InputSystem__
#include	<SDL.h>
#include	"Math2.h"
namespace GameFrame {
	enum class ButtomState {
		ENone,
		EPressed,
		EReleased,
		EHeld
	};
	class CursorState {
	public:
		friend class InputSystem;
		friend class Game;
		Vector2 GetMousePos() { return mMousePos; };

	private:
		Vector2 mMousePos;
		Uint32 mCurrState;
		Uint32 mPrevState;
	};

	class KeyboradState {
	public:
		bool GetKeyValue(SDL_Scancode keycode) const;
		ButtomState GetKeyState(SDL_Scancode keycode) const;
		friend class InputSystem;
	private:
		const Uint8* mCurrState;
		Uint8 mPrevState[SDL_NUM_SCANCODES];//unsigned char
	};


	//InputState结构体保存所有的输入状态，包括鼠标键盘
	struct InputState {
		KeyboradState keyborad;
		CursorState		mouse;
	};

	class InputSystem {
	public:
		bool Initialize();
		void ShutDown();
		void PrepareUpdate();//更新预备工作
		void update();//更新键码和鼠标
		const InputState& GetState() const{ return mState; };

	private:
		InputState mState;
	};

	
}
#endif  __InputSystem__
