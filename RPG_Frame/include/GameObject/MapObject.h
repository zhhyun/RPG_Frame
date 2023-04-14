#ifndef __MapObject__
#define __MapObject__
#include "GameObject.h"
#include "ActorObject.h"
#include "DEFINES.h"
#include "CollisionComponent.h"

namespace GameFrame {
	class PhysWorld {
	public:
		void AddBox(CollisionComponent* box);
		void RemoveBox(CollisionComponent* box);
	//private:
		std::vector<class CollisionComponent*> mBox;
	};

	class MapObject : public GameObject {
	public:
		MapObject(class Game* game, const char* fileName, const std::string& name);
		~MapObject();

		void update() override;
		void Draw(SDL_Renderer* renderer) override;

		void AddMapObject(GameObject* gameobject);
		void RemoveMapObject(GameObject* gameobject);

		friend class CollisionComponent;

	private:
		int MapW;
		int MapH;
		PhysWorld* Pw;

	protected:
		std::vector<class GameObject*> mMapObjects;//存放地图上的游戏物体
	};
}

#endif __MapObject__