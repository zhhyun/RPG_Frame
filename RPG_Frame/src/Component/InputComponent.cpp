#include	"InputComponent.h"
#include	"MoveComponent.h"
#include	"GameObject.h"
#include	"InputSystem.h"
#include	<SDL.h>

GameFrame::InputComponent::InputComponent(class GameObject* gameobject) :
	IsMain(false),
	RequestComp(NULL),
	Component(gameobject)
{
}

//测试时记得调英文输入法
void GameFrame::InputComponent::ProcessInput(InputSystem* keystate)
{

		RequestComp->ProcessInput(keystate);


	/*	if (keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_W) != ButtomState::ENone || 
			keystate->GetState().keyborad.GetKeyValue(SDL_SCANCODE_S) != ButtomState::ENone ||
			keystate->GetState().keyborad.GetKeyValue(SDL_SCANCODE_A) != ButtomState::ENone ||
			keystate->GetState().keyborad.GetKeyValue(SDL_SCANCODE_D) != ButtomState::ENone) {

			GetGameObject()->GetComponent<MoveComponent>()->ProcessInput(keystate);
		}*/

}

void GameFrame::InputComponent::SetRequestCom(Component* component)
{
	RequestComp = component;
}

void GameFrame::InputComponent::SetIsMain(bool is)
{
	IsMain = is;
}

