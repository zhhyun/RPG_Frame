#include	"PlayerObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"Game.h"

GameFrame::PlayerObject::PlayerObject(Game* game) :
	Hp(100),
	ACK(10),
	DEF(10),
	Speed(1),
	IsCombating(false),
	GameObject(game)
{
	Vector2 pos{110,110};
	SetPosition(pos);
	SpriteComponent* Sprite = new SpriteComponent(this, 100);
	AddSpriteComponent(Sprite);
	SDL_Texture* tex = GetGame()->GetTexture("Player");
	Sprite->SetTexture(tex);
	MoveComponent* Move = new MoveComponent(this);
	//BackpackComponent* BackPack = new BackpackComponent(this, 99);
	InputComponent* Input = new InputComponent(this);
}

GameFrame::PlayerObject::~PlayerObject()
{
}

int GameFrame::PlayerObject::GetHp()
{
	return Hp;
}

int GameFrame::PlayerObject::AddHp(int hp)
{
	Hp = Hp + hp;
	return Hp;
}

int GameFrame::PlayerObject::GetACK()
{
	return ACK;
}

int GameFrame::PlayerObject::AddACK(int ack)
{
	ACK = ACK + ack;
	return ACK;
}

int GameFrame::PlayerObject::GetDEF()
{
	return DEF;
}

int GameFrame::PlayerObject::AddDEF(int def)
{
	DEF = DEF + def;
	return DEF;
}

bool GameFrame::PlayerObject::GetBattleState()
{
	return IsCombating;
}

void GameFrame::PlayerObject::SetBattleSate(bool state)
{
	IsCombating = state;
}
