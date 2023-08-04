#ifndef __MoveComponent__
#define __MoveComponent__
#include "Component.h"
#include "Math2.h"
#include <vector>
#include <SDL.h>
#include "InputSystem.h"

namespace GameFrame {
	class GameObject;
	typedef struct KeyQueSate{
		SDL_Scancode key;
		ButtomState keystate;
	}KeyQueSate;
	class MoveComponent : public Component {
	public:
		MoveComponent(GameObject* gameobject);
		enum class MovState {
			MovStart,
			MovStop,
			MovHeld,
			Idle
		};
		void ProcessInput(const InputSystem* keystate);
		void SetSpeed(float speed);
		float GetSpeed();
		void update() override;
		bool MoveTo(Vector2 DestPos);//�ƶ�ָ���Ĭ���ٶȽ������Զ��ƶ���destpos������ɺ󷵻�1
		std::vector<KeyQueSate>			mReqKeys;

	private:
		Vector2								movdir;//�ƶ�����
		MovState							mMovState;
		float								Speed;
		bool								IsAcceptKey;
	};

}


#endif //__MoveComponent__
