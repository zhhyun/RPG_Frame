#ifndef  __InputSystem__
#define __InputSystem__
#include	<SDL.h>
namespace GameFrame {
	enum class ButtomState {
		ENone,
		EPressed,
		EReleased,
		EHeld
	};
	/*此处有鼠标状态类*/
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
	};

	class InputSystem {
	public:
		bool Initialize();
		void ShutDown();
		void PrepareUpdate();//更新预备工作
		void update();//更新键码
		const InputState& GetState() const{ return mState; };

	private:
		InputState mState;
	};

	
}
#endif  __InputSystem__
