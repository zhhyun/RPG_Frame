#ifndef __PhysSpace__
#define __PhysSpace__
#include	"Game.h"

namespace GameFrame {
	class Shape;
	class RectShape;
	class CollisionComponent;

	class PhysSpace {
	public:
		PhysSpace(Game* game);
		~PhysSpace() {};

		void RegisterCollisionComponent(CollisionComponent* rigid);
		void RemoveRigid(CollisionComponent* rigid);
		//清空物理空间
		void ReleaseSpace();
		void Update();

		friend class CollisionComponent;
	private:
		std::vector<CollisionComponent*> Rigids;
		Game* mGame;
		void CheckCollisionsBetweenComponents(CollisionComponent* componentA, CollisionComponent* componentB);
	};
}

#endif __PhysSpace__