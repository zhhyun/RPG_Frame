#include "Control.h"
#include "GameObject.h"
GameFrame::Control::Control(GameObject* gameobject, Vector2 pos):
	ObjectPosion(gameobject->GetPosition() + pos),
	BindObject(gameobject)
{
}

void GameFrame::Control::update()
{
}
