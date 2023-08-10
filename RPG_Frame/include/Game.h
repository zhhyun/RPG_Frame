#ifndef __I_Game__
#define __I_Game__
#include	<SDL_image.h>
#include	<SDL.h>
#include	<SDL_ttf.h>
#include	<unordered_map>
#include	"InputSystem.h"
#include	"Camera.h"
#include	<tinyxml.h>
#include	<vector>
#include	<json.hpp>
#include	"PhysSpace.h"


namespace GameFrame {
	class GameObject;
	class PlayerObject;
	class NpcObject;
	class ScreenUi;
	class Cursor;
	class Font;
	class BattleSystem;
	class Script;
	class Camera;
	class PhysSpace;

	class Game {
	public:
		Game();
		bool Initialize();
		void loop();
		void shutdown();
		enum class GameState {
			EActive,
			EPause,
			EBattle,
			EStop
		};
		void AddGameObject(GameObject* gameobject, const std::string& Name);
		void RemoveGameObject(GameObject* gameobject);
		SDL_Texture* GetTexture(const std::string& filename);
		SDL_Renderer* GetRenderer() { return mRenderer; };
		InputSystem* GetInputSystem() { return mInputSystem; };
		Cursor* GetCursor() { return mCursor; };
		Camera* GetCamera() { return mCamera; };
		PhysSpace* GetPhysSpace() { return mPhysSpace; };
		//GetAudioSystem();
		GameObject* GetGameObject(const std::string& name);
		PlayerObject* GetPlayer() { return Player; };
		Uint32 GetTicks() { return mTickCount; };
		Uint32 GetAnimTicks() { return mAnimTickCount; };
		GameState GetGameState() { return mGameState; };
		void ProcessInput();
		void SetGameState(GameState state) { mGameState = state; };
		void SetAnimTicks(Uint32 count);
		const std::vector<ScreenUi*>& GetUIStack() { return mUIStack; };
		void PushUI(ScreenUi* ui);
		Font* GetFont(const std::string& Fontname); 

	private:
		void Event();
		void Update();
		void Draw();
		void LoadTexture(const std::string& fileName, const std::string& newName);
		void LoadData();
		void Unload();

		std::unordered_map<std::string, SDL_Texture*> mTextures;
		std::unordered_map<std::string, GameObject*> mGameObjects;//标识要改成游戏角色id
		std::unordered_map<std::string, Font*> mFonts;
		std::vector<GameObject*> mPendingObjects;
		std::vector<ScreenUi*> mUIStack;
		std::vector<Script*> mScriptStack;

		bool							IsRunning;			//游戏运行标记
		bool							mIsUpdating;		//更新标记
		GameState						mGameState;			//游戏运行状态
		SDL_Window*						mWindow;			//窗口指针
		SDL_Renderer*					mRenderer;			//渲染器
		SDL_Texture*					mTexture;			//纹理图片
		Uint32							mTickCount;			//计时器 // uint32型数据结构储存上限为4294967295，换算成时间约497天
		Uint32							mAnimTickCount;		//动画计时器
		InputSystem*					mInputSystem;		//输入处理系统
		BattleSystem*					mBattleSystem;		//战斗系统
		//AudioSystem* mAudioSystem;				//音频系统
		//ActContrSystem* mActContrSystem;			//行为控制系统
		Cursor*							mCursor;			//鼠标
		Camera*							mCamera;			//摄像机
		PhysSpace*						mPhysSpace;			//物理空间
		PlayerObject*					Player;
		NpcObject* Npc;
		
	};

}

#endif __I_Game__