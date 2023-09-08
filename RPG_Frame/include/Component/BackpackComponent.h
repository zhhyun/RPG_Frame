#ifndef __BackpackComponent__
#define __BackpackComponent__
#include	"SpriteComponent.h"
#include	<vector>
//#include "Equipments.h"

namespace GameFrame {
	class GameObject;
	class Weapon;
	class Equipments;
	class Sword;
	class Armor;
	class Shield;

	class BackpackComponent : public SpriteComponent {
	public:
		BackpackComponent();
		~BackpackComponent();
		void ProcessInput(const uint8_t* keystate); //override;
		void update(); //override;
		void AddEquipment(Equipments* equip);
		int equipNum(const std::string& id);
		friend class MainMenu;

	private:
		void AddWeapon(Weapon* weapon);
		void AddArmor(Armor* armor);
		void AddSheild(Shield* sheild);
		void AddSword(Sword* sword);
		std::vector<GameObject*> mObjectsInBackpack;
		std::vector<Weapon*> mWeaponsInBackPack;
	};
}
#endif // __BackpackComponent__
