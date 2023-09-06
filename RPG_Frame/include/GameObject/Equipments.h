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

