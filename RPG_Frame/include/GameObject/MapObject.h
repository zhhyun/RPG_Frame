#ifndef __MapObject__
#define __MapObject__
#include "GameObject.h"
#include "ActorObject.h"
#include "DEFINES.h"
#include <unordered_map>
#include "CollisionComponent.h"

namespace GameFrame {
	class PhysWorld {
	public:
		void AddBox(CollisionComponent* box);
		void RemoveBox(CollisionComponent* box);
	//private:
		std::vector<CollisionComponent*> mBox;
	};

	class Layer {
	public:
		friend class MapObject;
		Vector2 TileIdParser(int id, SDL_Texture* tex);//������tile��ԭͼƬ��λ������
		Vector2 MapIdParser(int it);//������tileҪ���Ƶ���λ������
	private:
		const char* zlibcode;//unsigned char
		const char* tilePath = "tile";
		std::vector<int> Lcode;
		const char* LayerName={"none"};
		int width=0;//��λ��
		int height=0;
		int UpdateOrder = 0;
	};

	class MapObject : public GameObject {
	public:
		MapObject(class Game* game, const char* fileName, const std::string& name);
		~MapObject();

		void update() override;
		void Draw(SDL_Renderer* renderer) override;
		void DrawLayer(SDL_Renderer* renderer, Layer* layer);

		/*bool cmp(Layer* a, Layer* b) {
			return a->UpdateOrder < b->UpdateOrder;
		}*/

		void AddMapObject(GameObject* gameobject);
		void RemoveMapObject(GameObject* gameobject);

		void LoadMapXml(const char* filepath);
		void UncompressPy(Layer* layer);

		friend class CollisionComponent;

	private:
		const char* MapName;
		int MapW;
		int MapH;//��λ��
		int tilewidth;//��λ����
		int tileheight;
		PhysWorld* Pw;

	protected:
		std::vector<class GameObject*> mMapObjects;//��ŵ�ͼ�ϵ���Ϸ����
		std::vector<Layer*> mLayers;
	};
}

#endif __MapObject__