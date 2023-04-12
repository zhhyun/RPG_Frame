#include	"PlayerObject.h"
#include	"MapObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"CollisionComponent.h"
#include	"Game.h"

GameFrame::PlayerObject::PlayerObject(Game* game, MapObject* map, const std::string& name) :
	ActorObject(game, map, name)
{
	
	Vector2 pos{200,200};
	SetPosition(pos);
	SpriteComponent* Sprite = new SpriteComponent(this, 100);
	std::string str = "Player";
	Sprite->LoadTexture(str);
	MoveComponent* Move = new MoveComponent(this);
	CollisionComponent* collision = new CollisionComponent(this);
	InputComponent* Input = new InputComponent(this);
	BattleComponent* Battle = new BattleComponent(this);
	AddHp(1000);
	AddACK(20);
	collision->SetCollision(pos, 64, 64);
}

GameFrame::PlayerObject::~PlayerObject()
{
}


void GameFrame::PlayerObject::update()
{
	BattleComponent* bc = GetComponent<BattleComponent>();

	//如果在战斗中，则只更新战斗和输入组件
	if (IsCombating) {
		bc->update();
		return;
	}
	else {
		for (auto iter : mComponents) {
			iter->update();
		}
	}
}
