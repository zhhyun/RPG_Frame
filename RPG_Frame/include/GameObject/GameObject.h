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
		GameObject(class Game* game, const std::string& name);
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
		Vector2	GetPosition() const { return Pos; };
		void SetPosition(Vector2 pos) { Pos = pos; };
		void SetPositionX(int x) { Pos.x = x; };
		void SetPositionY(int y) { Pos.y = y; };
		class Game* GetGame() const;
		virtual void Draw(SDL_Renderer* renderer);


	protected:
		std::vector<class Component*> mComponents;
		std::vector<class SpriteComponent*> mSpriteComponents;
		class Game* mGame;
		State								mState;
		Vector2								Pos;
	};
}


#endif 