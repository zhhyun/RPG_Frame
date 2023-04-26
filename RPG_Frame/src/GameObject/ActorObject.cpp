#include	"ActorObject.h"
#include	"MapObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"Game.h"


GameFrame::ActorObject::ActorObject(Game* game, MapObject* map, const std::string& name) :
	Hp(100),
	MaxHp(100),
	ACK(10),
	DEF(10),
	Speed(1),
	IsCombating(false),
	mMap(map),
	Height(20),
	Wdith(20),
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

int GameFrame::ActorObject::GetACK()
{
	return ACK;
}

void GameFrame::ActorObject::AddACK(int ack)
{
	ACK = ACK + ack;
}

int GameFrame::ActorObject::GetDEF()
{
	return DEF;
}

void GameFrame::ActorObject::AddDEF(int def)
{
	DEF = DEF + def;
}

int GameFrame::ActorObject::GetH()
{
	return Height;
}

void GameFrame::ActorObject::SetH(int h)
{
	Height = h;
}

int GameFrame::ActorObject::GetW()
{
	return Wdith;
}

void GameFrame::ActorObject::SetW(int w)
{
	Wdith = w;
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
