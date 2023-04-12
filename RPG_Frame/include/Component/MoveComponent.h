#ifndef __MoveComponent__
#define __MoveComponent__
#include "Component.h"
#include "Math2.h"

namespace GameFrame {
	class GameObject;
	class MoveComponent : public Component {
	public:
		MoveComponent(GameObject* gameobject);
		void ProcessInput(const SDL_Keycode key);
		void ProcessInput2(const uint8_t* keystate);
		void update() override;

	private:
		
	};

}


#endif //__MoveComponent__
