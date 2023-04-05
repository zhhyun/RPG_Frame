#include "Component.h"
#include	"GameObject.h"

namespace GameFrame {
	Component::Component(class GameObject* gameobject):
		mGameObject(gameobject),
		mUpdateOder(100)
	{
		mGameObject->AddComponent(this);
	}

	Component::~Component()
	{
		mGameObject->RemoveComponent(this);
	}

	void Component::update()
	{
	}

	GameObject* Component::GetGameObject()
	{
		return mGameObject;
	}

	void Component::ProcessInput(const uint8_t* keystate)
	{
	}

}