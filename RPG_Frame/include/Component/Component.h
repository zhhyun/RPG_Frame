#ifndef __Component__
#define __Component__

#include	<SDL.h>

namespace GameFrame{

	class GameObject;

	class Component {
	public:
		Component(class GameObject* gameobject);
		virtual ~Component();
		virtual void update();
		class GameObject* GetGameObject();
		virtual void ProcessInput(const uint8_t* keystate);

	protected:
		class GameObject*				mGameObject;
		int								mUpdateOder;
	};
}

#endif // !__Component__



