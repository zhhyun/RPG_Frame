#pragma once
#include <SDL.h>

namespace GameFrame {
	class Game {
	public:
		Game();
		bool Initialize();
		void loop();
		void shutdown();

	private:
		void Event();
		void Update();
		void Draw();

		bool IsRunning;
		SDL_Window* mWindow;
	};
}
