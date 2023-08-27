#include	"Component.h"
#include	"Game.h"
#include	"GameObject.h"

namespace GameFrame {

	Component::Component(class GameObject* gameobject) :
		mOwner(gameobject),
		mUpdateOder(100)
	{
		mOwner->AddComponent(this);
	}

	Component::~Component()
	{
		mOwner->RemoveComponent(this);
	}

	GameObject* Component::GetGameObject()
	{
		return mOwner;
	}

	void Component::ProcessInput(const InputSystem* keystate)
	{
	}
	void Component::SubscribeToEvent(const std::string& id, std::function<void()> callback)
	{
		//mOwner->GetGame()->GetEventThread()->GetManager()->Subscribe(id, callback);
	}
}