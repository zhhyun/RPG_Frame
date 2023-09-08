#ifndef __GameObject__
#define __GameObject__

#include <SDL.h>
#include <string>
#include <vector>
#include "Math2.h"

namespace GameFrame {
	class GameObject {
	public:
		enum State {
			EActive,
			EWaitingDead,
			EDead
		};
		GameObject(class Game* game, const std::string& name, const std::string& id);
		GameObject(class Game* game);
		virtual ~GameObject();

		virtual void update();
		virtual void ProcessInput(class InputSystem* keystate);
		void AddComponent(class Component* component);
		void RemoveComponent(class Component* component);
		template<typename T> T* GetComponent() {
			for (auto com : mComponents) {
				T* component = dynamic_cast<T*>(com);
				if (component != nullptr) {
					return component;
				}
			}
			return nullptr;
		}
		void AddSpriteComponent(class SpriteComponent* spritecomponent);
		void RemoveSpriteComponent(class SpriteComponent* spritecomponent);
		template<typename T> T* GetSpriteComponent() {
			for (auto com : mSpriteComponents) {
				T* component = dynamic_cast<T*>(com);
				if (component != nullptr) {
					return component;
				}
			}
			return nullptr;
		};

		State GetState() const;
		void SetState(State state);
		//位置是以地图为坐标系而不是窗口
		Vector2	GetPosition() const { return ObjectPosion; };
		void SetPosition(Vector2 pos) { ObjectPosion = pos; };
		void SetPositionX(int x) { ObjectPosion.x = x; };
		void SetPositionY(int y) { ObjectPosion.y = y; };
		class Game* GetGame() const;
		virtual void Draw(SDL_Renderer* renderer);
		//获得当前object中心点位置；
		Vector2 GetMidllePoint();
		Vector2 WinVecTransToMapVec(Vector2 Winvec);
		Vector2 MapVecTransToWinVec(int MapW, int MapH, Vector2 vecInmap);


		int GetH() { return Height; };
		void SetH(int h) { Height = h; };
		int GetW() { return Width; };
		void SetW(int w) { Width = w; };
		std::string GetID() { return ID; };

	protected:
		std::vector<class Component*>		mComponents;
		std::vector<class SpriteComponent*> mSpriteComponents;
		class Game*							mGame;
		State								mState;
		Vector2								ObjectPosion;
		const std::string					ID;
		//Sence*								mMap;//挂载的地图
		int									Height;
		int									Width;
	};
}


#endif 