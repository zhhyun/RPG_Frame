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
		Vector2 TileIdParser(int id, SDL_Texture* tex);//解析出tile在原图片的位置坐标
		Vector2 MapIdParser(int it);//解析出tile要绘制到的位置坐标
	private:
		const char* zlibcode;//unsigned char
		const std::string tilePath = "sprite/tilesheet_0.png";//图层用到的tile文件路径
		std::vector<int> Lcode;
		const char* LayerName={"none"};
		SDL_Texture* LayerTex;//本图层导出后的纹理
		int grid_LayerWidth = 0;//用网格计量的尺寸
		int grid_LayerHeight = 0;
		//注意，这里是素材原本尺寸，实际运行生成地图时会根据需要放缩图层的大小，不要弄混
		int pixel_layerWidth = 0;//用像素计量的尺寸
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

		void LoadMapXml(const char* filepath);//将地图文件读取并按照图层顺序分层保存到mlayers里
		void UncompressPy(Layer* layer);//解压地图数据
		SDL_Texture* PreLayerTexBlit(SDL_Renderer* renderer, Layer* layer);
		friend class CollisionComponent;

	private:
		const char* MapName;
		SDL_Texture* MapTex;
		int MapTileW; // 用格计量的地图尺寸
		int MapTileH;
		int tileW;//地图里单个格的像素尺寸//由于地图的格大小和素材不一样，所以要单独保存
		int tileH;
		int MapW;//地图像素尺寸
		int MapH;
		PhysWorld* Pw;
	protected:
		void DrawLayer(SDL_Renderer* renderer, Layer* layer);
		std::vector<class GameObject*> mMapObjects;//存放地图上的游戏物体
		std::vector<Layer*> mLayers;
	};
}

#endif __MapObject__