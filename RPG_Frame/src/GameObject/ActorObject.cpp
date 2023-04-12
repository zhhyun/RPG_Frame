#include	"ActorObject.h"
#include	"MapObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"Game.h"


GameFrame::ActorObject::ActorObject(Game* game, MapObject* map, const std::string& name) :
	Hp(100),
	ACK(10),
	DEF(10),
	Speed(1),
	IsCombating(false),
	mMap(map),
	GameObject(game,name)
{
	map->AddMapObject(this);
}

GameFrame::ActorObject::~ActorObject()
{
}

int GameFrame::ActorObject::GetHp()
{
	return Hp;
}

int GameFrame::ActorObject::AddHp(int hp)
{
	Hp = Hp + hp;
	return Hp;
}

int GameFrame::ActorObject::GetACK()
{
	return ACK;
}

int GameFrame::ActorObject::AddACK(int ack)
{
	ACK = ACK + ack;
	return ACK;
}

int GameFrame::ActorObject::GetDEF()
{
	return DEF;
}

int GameFrame::ActorObject::AddDEF(int def)
{
	DEF = DEF + def;
	return DEF;
}

bool GameFrame::ActorObject::GetBattleState()
{
	return IsCombating;
}

void GameFrame::ActorObject::SetBattleSate(bool state)
{
	IsCombating = state;
}

int GameFrame::ActorObject::BattleStart(class ActorObject* b)
{

	if (IsCombating == true) {
		return 0;
	}
	else {
		IsCombating = false;
		BattleComponent* bc = GetComponent<BattleComponent>();
		bc->BattleInint(b);
		return 1;
	}

}
