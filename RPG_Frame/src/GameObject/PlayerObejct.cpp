#include	"PlayerObject.h"
#include	"MapObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"CollisionComponent.h"
#include	"AnimSpriteComponent.h"
#include	"Texture.h"
#include	"Game.h"
#include	"Math2.h"

GameFrame::PlayerObject::PlayerObject(Game* game, Sence* map, const std::string& name) :
	mAnimComponent(nullptr),
	ActorObject(game, map, name)
{
	Vector2 pos{240,274};
	Vector2 down{ 0,0 };
	Vector2 idleup{ 64,192 };
	Vector2 idledown{ 64,0 };
	Vector2 idleleft{ 64,64 };
	Vector2 idleright{ 64,128 };
	Vector2 left{ 0,64 };
	Vector2 right{ 0,128 };
	Vector2 up{ 0,192 };
	SetPosition(pos);
	mAnimComponent = new AnimSpriteComponent(this, 99);
	std::string str = "Player";
	auto ttex = mGame->GetTexture(str);
	MoveComponent* Move = new MoveComponent(this);
	CollisionComponent* collision = new CollisionComponent(this);
	InputComponent* Input = new InputComponent(this);
	Input->SetRequestCom(Move);
	BattleComponent* Battle = new BattleComponent(this);
	auto tex = new Texture("Alfonse");
	tex->CreateFromTexture(mGame->GetTexture("Alfonse"));
	Battle->SetBattleTexture(tex);
	
	//���ý�ɫ����
	Anim* UpForward = new Anim(ttex, 3, true, up, 10.0, PlayerW, PlayerH);
	Anim* DownForward = new Anim(ttex, 3, true, down, 15.0, PlayerW, PlayerH);
	Anim* LeftForward = new Anim(ttex, 3, true, left, 15.0, PlayerW, PlayerH);
	Anim* RightForward = new Anim(ttex, 3, true, right, 15.0, PlayerW, PlayerH);
	Anim* UpIdle = new Anim(ttex, 1, true, idleup, -1, PlayerW, PlayerH);
	Anim* DownIdle = new Anim(ttex, 1, true, idledown, -1, PlayerW, PlayerH);
	Anim* LeftIdle = new Anim(ttex, 1, true, idleleft, -1, PlayerW, PlayerH);
	Anim* RightIdle = new Anim(ttex, 1, true, idleright, -1, PlayerW, PlayerH);

	mAnimComponent->AddAnimation(UpForward, "UpForward");
	mAnimComponent->AddAnimation(DownForward, "DownForward");
	mAnimComponent->AddAnimation(LeftForward, "LeftForward");
	mAnimComponent->AddAnimation(RightForward,"RightForward");
	mAnimComponent->AddAnimation(UpIdle, "UpIdle");
	mAnimComponent->AddAnimation(DownIdle, "DownIdle");
	mAnimComponent->AddAnimation(LeftIdle, "LeftIdle");
	mAnimComponent->AddAnimation(RightIdle, "RightIdle");

	mAnimComponent->PlayAnimation("DownIdle");
	SetMaxHp(100);
	SetHp(60);
	AddACK(20);
	SetH(PlayerH); SetW(PlayerW);
	/*auto shape = new RectShape(collision, pos.x, pos.y, PlayerH, PlayerW);*/
	SDL_Rect collArea = { 15,32,64-2*15,32 };
	collision->SetCollisionArea(collArea);

	//Ϊ��ײ����ṩ��ײ������Ļص�������������ײ�����ݼ������ض��¼�
	//collision->DefinecallbackOnCollision([this]() {
	//	SDL_Log("collidion event has sub");
	//	GameEvent* event = new GameEvent("000004");
	//	mGame->GetEventThread()->GetManager()->RegisterEvent(event);
	//	});
	////�趨�ƶ�����ض��Ķ��ģ��ص����¼�
	//Move->SubscribeToEvent("000004", [this,Move]() {
	//	SDL_Log("sub collidion sucess");
	//	SetPosition(ObjectPosion - Move->GetSpeed() * Move->GetMovdir());
	//	});
}

GameFrame::PlayerObject::~PlayerObject()
{
}


void GameFrame::PlayerObject::update()
{
	BattleComponent* bc = GetComponent<BattleComponent>();

	//�����ս���У���ֻ����ս�����������
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

void GameFrame::PlayerObject::Draw(SDL_Renderer* renderer)
{
	mAnimComponent->Draw(renderer);
}

void GameFrame::PlayerObject::ProcessInput(InputSystem* keystate)
{
	GetComponent<InputComponent>()->ProcessInput(keystate);
}
