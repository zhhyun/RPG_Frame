#ifndef __PlayerObject__
#define __PlayerObject__
#include "ActorObject.h"

namespace GameFrame {
	class PlayerObject : public ActorObject {
	public:
		PlayerObject(Game* game, MapObject* map, const std::string& name);
		~PlayerObject();
		
		void update() override;
		void ProcessInput(InputSystem* keystate) override;
	private:
		
	};
}
#endif __PlayerObject__