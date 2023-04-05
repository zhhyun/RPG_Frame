#ifndef __I_Game__
#define __I_Game__
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace GameFrame {
	class GameObject;
	class PlayerObejct;

	class Game {
	public:
		Game();
		bool Initialize();
		void loop();
		void shutdown();
		void CreateGameObject(GameObject* gameobject);
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
		//��ȡ��ͼ
		SDL_Texture* GetTexture(const std::string& filename);

	private:
		void Event();
		void Update();
		void Draw();
		void LoadTexture(const std::string& fileName, const std::string& newName);
		void LoadData();
		void Unload();

		std::vector<GameObject*> mGameObjects;
		std::vector<GameObject*> mPendingObjects;

		//ע��unordered_map�ǹ�ϣ������
		std::unordered_map<std::string, SDL_Texture*> mTextures;


		bool							IsRunning;			//��Ϸ���б��
		bool							mIsUpdating;		//���±��
		SDL_Window*						mWindow;			//����ָ��
		SDL_Renderer*					mRenderer;			//��Ⱦ��
		SDL_Texture* mTexture;			//����ͼƬ
		TTF_Font* Font;
	};

}

#endif __I_Game__