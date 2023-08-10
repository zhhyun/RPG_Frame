#ifndef __PhysSpace__
#define __PhysSpace__
#include	"CollisionComponent.h"

//����ռ�Ӧ���м�����˭�������������任ʱ����ռ����ͷŻ��������ͷţ�

namespace GameFrame {
	class Game;

	class PhysSpace {
	public:
		PhysSpace(Game* game);
		~PhysSpace() {};

		void AddRigid(CollisionComponent* rigid);
		void RemoveRigid(CollisionComponent* rigid);
		//�������ռ�
		void ReleaseSpace();

		friend class CollisionComponent;
	private:
		std::vector<CollisionComponent*> Rigids;
		Game* mGame;
	};
}

#endif __PhysSpace__