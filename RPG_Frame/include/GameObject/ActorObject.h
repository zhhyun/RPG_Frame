#ifndef __ActorObject__
#define __ActorObject__

#include "GameObject.h"

namespace GameFrame {
	//class MapObject;
	class ActorObject : public GameObject {
	public:
		ActorObject(class Game* game, class MapObject* map, const std::string& name);
		~ActorObject();
		int GetHp();
		int AddHp(int hp);
		int GetACK();
		int AddACK(int ack);
		int GetDEF();
		int AddDEF(int def);

		int BattleStart(class ActorObject* b);

		bool GetBattleState();
		void SetBattleSate(bool state);

		friend class CollisionComponent;

	private:
		int		Hp;
		int		Speed;
		int		ACK;
		int		DEF;
		//int		

	protected:
		bool	IsCombating;
		MapObject*	 mMap;
	};

}

#endif	__ActorObject__



