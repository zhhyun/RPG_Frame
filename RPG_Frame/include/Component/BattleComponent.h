#ifndef __BattleComponent__
#define __BattleComponent__
#include "Component.h"
#include "Texture.h"
//ս�������������������ٸ���ս����ֻ���𴢴漼�ܻ�״̬���ݣ��Լ������ж���ս�������ƽ���ս��ϵͳ
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

		void SetBattleTexture(Texture* tex) { ActorInBattle = tex; };
		Texture* GetBattleTexture() { return ActorInBattle; };
		void Attack();
		void Skills();
		void Escape();

		void update() override;

		friend class BattleSystem;
	private:
		bool	IsWaiting;	//�����Ƿ����Լ��Ļغ�
		int		InputBuf;	//������뻺����
		ActorObject*	Enemies;//����
		ActorObject*	Player;
		Texture*		ActorInBattle;
	};
}

#endif __BattleComponent__

