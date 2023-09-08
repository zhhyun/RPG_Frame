#include	"Equipments.h"
#include	"Game.h"

GameFrame::Equipments::Equipments(const std::string& id, const std::string name, Game* game):
	ID(id),
	Name(name),
	GameObject(game)
{
	TakeOutPosFromTex = { 0,0,0,0 };
	Propertity = { 0,0,0,0 };
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
