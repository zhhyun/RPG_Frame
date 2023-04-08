#ifndef __BattleComponent__
#define __BattleComponent__
#include "Component.h"

namespace GameFrame {
	class GameObject;
	class PlayerObject;
	class NpcObject;
	class BattleComponent : public Component {
	public:
		BattleComponent(GameObject* gameobject);
		~BattleComponent();
		void ProcessInput(const uint8_t* keystate) override;

		void combat(PlayerObject* a, NpcObject* b);
		void PlayerDecision();
		void NpcDecision();
		int BattleInint(NpcObject* b);
		void BattleFin(NpcObject* b);

		void SetWaiting(bool set);
		bool GetWaiting();

		void SetChoose(int choose);
		int GetChoose();
	private:
		bool	IsWaiting;
		int		Choose;
		PlayerObject* mGameObject;
	};
}

#endif __BattleComponent__

