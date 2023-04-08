#ifndef __NpcObject__
#define __NpcObject__
#include "GameObject.h"
namespace GameFrame {
	class NpcObject : public GameObject {
	public:
		NpcObject(Game* game);
		~NpcObject();
		int GetHp();
		int AddHp(int hp);
		int GetACK();
		int AddACK(int ack);
		int GetDEF();
		int AddDEF(int def);
		bool GetBattleState();
		void SetBattleSate(bool state);

	private:
		int		Hp;
		int		Speed;
		int		ACK;
		int		DEF;
	};
}
#endif __NpcObject__