#ifndef __Equipments__
#define __Equipments__
#include	"GameObject.h"
/**********************************************************************/
/*																	  */
/*				idע�������ΪϵͳĬ�Ϸ���ź��ⲿ�ţ�					  */
/*				�ⲿ�����ڵ�����������Ӷ���ʹ�á�						  */
/*				�ⲿ���������Ա��+ϵͳ�����ɣ�						  */
/*				ϵͳ���Ψһ����Ա���ڵ����������ļ�������Ψһ			  */
/*																	  */
/**********************************************************************/
namespace GameFrame {
	class Game;

	enum class EquipCLASS {
		UNKONWN,
		WEAPON,
		ARMOR,
		SWORD,
		SHIELD
		//........
	};

	typedef struct EquipPropertity {
		int deltaACK;
		int deltaDEF;
		int deltaHealth;
		int deltaMp;
		//...
	}EquPropertity;

	class Equipments : public GameObject {
		enum class EquCLASS {
			ARMOR,
			SWORD,
			SHIELD
			//........
		};

	public:
		Equipments(const std::string& id, const std::string name, Game* game);

		void SetEquipTexArea(SDL_Rect area) { TakeOutPosFromTex = area; };
		void SetEquipTex(SDL_Texture* tex) { EquTileset = tex; };
		void SetLevel(unsigned int lv) { level = lv; };
		void LevelUp() { level++; };
		void SetLimited(int limit) { limited = limit; };
		void SetPropertity(EquPropertity propertity) { Propertity = propertity; };
		void SetClass(EquipCLASS mClass) { Class = mClass; };
		int GetLimit() { return limited; };
		EquipCLASS GetClass() { return Class; };
		EquPropertity GetPropty() { return Propertity; };
		SDL_Texture* GetEquipTex() { return EquTileset; };
		SDL_Rect GetRectFromTex() { return TakeOutPosFromTex; };

	protected:
		bool enable = true;
		unsigned int level;
		int limited = -1;	//-1Ϊ������
		const std::string Name;
		SDL_Texture* EquTileset;
		EquPropertity Propertity = { 0,0,0,0 };
		SDL_Rect TakeOutPosFromTex = { 0,0,0,0 };
		EquipCLASS Class = EquipCLASS::UNKONWN;
	};

	class Weapon : public Equipments {
	public:
		Weapon(const std::string& id, const std::string name, Game* game);

	private:

	};

	class Sword : public Weapon {
	public:
		Sword(const std::string& id, const std::string name, Game* game);

	private:

	};


	class Armor : public Equipments {
	public:
		Armor(const std::string& id, const std::string name, Game* game);
	private:

	};

	

	class Shield : public Equipments {
	public:
		Shield(const std::string& id, const std::string name, Game* game);
	};
}


#endif __Equipments__  