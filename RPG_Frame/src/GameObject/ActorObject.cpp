#include	"ActorObject.h"
#include	"MapObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"Dialogbox.h"
#include	"Game.h"
#include	"Math2.h"

GameFrame::ActorObject::ActorObject(Game* game, Sence* map, const std::string& name) :
	Hp(100),
	MaxHp(100),
	ACK(10),
	DEF(10),
	Speed(1),
	IsCombating(false),
	mSence(map),
	Lv(1),
	ActorName(name),
	mDialog(nullptr),
	mDir(Dir::DOWN),
	mScale(1),
	mRotation(0),
	GameObject(game,name)
{
	map->SetPlayer(this);
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

bool GameFrame::ActorObject::GetBattleState()
{
	return IsCombating;
}

void GameFrame::ActorObject::SetBattleSate(bool state)
{
	IsCombating = state;
}

bool GameFrame::ActorObject::CreateDialog(const std::string& scriptname)
{
	if (auto dialog = new Dialogbox(mGame, scriptname)) {
		/*从人物纹理中获取肖像dialog->Portrait;*/
		mDialog = dialog;
		return true;
	}
	else
		return false;
}

void GameFrame::ActorObject::CloseDialog()
{
	if (mDialog != nullptr) {
		mDialog->close();
	}
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