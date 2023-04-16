#include	"GameObject.h"
#include	"Game.h"
#include	"Component.h"
#include	"SpriteComponent.h"


namespace GameFrame {
	GameObject::GameObject(Game* game, const std::string& name) :
		mDir(Dir::DOWN),
		Pos(0,0),
		mScale(1),
		mRotation(0),
		mGame(game),
		mState(State::EActive)
	{
		mGame->AddGameObject(this,name);
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

	void GameObject::SetPosition(Vector2 pos)
	{
		Pos = pos;
	}

	float GameObject::GetRotation() const
	{
		return 0.0f;
	}

	void GameObject::SetRotation(float rotation)
	{
	}

	Vector2 GameObject::GetScale() const
	{
		return Vector2();
	}

	void GameObject::SetScale(Vector2 scale)
	{
	}

	GameObject::Dir GameObject::GetDir() const
	{
		return mDir;
	}

	void GameObject::SetDir(Dir mdir)
	{
		mDir = mdir;
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

	Vector2 GameObject::GetPosition() const
	{
		return Pos;
	}
	
}
