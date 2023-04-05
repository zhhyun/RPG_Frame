#include "InputComponent.h"
#include "MoveComponent.h"
#include	"GameObject.h"
#include	<SDL.h>

GameFrame::InputComponent::InputComponent(class GameObject* gameobject) :
	IsMain(false),
	RequestComp(NULL),
	Component(gameobject)
{
}

//测试时记得调英文输入法
void GameFrame::InputComponent::ProcessInput(const uint8_t* keystate)
{
	if (IsMain) {
		//若值为1，则送给正在响应的组件
		RequestComp->ProcessInput(keystate);	
	}
	else {
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D]) {
			GetGameObject()->GetComponent<MoveComponent>()->ProcessInput(keystate);
		}
		else if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_X]) {
		}
		
	}
}

