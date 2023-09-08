#ifndef __Equipments__
#define __Equipments__
#include	"GameObject.h"
/**********************************************************************/
/*																	  */
/*				id注册号区分为系统默认分配号和外部号，					  */
/*				外部号用于第三方作者添加对象使用。						  */
/*				外部号组成由相对编号+系统编号组成，						  */
/*				系统编号唯一，相对编号在第三方对象文件索引中唯一			  */
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
		int limited = -1;	//-1为无限制
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