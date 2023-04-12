#ifndef __BattleComponent__
#define __BattleComponent__
#include "Component.h"

namespace GameFrame {
	class GameObject;
	class ActorObject;
	class NpcObject;
	class BattleComponent : public Component {
	public:
		BattleComponent(ActorObject* gameobject);
		~BattleComponent();
		void ProcessInput(const SDL_Keycode key);
		void ProcessInput2(const uint8_t* keystate);

		void combat(ActorObject* a, ActorObject* b);
		void PlayerDecision();
		void NpcDecision();
		int BattleInint(ActorObject* b);
		void BattleFin(ActorObject* b);

		void SetWaiting(bool set);
		bool GetWaiting();

		void ResetBuf();
		void SetBuf(int input);
		int GetBuf();
		void SetEnemy(ActorObject* b);
		bool IsActive();

		void Attack();
		void Skills();
		void Escape();

		void update() override;
	private:
		bool	IsWaiting;	//现在是否是自己的回合
		int		InputBuf;	//玩家输入缓存区
		ActorObject*	Enemies;//敌人
		ActorObject*	Player;
	};
}

#endif __BattleComponent__

