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
using namespace GameFrame;

namespace GameFrame {
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

		typedef struct EquPropertity {
			int deltaACK;
			int deltaDEF;
			int deltaHealth;
			int deltaMp;
			//...
		}EquPropertity;

	public:
		Equipments(const std::string& id, const std::string name, Game* game);
		
		void SetEquipTexArea(SDL_Rect area) { TakeOutPosFromTex = area; };
		void SetEquipTex(SDL_Texture* tex) { EquTileset = tex; };
		void SetLevel(unsigned int lv) { level = lv; };
		void LevelUp() { level++; };
		void SetLimited(int limit) { limited = limit; };
		void SetPropertity(EquPropertity propertity) { Propertity = propertity; };
		void SetClass(EquipCLASS mClass) { Class = mClass; };

	private:
		bool enable;
		unsigned int level;
		int limited;
		const std::string id;
		const std::string name;
		EquPropertity propertity;
		SDL_Rect TakeOutPosFromTex;

		int GetLimit() { return limited; };

		


	protected:
		bool enable = true;
		unsigned int level;
		int limited = -1;	//-1Ϊ������
		const std::string ID;
		const std::string Name;
		SDL_Texture* EquTileset;
		EquPropertity Propertity;
		SDL_Rect TakeOutPosFromTex;
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

	private:

	};

	

	class Shield : public Equipments {

	};
}


#endif __Equipments__  