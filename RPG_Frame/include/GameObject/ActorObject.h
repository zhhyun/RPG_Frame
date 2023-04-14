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
		void AddHp(int hp);
		int GetACK();
		void AddACK(int ack);
		int GetDEF();
		void AddDEF(int def);
		int GetH();
		void SetH(int h);
		int GetW();
		void SetW(int w);

		int BattleStart(class ActorObject* b);

		bool GetBattleState();
		void SetBattleSate(bool state);

		friend class CollisionComponent;

	private:
		int		Hp;
		int		Speed;
		int		ACK;
		int		DEF;
		int		Height;
		int		Wdith;

	protected:
		bool	IsCombating;
		MapObject*	 mMap;
	};

}

#endif	__ActorObject__



