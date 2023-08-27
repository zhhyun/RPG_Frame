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

//����ʱ�ǵõ�Ӣ�����뷨
void GameFrame::InputComponent::ProcessInput(InputSystem* keystate)
{
	//������������������·�ɵ�ָ�����
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

