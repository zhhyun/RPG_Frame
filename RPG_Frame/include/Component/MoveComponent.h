#ifndef __MoveComponent__
#define __MoveComponent__
#include "Component.h"
#include "Math2.h"

namespace GameFrame {
	class GameObject;
	class MoveComponent : public Component {
	public:
		MoveComponent(GameObject* gameobject);
		void ProcessInput(const uint8_t *keystate) override;
		void update() override;

	private:
		
	};

}


#endif //__MoveComponent__
