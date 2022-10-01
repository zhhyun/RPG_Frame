#include "Game.h"

namespace GameFrame {
	Game::Game() {
		mWindow = nullptr;
		IsRunning = true;
	}

	bool Game::Initialize() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_Log("初始化失败:%s", SDL_GetError());
			return false;
		}

		mWindow = SDL_CreateWindow("FRAME", 400, 200, 600, 480, 0);//XYWH

		if (!mWindow) {
			SDL_Log("窗口初始化失败:%s", SDL_GetError());
		}
		return true;
	}

	void Game::loop() {
		while (IsRunning) {
			Event();
			Update();
			Draw();
		}
	}

	void Game::shutdown()
	{
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
	}

	void Game::Event()
	{
	}

	void Game::Update()
	{
	}

	void Game::Draw()
	{
	}
}


