#ifndef __MapObject__
#define __MapObject__
#include "GameObject.h"
#include "ActorObject.h"
#include "DEFINES.h"


namespace GameFrame {
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
		/*int map[ScreenW/32][ScreenH/32];
		int RunMap[ScreenW/32][ScreenH/32];*/

	protected:
		std::vector<class GameObject*> mMapObjects;//存放地图上的游戏物体
	};
}

#endif __MapObject__