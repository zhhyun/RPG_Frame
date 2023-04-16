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
	/*�˴������״̬��*/
	class KeyboradState {
	public:
		bool GetKeyValue(SDL_Scancode keycode) const;
		ButtomState GetKeyState(SDL_Scancode keycode) const;
		friend class InputSystem;
	private:
		const Uint8* mCurrState;
		Uint8 mPrevState[SDL_NUM_SCANCODES];//unsigned char
	};

	//InputState�ṹ�屣�����е�����״̬������������
	struct InputState {
		KeyboradState keyborad;
	};

	class InputSystem {
	public:
		bool Initialize();
		void ShutDown();
		void PrepareUpdate();//����Ԥ������
		void update();//���¼���
		const InputState& GetState() const{ return mState; };

	private:
		InputState mState;
	};

	
}
#endif  __InputSystem__
