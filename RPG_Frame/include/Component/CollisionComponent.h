#ifndef __CollisionComponent__
#define __CollisionComponent__
#include	"Component.h"
#include	<vector>
#include	"Math2.h"

namespace GameFrame {
	class GameObject;

	class CollisionComponent : public Component {
	public:
		CollisionComponent(GameObject* gameobject);
		~CollisionComponent();
		
		void SetCollision(Vector2 vec, int h, int w);
		int CheckCollision();
		
		void update() override;
		//´¢´æÅö×²ÇøÓòµÄÈÝÆ÷
		SDL_Rect* mCollision;

		
	};
}
#endif __CollisionComponent__