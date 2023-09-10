#include "BackpackComponent.h"
#include "Equipments.h"
#include "GameObject.h"
GameFrame::BackpackComponent::BackpackComponent(GameObject* gameobject):
	SpriteComponent(gameobject, 1)
{
}
void GameFrame::BackpackComponent::ProcessInput(const uint8_t* keystate)
{
}

void GameFrame::BackpackComponent::update()
{
}

void GameFrame::BackpackComponent::AddEquipment(Equipments* equip)
{
	auto id = equip->GetID();
	if (equipNum(id) == equip->GetLimit()) {
		return;
	}
	if (equip->GetClass() == EquipCLASS::SWORD) {
		AddWeapon(dynamic_cast<Weapon*>(equip));
		AddSword(dynamic_cast<Sword*>(equip));
	}
	else if (equip->GetClass() == EquipCLASS::WEAPON) {
		AddWeapon(dynamic_cast<Weapon*>(equip));
	}
	else if (equip->GetClass() == EquipCLASS::ARMOR) {
		AddArmor(dynamic_cast<Armor*>(equip));
	}
	mObjectsInBackpack.emplace_back(equip);
	mEquipsInBackpack.emplace_back(equip);
}

int GameFrame::BackpackComponent::equipNum(const std::string& id)
{
	int num = 0;
	for (auto iter : mObjectsInBackpack) {
		if (iter->GetID() == id) {
			num++;
		}
	}
	return num;
}

void GameFrame::BackpackComponent::AddWeapon(Weapon* weapon)
{
	mWeaponsInBackPack.emplace_back(weapon);
}

void GameFrame::BackpackComponent::AddArmor(Armor* armor)
{
}

void GameFrame::BackpackComponent::AddSheild(Shield* sheild)
{
}

void GameFrame::BackpackComponent::AddSword(Sword* sword)
{
}
