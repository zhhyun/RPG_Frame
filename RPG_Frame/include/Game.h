#ifndef __I_Game__
#define __I_Game__
#include	<SDL_image.h>
#include	<SDL.h>
#include	<SDL_ttf.h>
#include	<unordered_map>
#include	"InputSystem.h"
#include	<tinyxml.h>
#include	<vector>

namespace GameFrame {
	class GameObject;
	class PlayerObejct;
	class ScreenUi;
	class Cursor;
	class Font;

	class Game {
	public:
		Game();
		bool Initialize();
		void loop();
		void shutdown();
		enum class GameState {
			EActive,
			EPause,
			EStop
		};
		void AddGameObject(GameObject* gameobject, const std::string& Name);
		void RemoveGameObject(GameObject* gameobject);
		SDL_Texture* GetTexture(const std::string& filename);
		SDL_Renderer* GetRenderer() { return mRenderer; };
		InputSystem* GetInputSystem() { return mInputSystem; };
		Cursor* GetCursor() { return mCursor; };
		//GetAudioSystem();
		GameObject* GetGameObject(const std::string& name);
		Uint32 GetTicks() { return mTickCount; };
		Uint32 GetAnimTicks() { return mAnimTickCount; };
		GameState GetGameState() { return mGameState; };
		void ProcessInput();

		void SetGameState(GameState state) { mGameState = state; };
		void SetAnimTicks(Uint32 count);
		const std::vector<ScreenUi*>& GetUIStack() { return mUIStack; };
		void PushUI(ScreenUi* ui);

	private:
		void Event();
		void Update();
		void Draw();
		void LoadTexture(const std::string& fileName, const std::string& newName);
		void LoadData();
		void Unload();

		std::unordered_map<std::string, SDL_Texture*> mTextures;
		std::unordered_map<std::string, GameObject*> mGameObjects;
		std::vector<GameObject*> mPendingObjects;
		std::vector<ScreenUi*> mUIStack;
		std::vector<Font*> mFonts;

		bool							IsRunning;			//游戏运行标记
		bool							mIsUpdating;		//更新标记
		GameState						mGameState;			//游戏运行状态
		SDL_Window*						mWindow;			//窗口指针
		SDL_Renderer*					mRenderer;			//渲染器
		 SDL_Texture*					mTexture;			//纹理图片
		Uint32							mTickCount;			//计时器 // uint32型数据结构储存上限为4294967295，换算成时间约497天
		Uint32							mAnimTickCount;		//动画计时器
		InputSystem*					mInputSystem;		//输入处理系统
		Cursor*							mCursor;			//鼠标
		//mAudioSystem;
	};

}

#endif __I_Game__