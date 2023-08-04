#include	"GameObject.h"
#include	"Game.h"
#include	"Component.h"
#include	"InputSystem.h"
#include	"SpriteComponent.h"


namespace GameFrame {
	GameObject::GameObject(Game* game, const std::string& name) :
		mGame(game),
		mState(State::EActive)
	{
		mGame->AddGameObject(this,name);
	}

	GameObject::GameObject(Game* game):
		mGame(game),
		mState(State::EActive)
	{
	}

	GameObject::~GameObject()
	{ 
		mGame->RemoveGameObject(this);
		while (mComponents.empty()) 
		{
			delete mComponents.back();
		}
	}
	void GameObject::update()
	{
		if (mState == GameObject::State::EActive) {
			for (auto component : mComponents) {
				component->update();
			}
		}
	}
	void GameObject::ProcessInput(InputSystem* keystate)
	{
	}
	void GameObject::AddComponent(Component* component)
	{
		mComponents.emplace_back(component);
	}
	void GameObject::RemoveComponent(Component* compoent)
	{
	}
	void GameObject::AddSpriteComponent(SpriteComponent* spritecomponent)
	{
		mSpriteComponents.emplace_back(spritecomponent);
	}
	void GameObject::RemoveSpriteComponent(SpriteComponent* spritecomponent)
	{
	}
	GameObject::State GameObject::GetState() const
	{
		return mState;
	}
	void GameObject::SetState(State state) 
	{
		mState = state;
	}

	class Game* GameObject::GetGame() const
	{
		return mGame;
	}

	void GameObject::Draw(SDL_Renderer* renderer)
	{
		for (auto iter : mSpriteComponents) {
			iter->Draw(renderer);
		}
	}
}
