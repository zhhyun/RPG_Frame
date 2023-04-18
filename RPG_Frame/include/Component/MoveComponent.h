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
		std::vector<KeyQueSate>			mReqKeys;

	private:
		Vector2								movdir;//ÒÆ¶¯ÏòÁ¿
		MovState							mMovState;
		float								Speed;
	};

}


#endif //__MoveComponent__
