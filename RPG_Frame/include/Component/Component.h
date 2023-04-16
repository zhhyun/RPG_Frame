#ifndef __Component__
#define __Component__

#include	<SDL.h>

namespace GameFrame{

	class GameObject;
	class InputSystem;
	class Component {
	public:
		Component(class GameObject* gameobject);
		virtual ~Component();
		virtual void update();
		class GameObject* GetGameObject();
		virtual void ProcessInput(const InputSystem* keystate);

	protected:
		class GameObject*				mOwner;
		int								mUpdateOder;
	};
}

#endif // !__Component__



