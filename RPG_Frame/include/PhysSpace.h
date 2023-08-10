#ifndef __PhysSpace__
#define __PhysSpace__
#include	"CollisionComponent.h"

//物理空间应该有几个？谁来创建？场景变换时物理空间是释放还是内容释放？

namespace GameFrame {
	class Game;

	class PhysSpace {
	public:
		PhysSpace(Game* game);
		~PhysSpace() {};

		void AddRigid(CollisionComponent* rigid);
		void RemoveRigid(CollisionComponent* rigid);
		//清空物理空间
		void ReleaseSpace();

		friend class CollisionComponent;
	private:
		std::vector<CollisionComponent*> Rigids;
		Game* mGame;
	};
}

#endif __PhysSpace__