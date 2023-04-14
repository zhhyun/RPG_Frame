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
		void SetCollision(Vector2 vec);
		int CheckCollision();
		void OnUpdateWorldTransform();

		//´¢´æÅö×²ÇøÓòµÄÈÝÆ÷
		friend class CollisionComponent;
	private:
		SDL_Rect	mCollision;
		bool		IsUpdateFromObject;
	};
}
#endif __CollisionComponent__