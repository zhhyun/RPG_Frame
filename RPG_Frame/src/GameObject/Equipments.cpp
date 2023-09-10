#include	"Equipments.h"
#include	"Game.h"

GameFrame::Equipments::Equipments(const std::string& id, const std::string name, Game* game):
	Name(name),
	level(1),
	GameObject(game, name,id)
{
}


GameFrame::Weapon::Weapon(const std::string& id, const std::string name, Game* game):	
	Equipments(id, name, game)
{
	Class = EquipCLASS::WEAPON;
}

GameFrame::Sword::Sword(const std::string& id, const std::string name, Game* game):
	Weapon(id, name, game)
{
	Class = EquipCLASS::SWORD;
}

GameFrame::Armor::Armor(const std::string& id, const std::string name, Game* game):
	Equipments(id, name, game)
{
	Class = EquipCLASS::ARMOR;
}

GameFrame::Shield::Shield(const std::string& id, const std::string name, Game* game):
	Equipments(id, name, game)
{
	Class = EquipCLASS::SHIELD;
}
