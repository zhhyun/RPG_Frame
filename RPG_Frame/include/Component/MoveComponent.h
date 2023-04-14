#ifndef __MoveComponent__
#define __MoveComponent__
#include "Component.h"
#include "Math2.h"

namespace GameFrame {
	class GameObject;
	class MoveComponent : public Component {
	public:
		MoveComponent(GameObject* gameobject);

		enum class MovDir {
			idle,
			toUp,
			toDown,
			toLeft,
			toRight
		};
		void ProcessInput(const uint8_t* keystate);
		void update() override;

	private:
		bool								IsMoving;
		MovDir								movdir;
	};

}


#endif //__MoveComponent__
