#ifndef __ActorObject__
#define __ActorObject__
#include	"GameObject.h"
#include	"Math2.h"
#include	"BackpackComponent.h"
#include "Equipments.h"

namespace GameFrame {
	class Dialogbox;
	class Weapon;
	class Shield;
	class Armor;

	class ActorObject : public GameObject {
		typedef struct readyEquip {
			Weapon* slot1;
			Shield* slot2;
			Armor* slot3;
		}readyEquip;

	public:
		ActorObject(class Game* game, class Sence* map, const std::string& name, const std::string& id);
		~ActorObject();
		enum Dir
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		int GetHp();
		void SetMaxHp(int hp) { MaxHp = hp; };
		int GetMaxHp() { return MaxHp; };
		void SetHp(int hp) { Hp = hp; };
		int GetACK();
		void AddACK(int ack);
		int GetDEF();
		void AddDEF(int def);
		int GetLv() { return Lv; };
		void SetLv(int lv) { Lv = lv; };

		int BattleStart(class ActorObject* b);
		bool GetBattleState();
		void SetBattleSate(bool state);
		std::string GetActorName() { return ActorName; };

		float GetRotation() const { return mRotation; };
		void SetRotation(float rotation) { mRotation = rotation; };
		int	GetScale() const { return mScale; };
		void SetScale(int scale){ mScale = scale; };
		Dir GetDir() const{ return mDir; };
		void SetDir(Dir mdir){ mDir = mdir; };
		Sence* GetMapObject() {	return mSence; };
		void ChangeMap(Sence* sence) { mSence = sence; };
		bool CreateDialog(const std::string& scriptname);
		void CloseDialog();
		Dialogbox* GetmDialog() { return mDialog; };
		readyEquip GetreadyEquip() { return mReadyEquip; };
		void Additem(GameObject* item) {
			//mBackpack->AddEquipment(item);
		}
		void Additem(Equipments* equip) {
			SDL_Log("add item");
			mBackpack->AddEquipment(equip);
		}

		//id区分了物品种类，但是没有编号实例，需要重新设计一个实例编号
		void EquipEquipment(const std::string& equipid);

		friend class CollisionComponent;
		friend class Script;

	private:
		int		Hp;
		int		MaxHp;
		int		Speed;
		int		ACK;
		int		DEF;
		int		Lv;
		std::string ActorName;


		int BasicACK;
		int BasicDEF;
		int BasicLv;
		int BasicHp;


	protected:
		Dir									mDir;
		int									mScale;
		float								mRotation;
		Dialogbox*							mDialog;
		bool								IsCombating;
		Sence*								mSence;			//人物挂载的地图
		BackpackComponent*					mBackpack;		//背包
		readyEquip							mReadyEquip;	//人物身上的装备

		void UpdateEquipGain();
	};
}

#endif	__ActorObject__



