#ifndef __BattleSystem__
#define __BattleSystem__
#include	"Game.h"
#include	"ActorObject.h"
#include	"Texture.h"
#include	<vector>

namespace GameFrame {
	class Texture;
	class PlayerObject;
	class BattleSystem {
	public:
		BattleSystem(Texture* Sence, Game* game, PlayerObject* player);
		~BattleSystem(){};
		void Draw(SDL_Renderer* renderer);

		std::vector<ActorObject*> Allies;
		std::vector<ActorObject*> Enemies;

	private:
		Texture* mSence;//Õ½¶·³¡¾°
		Game* mGame;
		PlayerObject* mPlayer;
	};
}

#endif __BattleSystem__