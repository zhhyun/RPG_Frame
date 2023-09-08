#ifndef __ActorObject__
#define __ActorObject__
#include	"GameObject.h"
#include	"Math2.h"
#include	"BackpackComponent.h"

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
		ActorObject(class Game* game, class Sence* map, const std::string& name);
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

	protected:
		Dir									mDir;
		int									mScale;
		float								mRotation;
		Dialogbox*							mDialog;
		bool								IsCombating;
		Sence*								mSence;			//人物挂载的地图
		BackpackComponent*					mBackpack;		//背包
		readyEquip							mReadyEquip;	//人物身上的装备
	};
}

#endif	__ActorObject__



