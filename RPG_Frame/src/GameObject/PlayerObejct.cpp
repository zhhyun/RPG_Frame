#include	"PlayerObject.h"
#include	"MapObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"CollisionComponent.h"
#include	"AnimSpriteComponent.h"
#include	"Game.h"

GameFrame::PlayerObject::PlayerObject(Game* game, MapObject* map, const std::string& name) :
	ActorObject(game, map, name)
{
	Vector2 pos{210,274};
	Vector2 down{ 0,0 };
	Vector2 idleup{ 64,192 };
	Vector2 idledown{ 64,0 };
	Vector2 idleleft{ 64,64 };
	Vector2 idleright{ 64,128 };
	Vector2 left{ 0,64 };
	Vector2 right{ 0,128 };
	Vector2 up{ 0,192 };
	SetPosition(pos);
	//SpriteComponent* Sprite = new SpriteComponent(this, 100);
	AnimSpriteComponent* Animation = new AnimSpriteComponent(this, 99);
	std::string str = "Player";
	Animation->LoadTexture(str);
	MoveComponent* Move = new MoveComponent(this);
	CollisionComponent* collision = new CollisionComponent(this);
	InputComponent* Input = new InputComponent(this);
	Input->SetRequestCom(Move);
	BattleComponent* Battle = new BattleComponent(this);
	
	//设置角色动画
	Anim* UpForward = new Anim(Animation->GetTexture(str), 3, true, up, 10.0, PlayerW, PlayerH);
	Anim* DownForward = new Anim(Animation->GetTexture(str), 3, true, down, 15.0, PlayerW, PlayerH);
	Anim* LeftForward = new Anim(Animation->GetTexture(str), 3, true, left, 15.0, PlayerW, PlayerH);
	Anim* RightForward = new Anim(Animation->GetTexture(str), 3, true, right, 15.0, PlayerW, PlayerH);
	Anim* UpIdle = new Anim(Animation->GetTexture(str), 1, true, idleup, -1, PlayerW, PlayerH);
	Anim* DownIdle = new Anim(Animation->GetTexture(str), 1, true, idledown, -1, PlayerW, PlayerH);
	Anim* LeftIdle = new Anim(Animation->GetTexture(str), 1, true, idleleft, -1, PlayerW, PlayerH);
	Anim* RightIdle = new Anim(Animation->GetTexture(str), 1, true, idleright, -1, PlayerW, PlayerH);

	Animation->AddAnimation(UpForward, "UpForward");
	Animation->AddAnimation(DownForward, "DownForward");
	Animation->AddAnimation(LeftForward, "LeftForward");
	Animation->AddAnimation(RightForward,"RightForward");
	Animation->AddAnimation(UpIdle, "UpIdle");
	Animation->AddAnimation(DownIdle, "DownIdle");
	Animation->AddAnimation(LeftIdle, "LeftIdle");
	Animation->AddAnimation(RightIdle, "RightIdle");

	Animation->PlayAnimation("DownIdle");
	SetMaxHp(100);
	SetHp(60);
	AddACK(20);
	SetH(PlayerH); SetW(PlayerW);
	collision->SetCollision(pos, GetH(), GetW());
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

void GameFrame::PlayerObject::ProcessInput(InputSystem* keystate)
{
	GetComponent<InputComponent>()->ProcessInput(keystate);
}
 