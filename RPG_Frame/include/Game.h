#ifndef __I_Game__
#define __I_Game__
#include	<SDL_image.h>
#include	<SDL.h>
#include	<SDL_ttf.h>
//#include	<string>
#include	<unordered_map>
#include	"InputSystem.h"
#include	<tinyxml.h>

namespace GameFrame {
	class GameObject;
	class PlayerObejct;
	
	class Game {
	public:
		Game();
		bool Initialize();
		void loop();
		void shutdown();
		void AddGameObject(GameObject* gameobject);
		void AddGameObject(GameObject* gameobject, const std::string& Name);
		template<typename T> T* GetGameObject() {
			for (auto com : mGameObjects) {
				T* gameobject = dynamic_cast<T*>(com);
				if (gameobject != nullptr) {
					return gameobject;
				}
			}
			return nullptr;
		}

		void RemoveGameObject(GameObject* gameobject);
		//获取贴图
		SDL_Texture* GetTexture(const std::string& filename);
		GameObject* GetGameObject(const std::string& name);
		Uint32 GetTicks();
		Uint32 GetAnimTicks();
		void SetAnimTicks(Uint32 count);

	private:
		void Event();
		void Update();
		void Draw();
		void LoadTexture(const std::string& fileName, const std::string& newName);
		void LoadData();
		void Unload();

		std::vector<GameObject*> mGameObjects;
		std::vector<GameObject*> mPendingObjects;

		//注：unordered_map是哈希表容器
		std::unordered_map<std::string, SDL_Texture*> mTextures;
		std::unordered_map<std::string, GameObject*> mGameObjects2;

		bool							IsRunning;			//游戏运行标记
		bool							mIsUpdating;		//更新标记
		SDL_Window*						mWindow;			//窗口指针
		SDL_Renderer*					mRenderer;			//渲染器
		SDL_Texture*					mTexture;			//纹理图片
		TTF_Font*						Font;				//字体
		Uint32							mTickCount;			//计时器 // uint32型数据结构储存上限为4294967295，换算成时间约497天
		Uint32							mAnimTickCount;		//动画用计时器
		InputSystem*					mInputSystem;		//输入处理系统
	};

}

#endif __I_Game__