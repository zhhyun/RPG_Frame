#ifndef __GameObject__
#define __GameObject__

#include <SDL.h>
#include <string>
#include <vector>
#include "Math2.h"

namespace GameFrame {
	class GameObject {
	public:
		enum class State {
			EActive,
			EDead
		};
		enum class Dir
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		GameObject(class Game* game, const std::string& name);

		virtual ~GameObject();

		virtual void update();

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
		Vector2	GetPosition() const;
		void SetPosition(Vector2 pos);
		float	GetRotation() const;
		void SetRotation(float rotation);
		Vector2	GetScale() const;
		void SetScale(Vector2 scale);
		Dir GetDir() const;
		void SetDir(Dir mdir);
		class Game* GetGame() const;
		virtual void Draw(SDL_Renderer* renderer);
		bool GetMovingState();
		void SetMovingState(bool ismov);


	protected:
		std::vector<class Component*> mComponents;
		std::vector<class SpriteComponent*> mSpriteComponents;

	private:
		Dir									mDir;
		Vector2								Pos;
		int									mScale;
		float								mRotation;
		class Game*							mGame;
		State								mState;
		bool								IsMoving;

	};
}


#endif 