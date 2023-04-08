#ifndef __PlayerObject__
#define __PlayerObject__
#include "GameObject.h"

namespace GameFrame {
	class PlayerObject : public GameObject {
	public:
		PlayerObject(Game* game);
		~PlayerObject();
		
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
		bool	IsCombating;
	};
}
#endif __PlayerObject__