#ifndef __PlayerObject__
#define __PlayerObject__
#include "ActorObject.h"

namespace GameFrame {
	class AnimSpriteComponent;
	class PlayerObject : public ActorObject {	
	public:
		PlayerObject(Game* game, Sence* map, const std::string& name);
		~PlayerObject();
		
		void update() override;
		void Draw(SDL_Renderer* renderer) override;
		void ProcessInput(InputSystem* keystate) override;
		
	private:
		AnimSpriteComponent* mAnimComponent;
	};
}
#endif __PlayerObject__