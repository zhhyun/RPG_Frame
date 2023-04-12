#include	"NpcObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"CollisionComponent.h"
#include	"Game.h"

GameFrame::NpcObject::NpcObject(Game* game, MapObject* map, const std::string& name):
	ActorObject(game, map, name)
{
	Vector2 pos{ 210,210 };
	SetPosition(pos);
	SpriteComponent* Npc = new SpriteComponent(this, 100);
	BattleComponent* Battle = new BattleComponent(this);
	CollisionComponent* collision = new CollisionComponent(this);
	collision->SetCollision(pos, 64, 32);
	std::string str = "Npc";
	Npc->LoadTexture(str);
}

GameFrame::NpcObject::~NpcObject()
{
}
