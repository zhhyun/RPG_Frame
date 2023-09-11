#include	"ActorObject.h"
#include	"MapObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"Dialogbox.h"
#include	"Game.h"
#include	"Math2.h"

GameFrame::ActorObject::ActorObject(Game* game, Sence* map, const std::string& name, const std::string& id) :
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
	GameObject(game,name,id)
{
	BasicACK = ACK;
	BasicDEF = DEF;
	BasicHp = MaxHp;
	BasicLv = Lv;
	mReadyEquip.slot1 = nullptr;// new Weapon("slot1", "slot1", mGame);
	mReadyEquip.slot2 = nullptr; //new Shield("slot2", "slot2", mGame);
	mReadyEquip.slot3 = nullptr; //new Armor("slot3", "slot3", mGame);
	map->SetPlayer(this);
	mBackpack = new BackpackComponent(this);
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

void GameFrame::ActorObject::EquipEquipment(const std::string& equipid)
{
	for (auto equip : mBackpack->mEquipsInBackpack) {
		if (equip->GetID() == equipid) {
			if (equip->GetClass() == EquipCLASS::WEAPON || equip->GetClass() == EquipCLASS::SWORD) {
				mReadyEquip.slot1 = dynamic_cast<Weapon*>(equip);
			}
			else if (equip->GetClass() == EquipCLASS::SHIELD) {
				mReadyEquip.slot2 = dynamic_cast<Shield*>(equip);
			}
			else if (equip->GetClass() == EquipCLASS::ARMOR) {
				mReadyEquip.slot3 = dynamic_cast<Armor*>(equip);
			}
		}
	}
}

void GameFrame::ActorObject::UpdateEquipGain()
{
	if (mReadyEquip.slot1) {
		ACK = BasicACK + mReadyEquip.slot1->GetPropty().deltaACK; /*+
			mReadyEquip.slot2->GetPropty().deltaACK +
			mReadyEquip.slot3->GetPropty().deltaACK);*/

		DEF = BasicDEF + mReadyEquip.slot1->GetPropty().deltaDEF; /* +
			mReadyEquip.slot2->GetPropty().deltaDEF +
			mReadyEquip.slot3->GetPropty().deltaDEF);*/
	}
	

	//....
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