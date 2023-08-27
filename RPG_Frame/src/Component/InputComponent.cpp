#include	"InputComponent.h"
#include	"MoveComponent.h"
#include	"GameObject.h"
#include	"InputSystem.h"
#include	<SDL.h>

GameFrame::InputComponent::InputComponent(GameObject* gameobject) :
	IsMain(false),
	RequestComp(NULL),
	Component(gameobject)
{
}

//测试时记得调英文输入法
void GameFrame::InputComponent::ProcessInput(InputSystem* keystate)
{
	//将传入对象的输入数据路由到指定组件
	RequestComp->ProcessInput(keystate);
}

void GameFrame::InputComponent::SetRequestCom(Component* component)
{
	RequestComp = component;
}

void GameFrame::InputComponent::SetIsMain(bool is)
{
	IsMain = is;
}

