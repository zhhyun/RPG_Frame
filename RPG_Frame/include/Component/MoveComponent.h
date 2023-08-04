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
		bool MoveTo(Vector2 DestPos);//移动指令，以默认速度将人物自动移动到destpos处，完成后返回1
		std::vector<KeyQueSate>			mReqKeys;

	private:
		Vector2								movdir;//移动向量
		MovState							mMovState;
		float								Speed;
		bool								IsAcceptKey;
	};

}


#endif //__MoveComponent__
