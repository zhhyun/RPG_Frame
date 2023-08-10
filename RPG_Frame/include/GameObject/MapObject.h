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
	//储存地图上的碰撞区间
	//碰撞区间目前支持矩形、圆形、线段
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
		//解析出tile在原图片的位置坐标
		Vector2 TileIdParser(int id, SDL_Texture* tex);
		//解析出tile要绘制到的位置坐标
		Vector2 MapIdParser(int it);
	private:
		const char* zlibcode;//unsigned char
		//图层用到的tile文件路径,应该在实例化时定义(目前未调整)
		const std::string tilePath = "sprite/tilesheet_0.png";
		std::vector<int> Lcode;
		const char* LayerName={"none"};
		//本图层导出后的纹理
		SDL_Texture* LayerTex;
		//用网格计量的宽度
		int mesh_LayerWidth = 0;
		//用网格计量的高度
		int mesh_LayerHeight = 0;

		//注意，这里是素材原本尺寸，实际运行生成地图时会根据需要放缩图层的大小，不要弄混
		//用像素计量的宽度
		int pixel_layerWidth = 0;
		//用像素计量的高度
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

		void LoadMapXml(const std::string& filepath);//将地图文件读取并按照图层顺序分层保存到mlayers里
		SDL_Texture* PreLayerTexBlit(SDL_Renderer* renderer, Layer* layer);
		void SetTileAttr();//设置格子的属性和事件
		friend class CollisionComponent;

	private:
		const char* MapName;
		std::string Map_id;
		SDL_Texture* MapTex;
		int MapTileW; // 用格计量的地图尺寸
		int MapTileH;
		int tileW;//地图里单个格的像素尺寸//由于地图的格大小和素材不一样，所以要单独保存
		int tileH;
		//地图像素宽
		int MapW;
		//地图像素高
		int MapH;

		//碰撞区域
		PhysWorld* CollisionsInMap;

		void UncompressTile_By_Py(Layer* layer);//解压地图数据
		//从json文件里读取地图的碰撞区域
		int LoadCollision(const std::string& path);

	protected:
		void DrawLayer(SDL_Renderer* renderer, Layer* layer);
		std::vector<class GameObject*> mObjectsInMap;//存放地图上的游戏物体
		std::vector<Layer*> mLayers;
	};
}

#endif __MapObject__