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


	private:
		bool enable;
		unsigned int level;
		int limited;
		const std::string id;
		const std::string name;
		Texture EquTileset;
		EquPropertity propertity;
		SDL_Rect TakeOutPosFromTex;
		//suit
	};

	class Weapon : public Equipments {
	public:

	private:

	};

	class Armor : public Equipments {
	public:
	private:

	};

	class Sword : public Weapon {

	};

}


#endif //  

