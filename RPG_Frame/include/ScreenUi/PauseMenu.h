#ifndef __PauseMenu__
#define __PauseMenu__
#include	"ScreenUi.h"
#include	"Math2.h"
#include	<SDL.h>
#include	<string>
#include	<vector>
#include	"Texture.h"
#include	<algorithm>

namespace GameFrame {
	class PauseMenu : public ScreenUi {
	public:
		PauseMenu(class Game* game, const std::string& NameInGame);
		~PauseMenu();
		void Draw(SDL_Renderer* renderer) override;
		void HandKeyPress(int key)override;
		void AddButton(const std::string& name, Vector2 pos, Texture* tex, std::function<void()> OnClick) override;

	private:
	};
}

#endif __PauseMenu__