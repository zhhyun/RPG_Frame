#ifndef __MainMenu__
#define __MainMenu__
#include	"ScreenUi.h"
#include	"Button.h"
#include	"Game.h"
#include	"DEFINES.h"
#include	"Fonts.h"

namespace GameFrame {
	class MainMenu : public ScreenUi {
	public:
		MainMenu(class Game* game);
		~MainMenu(){};

		void Draw(SDL_Renderer* renderer)override;
		
	private:
		void DrawHeroData(SDL_Renderer* renderer);//»æÖÆ¹¥»÷¡¢·ÀÓù
		void DrawHeroName(SDL_Renderer* renderer);
		void DrawHpBar(SDL_Renderer* renderer);
		void DrawMpBar(SDL_Renderer* renderer);
		void DrawLvBar(SDL_Renderer* renderer);
		void HandKeyPress(int key) override;

		Font* mFont;
		PlayerObject* BindPlayer;
	};
}
#endif __MainMenu__