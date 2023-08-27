#ifndef __Component__
#define __Component__
#include	<functional>
#include	<string>
#include	<SDL.h>


namespace GameFrame{
	class GameObject;
	class InputSystem;

	class Component {
	public:
		Component(GameObject* gameobject);
		virtual ~Component();
		virtual void update() {};
		GameObject* GetGameObject();
		virtual void ProcessInput(const InputSystem* keystate);

		void SubscribeToEvent(const std::string& id, std::function<void()> callback);

	protected:
		GameObject*				mOwner;
		int						mUpdateOder;
	};
}

#endif // !__Component__



