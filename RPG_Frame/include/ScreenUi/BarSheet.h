#ifndef __BarSheet__
#define __BarSheet__
#include	"ScreenUi.h"

namespace GameFrame {
	class PlayerObject;
	class BarSheet : public ScreenUi {
	public:
		BarSheet(class Game* game, const std::string& fileName,PlayerObject* player);
		~BarSheet();
		void Draw(SDL_Renderer* renderer) override;
	private:
		PlayerObject*	Player;
	};
}

#endif __BarSheet__