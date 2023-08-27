#ifndef __MapObject__
#define __MapObject__
#include	"GameObject.h"
#include	"ActorObject.h"
#include	"DEFINES.h"
#include	<unordered_map>
#include	<string>
#include	<json.hpp>
#include	<fstream>
#include	<filesystem>
#include	"CollisionComponent.h"

#define TIELPATH  "sprite/tilesheet_0.png"

namespace GameFrame {
	class MapObject;
	class GameEvent;

	typedef struct Property {
		std::string Name;
		int Value;
	}Property;


	typedef struct Tile {
		std::vector<Property> mProperties;
		int Tile_id;
	}Tile;

	typedef struct Object {
		std::vector<Property> mProperties;
		int x;
		int y;
		int width;
		int height;
	}Object;


	typedef struct  ObjectGroup {
		std::vector<Object> mObjects;
		std::string name;
		bool visible;
	}ObjectGroup;

	typedef struct AnimaTile {
		int tileCode;
		SDL_Rect tileSrc;
		SDL_Rect tileRect;
		int length;
		int currFrame = 0;
		float fps = 5.0;
		Uint32 AnimTicks = 0;
		SDL_Texture* tex;
	}AnimaTile;


	class Layer {
	public:
		Layer(const std::string& FilePath, class Sence* sence);
		Layer() {};
		~Layer(){};
		
		//解析出tile在原图片的位置坐标
		Vector2 TileIdParser(int id, SDL_Texture* tex);
		//解析出tile要绘制到的位置坐标
		Vector2 MapIdParser(int it);
		friend class Sence;
		friend class MapObject;

	private:
		bool visible = false;
		std::string LayerName = { "none" };
		std::string property = "null";
		//图层用到的tile文件路径,应该在实例化时定义(目前未调整)
		const std::string FilePath;

		int mesh_LayerWidth = 0;//用网格计量的宽度	
		int mesh_LayerHeight = 0;//用网格计量的高度

		//注意，这里是素材原本尺寸，实际运行生成地图时会根据需要放缩图层的大小，不要弄混
		int pixel_layerWidth = 0;//用像素计量的宽度
		int pixel_layerHeight = 0;//用像素计量的高度

		int layerTileW ;
		int layerTileH ;
		class Sence* mSence;
		int UpdateOrder = 0;

		std::vector<int> Lcode;
		std::vector<AnimaTile> AnimaTiles;
	};

	class Sence {
	public:
		Sence(MapObject* map, const std::string& fileName);
		~Sence();
		void update();
		void Draw(SDL_Renderer* renderer);
		void LoadSenceXml(const std::string& filepath);//将地图文件读取并按照图层顺序分层保存到mlayers里		
		Tile GetStandTileFromLayer(Vector2 standpos);//获得脚底所踩的图块
		bool GetStandTileFromObejctLayer(Vector2 standpos);//获得所在位置的物体层图块，用于判断图层渲染顺序
		Object* GetStandTileFromObject(Vector2 standpos);//从对象层获取脚踩的对象
		std::string GetSenceID() { return sence_id; };
		
		int GettileW() { return tileW; };
		int GettileH() { return tileH; };
		int GetMapW() { return MapW; };
		int GetMapH() { return MapH; };
		void SetPlayer(class ActorObject* player) { Player = player; };
		Vector2 MapVecTransToWinVec(Vector2 mapPos);
		std::vector<int> Lcode;
		std::vector<int> OLcode;
		std::vector<Tile> Tileset;//tile数组，存放的是所有tile的编号和属性
		std::vector<SDL_Texture*> layerTex;

		friend class Camera;
		friend class MapObject;
		friend class Layer;

	private:
		std::string SenceName;
		std::string sence_id;
		int SenceTileW; // 用格计量的地图尺寸
		int SenceTileH;

		//由于地图的格大小和素材不一样，所以这里的尺寸不从文件中读取而是自定义的
		int tileW = TILEW;//地图里单个格的像素尺寸
		int tileH = TILEH;
		int MapW;//地图像素宽
		int MapH;//地图像素高

		void CheckinRegion(GameObject* object);//检查游戏对象是否在特殊地块
		void Mergelayers_GeneraTex(SDL_Renderer* renderer);//合成地面图层，生成新的地图数组,并为所有图层生成纹理
		void UncompressTile_By_Py(Layer* layer, const char* zlicode);//解压地图数据

		void ClearLayersTex();
		void ClearObjGroups();
		
		MapObject* mMap;

	protected:
		void DrawLayer(SDL_Renderer* renderer, SDL_Texture* layerTex);
		void DrawAnimTile(SDL_Renderer* renderer);
		class ActorObject* Player;
		std::vector<Layer*> mLayers;
		std::vector<ObjectGroup> mObejctGroups;
	};












	class MapObject : public GameObject {
	public:
		MapObject(class Game* game,const std::string& folderPath, const std::string& map_id);
		~MapObject() {};

		void update() override;
		void Draw(SDL_Renderer* renderer) override;

		void ExchangeSence(std::string Srcsence_id, std::string Dstsence_id);
		void ExchangeSence(Sence* Srcsence, Sence* Dstsence);
		Tile GetStandTileFromLayer(Vector2 standpos);

		void AddSence(Sence* sence);
		Sence* GetCurrSence() { return CurrSence; };
		Sence* GetSenceFromName(std::string senceName);
		void LoadSence(const std::string& folderPath);
		void EnterSence(Sence* targetSence);
		void EnterSence(Sence* targetSence,int destid);
		void LeaveCurrSence();
		
		

	private:
		std::vector<Sence*> mSences;
		Sence*	CurrSence;
		std::string Map_id;
	};
}

#endif __MapObject__