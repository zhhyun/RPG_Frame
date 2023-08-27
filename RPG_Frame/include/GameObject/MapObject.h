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
		
		//������tile��ԭͼƬ��λ������
		Vector2 TileIdParser(int id, SDL_Texture* tex);
		//������tileҪ���Ƶ���λ������
		Vector2 MapIdParser(int it);
		friend class Sence;
		friend class MapObject;

	private:
		bool visible = false;
		std::string LayerName = { "none" };
		std::string property = "null";
		//ͼ���õ���tile�ļ�·��,Ӧ����ʵ����ʱ����(Ŀǰδ����)
		const std::string FilePath;

		int mesh_LayerWidth = 0;//����������Ŀ��	
		int mesh_LayerHeight = 0;//����������ĸ߶�

		//ע�⣬�������ز�ԭ���ߴ磬ʵ���������ɵ�ͼʱ�������Ҫ����ͼ��Ĵ�С����ҪŪ��
		int pixel_layerWidth = 0;//�����ؼ����Ŀ��
		int pixel_layerHeight = 0;//�����ؼ����ĸ߶�

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
		void LoadSenceXml(const std::string& filepath);//����ͼ�ļ���ȡ������ͼ��˳��ֲ㱣�浽mlayers��		
		Tile GetStandTileFromLayer(Vector2 standpos);//��ýŵ����ȵ�ͼ��
		bool GetStandTileFromObejctLayer(Vector2 standpos);//�������λ�õ������ͼ�飬�����ж�ͼ����Ⱦ˳��
		Object* GetStandTileFromObject(Vector2 standpos);//�Ӷ�����ȡ�ŲȵĶ���
		std::string GetSenceID() { return sence_id; };
		
		int GettileW() { return tileW; };
		int GettileH() { return tileH; };
		int GetMapW() { return MapW; };
		int GetMapH() { return MapH; };
		void SetPlayer(class ActorObject* player) { Player = player; };
		Vector2 MapVecTransToWinVec(Vector2 mapPos);
		std::vector<int> Lcode;
		std::vector<int> OLcode;
		std::vector<Tile> Tileset;//tile���飬��ŵ�������tile�ı�ź�����
		std::vector<SDL_Texture*> layerTex;

		friend class Camera;
		friend class MapObject;
		friend class Layer;

	private:
		std::string SenceName;
		std::string sence_id;
		int SenceTileW; // �ø�����ĵ�ͼ�ߴ�
		int SenceTileH;

		//���ڵ�ͼ�ĸ��С���زĲ�һ������������ĳߴ粻���ļ��ж�ȡ�����Զ����
		int tileW = TILEW;//��ͼ�ﵥ��������سߴ�
		int tileH = TILEH;
		int MapW;//��ͼ���ؿ�
		int MapH;//��ͼ���ظ�

		void CheckinRegion(GameObject* object);//�����Ϸ�����Ƿ�������ؿ�
		void Mergelayers_GeneraTex(SDL_Renderer* renderer);//�ϳɵ���ͼ�㣬�����µĵ�ͼ����,��Ϊ����ͼ����������
		void UncompressTile_By_Py(Layer* layer, const char* zlicode);//��ѹ��ͼ����

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