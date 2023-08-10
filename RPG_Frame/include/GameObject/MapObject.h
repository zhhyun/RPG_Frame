#ifndef __MapObject__
#define __MapObject__
#include	"GameObject.h"
#include	"ActorObject.h"
#include	"DEFINES.h"
#include	<unordered_map>
#include	<string>
#include	<json.hpp>
#include	<fstream>
#include	"CollisionComponent.h"


namespace GameFrame {
	//�����ͼ�ϵ���ײ����
	//��ײ����Ŀǰ֧�־��Ρ�Բ�Ρ��߶�
	class PhysWorld {
	public:
		void AddBox(CollisionComponent* box);
		void RemoveBox(CollisionComponent* box);
		std::vector<CollisionComponent*> mBox;
	};

	class Layer {
	public:
		Layer();
		~Layer(){};
		friend class MapObject;
		//������tile��ԭͼƬ��λ������
		Vector2 TileIdParser(int id, SDL_Texture* tex);
		//������tileҪ���Ƶ���λ������
		Vector2 MapIdParser(int it);
	private:
		const char* zlibcode;//unsigned char
		//ͼ���õ���tile�ļ�·��,Ӧ����ʵ����ʱ����(Ŀǰδ����)
		const std::string tilePath = "sprite/tilesheet_0.png";
		std::vector<int> Lcode;
		const char* LayerName={"none"};
		//��ͼ�㵼���������
		SDL_Texture* LayerTex;
		//����������Ŀ��
		int mesh_LayerWidth = 0;
		//����������ĸ߶�
		int mesh_LayerHeight = 0;

		//ע�⣬�������ز�ԭ���ߴ磬ʵ���������ɵ�ͼʱ�������Ҫ����ͼ��Ĵ�С����ҪŪ��
		//�����ؼ����Ŀ��
		int pixel_layerWidth = 0;
		//�����ؼ����ĸ߶�
		int pixel_layerHeight = 0;

		int layerTileW ;
		int layerTileH ;
		int UpdateOrder = 0;
	};






	class MapObject : public GameObject {
	public:
		MapObject(class Game* game, const std::string& fileName, const std::string& name);
		~MapObject();
		friend class Camera;

		void update() override;
		void Draw(SDL_Renderer* renderer) override;

		void AddMapObject(GameObject* gameobject);
		void RemoveMapObject(GameObject* gameobject);

		void LoadMapXml(const std::string& filepath);//����ͼ�ļ���ȡ������ͼ��˳��ֲ㱣�浽mlayers��
		SDL_Texture* PreLayerTexBlit(SDL_Renderer* renderer, Layer* layer);
		void SetTileAttr();//���ø��ӵ����Ժ��¼�
		friend class CollisionComponent;

	private:
		const char* MapName;
		std::string Map_id;
		SDL_Texture* MapTex;
		int MapTileW; // �ø�����ĵ�ͼ�ߴ�
		int MapTileH;
		int tileW;//��ͼ�ﵥ��������سߴ�//���ڵ�ͼ�ĸ��С���زĲ�һ��������Ҫ��������
		int tileH;
		//��ͼ���ؿ�
		int MapW;
		//��ͼ���ظ�
		int MapH;

		//��ײ����
		PhysWorld* CollisionsInMap;

		void UncompressTile_By_Py(Layer* layer);//��ѹ��ͼ����
		//��json�ļ����ȡ��ͼ����ײ����
		int LoadCollision(const std::string& path);

	protected:
		void DrawLayer(SDL_Renderer* renderer, Layer* layer);
		std::vector<class GameObject*> mObjectsInMap;//��ŵ�ͼ�ϵ���Ϸ����
		std::vector<Layer*> mLayers;
	};
}

#endif __MapObject__