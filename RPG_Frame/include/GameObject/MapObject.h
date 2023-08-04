#ifndef __MapObject__
#define __MapObject__
#include "GameObject.h"
#include "ActorObject.h"
#include "DEFINES.h"
#include <unordered_map>
#include "CollisionComponent.h"
#include <string>

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
		Layer();
		friend class MapObject;
		Vector2 TileIdParser(int id, SDL_Texture* tex);//������tile��ԭͼƬ��λ������
		Vector2 MapIdParser(int it);//������tileҪ���Ƶ���λ������
	private:
		const char* zlibcode;//unsigned char
		const std::string tilePath = "sprite/tilesheet_0.png";//ͼ���õ���tile�ļ�·��
		std::vector<int> Lcode;
		const char* LayerName={"none"};
		SDL_Texture* LayerTex;//��ͼ�㵼���������
		int grid_LayerWidth = 0;//����������ĳߴ�
		int grid_LayerHeight = 0;
		//ע�⣬�������ز�ԭ���ߴ磬ʵ���������ɵ�ͼʱ�������Ҫ����ͼ��Ĵ�С����ҪŪ��
		int pixel_layerWidth = 0;//�����ؼ����ĳߴ�
		int pixel_layerHeight = 0;
		int layerTileW ;
		int layerTileH ;
		int UpdateOrder = 0;
	};






	class MapObject : public GameObject {
	public:
		MapObject(class Game* game, const char* fileName, const std::string& name);
		~MapObject();
		friend class Camera;

		void update() override;
		void Draw(SDL_Renderer* renderer) override;

		void AddMapObject(GameObject* gameobject);
		void RemoveMapObject(GameObject* gameobject);

		void LoadMapXml(const char* filepath);//����ͼ�ļ���ȡ������ͼ��˳��ֲ㱣�浽mlayers��
		void UncompressPy(Layer* layer);//��ѹ��ͼ����
		SDL_Texture* PreLayerTexBlit(SDL_Renderer* renderer, Layer* layer);
		friend class CollisionComponent;

	private:
		const char* MapName;
		SDL_Texture* MapTex;
		int MapTileW; // �ø�����ĵ�ͼ�ߴ�
		int MapTileH;
		int tileW;//��ͼ�ﵥ��������سߴ�//���ڵ�ͼ�ĸ��С���زĲ�һ��������Ҫ��������
		int tileH;
		int MapW;//��ͼ���سߴ�
		int MapH;
		PhysWorld* Pw;
	protected:
		void DrawLayer(SDL_Renderer* renderer, Layer* layer);
		std::vector<class GameObject*> mMapObjects;//��ŵ�ͼ�ϵ���Ϸ����
		std::vector<Layer*> mLayers;
	};
}

#endif __MapObject__