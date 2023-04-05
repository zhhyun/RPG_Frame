#ifndef __BattleComponent__
#define __BattleComponent__
#include "Component.h"

namespace GameFrame {
	class GameObject;
	class BattleComponent : public Component {
	public:
		BattleComponent(GameObject* gameobject);
		void ProcessInput(const uint8_t* keystate) override;


	private:

	};
}

#endif __BattleComponent__