#ifndef __InputComponent__
#define __InputComponent__
#include "Component.h"

namespace GameFrame {
	class GameObject;
	class InputSystem;
	class InputComponent : public Component {
	public:
		InputComponent(GameObject* gameobject);
		//void ProcessInput(const SDL_Keycode key);
		void ProcessInput(const uint8_t* keystate);
		void ProcessInput(InputSystem* keystate);
		void SetRequestCom(Component* component);
		void SetIsMain(bool is);

	private:
		bool IsMain;
		class Component *RequestComp;
	};
}

#endif __InputComponent__