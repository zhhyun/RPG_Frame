#include "Component.h"
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

	void Component::update()
	{
	}

	GameObject* Component::GetGameObject()
	{
		return mOwner;
	}

	void Component::ProcessInput(const uint8_t* keystate)
	{
	}
}